#include "inventory.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QVariant>
#include <QDebug>
#include <algorithm>

static void setErr(QString *err, const QString &msg) {
    if (err) *err = msg;
}

// ── Constructor ───────────────────────────────────────────────────────────────
Inventory::Inventory(QString name, QString sku, QString type, int qtAv, int qtRs,
                     int threshold, QString unit, double price, QString status,
                     QString zone, QString shelf, QString description)
    : m_name(std::move(name))
    , m_sku(std::move(sku))
    , m_type(std::move(type))
    , m_qtAv(qtAv)
    , m_qtRs(qtRs)
    , m_threshold(threshold)
    , m_unit(std::move(unit))
    , m_price(price)
    , m_status(std::move(status))
    , m_zone(std::move(zone))
    , m_shelf(std::move(shelf))
    , m_description(std::move(description))
    , m_idemp(0)
{}

bool Inventory::nextId(int &outId, QString *err)
{
    QSqlQuery q;
    if (!q.exec("SELECT NVL(MAX(ID_PRODUCT), 0) + 1 FROM PRODUCT")) {
        setErr(err, q.lastError().text());
        return false;
    }
    if (q.next()) {
        outId = q.value(0).toInt();
        return true;
    }
    return false;
}

// ── CREATE ───────────────────────────────────────────────────────────────────
bool Inventory::ajouter(QString *err) const
{
    int newId = 0;
    if (!nextId(newId, err)) return false;

    QSqlQuery q;
    q.prepare(
        "INSERT INTO PRODUCT "
        "(ID_PRODUCT, SKU, QT_AV, STATUS, IDEMP, NAME, PRICE, TYPE, QT_RS, THRESHOLD, UNIT, ZONE, SHELF, DESCR, USE_COUNT) "
        "VALUES (:id, :sku, :qt, :status, (SELECT NVL(MIN(ID_EMPLOYE), 1) FROM EMPLOYES), :name, :price, :type, :qtr, :thr, :unit, :zone, :shelf, :desc, :usecount)"
    );
    q.bindValue(":id",     newId);
    q.bindValue(":sku",    m_sku);
    q.bindValue(":qt",     m_qtAv);
    q.bindValue(":status", m_status);
    q.bindValue(":name",   m_name);
    q.bindValue(":price",  m_price);
    q.bindValue(":type",   m_type);
    q.bindValue(":qtr",    m_qtRs);
    q.bindValue(":thr",    m_threshold);
    q.bindValue(":unit",   m_unit);
    q.bindValue(":zone",   m_zone);

    // If shelf is text and column is numeric, try a fallback
    bool shelfOk;
    int shelfNum = m_shelf.toInt(&shelfOk);
    if (shelfOk) q.bindValue(":shelf", shelfNum);
    else q.bindValue(":shelf", m_shelf); // Try string anyway, handler will catch ORA-01722


    q.bindValue(":desc",   m_description);
    q.bindValue(":usecount", 0);


    if (!q.exec()) {
        QString e = q.lastError().text();
        if (e.contains("ORA-00904") || e.contains("ORA-01722")) {
             QSqlQuery alter;
             // Ensure columns exist and have correct types
             alter.exec("ALTER TABLE PRODUCT ADD NAME VARCHAR2(200)");
             alter.exec("ALTER TABLE PRODUCT ADD PRICE NUMBER");
             alter.exec("ALTER TABLE PRODUCT ADD TYPE VARCHAR2(100)");
             alter.exec("ALTER TABLE PRODUCT ADD QT_RS NUMBER");
             alter.exec("ALTER TABLE PRODUCT ADD THRESHOLD NUMBER");
             alter.exec("ALTER TABLE PRODUCT ADD UNIT VARCHAR2(50)");
             alter.exec("ALTER TABLE PRODUCT ADD ZONE VARCHAR2(100)");
             
             // Fix SHELF: If it's already a NUMBER, ORA-01722 occurs if we try to insert "1st floor".
             // We attempt to change it to VARCHAR2(100) if it already exists as NUMBER.
             if (!alter.exec("ALTER TABLE PRODUCT ADD SHELF VARCHAR2(100)")) {
                 // If it fails because column already exists, try MODIFY
                 alter.exec("ALTER TABLE PRODUCT MODIFY SHELF VARCHAR2(100)");
             }

             alter.exec("ALTER TABLE PRODUCT ADD DESCR VARCHAR2(2000)");
             alter.exec("ALTER TABLE PRODUCT ADD USE_COUNT NUMBER DEFAULT 0");

             // Finally try adding IDEMP if missing
             alter.exec("ALTER TABLE PRODUCT ADD IDEMP NUMBER");

             if (q.exec()) return true;
        }

        setErr(err, q.lastError().text());
        return false;
    }
    return true;
}

// ── UPDATE ───────────────────────────────────────────────────────────────────
bool Inventory::modifier(const QString &idProduct,
                         const QString &name, const QString &sku, const QString &type,
                         int qtAv, int qtRs, int threshold, const QString &unit,
                         double price, const QString &status, const QString &zone,
                         const QString &shelf, const QString &description, QString *err)
{
    QSqlQuery q;
    q.prepare(
        "UPDATE PRODUCT SET "
        "QT_AV=:qt, STATUS=:status, SKU=:sku, NAME=:name, PRICE=:price, TYPE=:type, QT_RS=:qtr, THRESHOLD=:thr, UNIT=:unit, ZONE=:zone, SHELF=:shelf, DESCR=:desc "
        "WHERE ID_PRODUCT=:id"
    );
    q.bindValue(":qt",     qtAv);
    q.bindValue(":status", status);
    q.bindValue(":sku",    sku);
    q.bindValue(":name",   name);
    q.bindValue(":price",  price);
    q.bindValue(":type",   type);
    q.bindValue(":qtr",    qtRs);
    q.bindValue(":thr",    threshold);
    q.bindValue(":unit",   unit);
    q.bindValue(":zone",   zone);

    bool shelfOk;
    int shelfNum = shelf.toInt(&shelfOk);
    if (shelfOk) q.bindValue(":shelf", shelfNum);
    else q.bindValue(":shelf", shelf);

    q.bindValue(":desc",   description);
    q.bindValue(":id",     idProduct);


    if (!q.exec()) {
        QString e = q.lastError().text();
        if (e.contains("ORA-00904") || e.contains("ORA-01722")) {
             QSqlQuery alter;
             alter.exec("ALTER TABLE PRODUCT ADD DESCR VARCHAR2(2000)");
             alter.exec("ALTER TABLE PRODUCT ADD USE_COUNT NUMBER DEFAULT 0");
             if (q.exec()) return true;
        }
        setErr(err, q.lastError().text());
        return false;
    }
    return true;
}


// ── DELETE ───────────────────────────────────────────────────────────────────
bool Inventory::supprimer(const QString &idProduct,
                           const QString &sku,
                           QString *err)
{
    QSqlQuery q;
    q.prepare("DELETE FROM PRODUCT WHERE ID_PRODUCT=:id");
    q.bindValue(":id",  idProduct);
    if (!q.exec()) {
        setErr(err, q.lastError().text());
        return false;
    }
    return true;
}

static void fillRow(const QSqlQuery &q, Inventory::Row &r) {
    r.idProduct = q.value("ID_PRODUCT").toString();
    r.sku       = q.value("SKU").toString();
    r.qtAv      = q.value("QT_AV").toInt();
    r.status    = q.value("STATUS").toString();
    r.idemp     = q.value("IDEMP").toInt();
    
    QSqlRecord rec = q.record();
    if (rec.indexOf("NAME")      >= 0) r.name      = q.value("NAME").toString();
    if (rec.indexOf("PRICE")     >= 0) r.price     = q.value("PRICE").toDouble();
    if (rec.indexOf("TYPE")      >= 0) r.type      = q.value("TYPE").toString();
    if (rec.indexOf("QT_RS")     >= 0) r.qtRs      = q.value("QT_RS").toInt();
    if (rec.indexOf("THRESHOLD") >= 0) r.threshold = q.value("THRESHOLD").toInt();
    if (rec.indexOf("UNIT")        >= 0) r.unit        = q.value("UNIT").toString();
    if (rec.indexOf("ZONE")        >= 0) r.zone        = q.value("ZONE").toString();
    if (rec.indexOf("SHELF")       >= 0) r.shelf       = q.value("SHELF").toString();
    if (rec.indexOf("DESCR")       >= 0) r.description = q.value("DESCR").toString();
    if (rec.indexOf("DESCRIPTION") >= 0) r.description = q.value("DESCRIPTION").toString(); 
    if (rec.indexOf("USE_COUNT") >= 0) r.useCount = q.value("USE_COUNT").toInt();
    else r.useCount = 0;
}

// ── READ ALL ─────────────────────────────────────────────────────────────────
bool Inventory::chargerTout(QVector<Row> &out, const QString &orderBy, QString *err)
{
    out.clear();
    QSqlQuery q;
    // Select all columns with dynamic order
    QString sql = "SELECT * FROM PRODUCT ORDER BY " + orderBy;
    if (!q.exec(sql)) {
        setErr(err, q.lastError().text());
        return false;
    }

    while (q.next()) {
        Row r;
        fillRow(q, r);
        out.push_back(r);
    }
    return true;
}

bool Inventory::typesDistincts(QVector<QString> &out, QString *err)
{
    out.clear();
    QSqlQuery q;
    if (!q.exec("SELECT DISTINCT TYPE FROM PRODUCT "
                "WHERE TYPE IS NOT NULL AND LENGTH(TRIM(TYPE)) > 0 "
                "ORDER BY TYPE")) {
        setErr(err, q.lastError().text());
        return false;
    }
    while (q.next()) {
        const QString t = q.value(0).toString().trimmed();
        if (!t.isEmpty() && !out.contains(t))
            out.push_back(t);
    }
    std::sort(out.begin(), out.end(), [](const QString &a, const QString &b) {
        return QString::localeAwareCompare(a, b) < 0;
    });
    return true;
}

// ── SEARCH ───────────────────────────────────────────────────────────────────
bool Inventory::chercher(QVector<Row> &out, const QString &keyword, const QString &zone,
                         const QString &status, const QString &type, const QString &orderBy, QString *err)
{
    out.clear();

    // Safely escape a string for inline SQL (prevent injection in read queries)
    auto esc = [](const QString &s) -> QString {
        return s.toUpper().replace("'", "''");
    };

    QString sql = "SELECT * FROM PRODUCT WHERE 1=1";

    if (!keyword.isEmpty()) {
        const QString k = esc(keyword);
        sql += QString(" AND (TO_CHAR(ID_PRODUCT) LIKE '%%%1%%'"
                       " OR UPPER(SKU) LIKE '%%%1%%'"
                       " OR UPPER(NAME) LIKE '%%%1%%')").arg(k);
    }
    if (!zone.isEmpty()) {
        sql += QString(" AND UPPER(ZONE) = '%1'").arg(esc(zone));
    }
    if (!status.isEmpty()) {
        // Status stored as-is (mixed case in DB), do case-insensitive compare
        sql += QString(" AND UPPER(STATUS) = '%1'").arg(esc(status));
    }
    if (!type.isEmpty()) {
        QString t = type;
        t.replace(QLatin1Char('\''), QLatin1String("''"));
        sql += QString(" AND TYPE = '%1'").arg(t);
    }

    const QString order = orderBy.isEmpty() ? "SKU" : orderBy;
    sql += " ORDER BY " + order;

    QSqlQuery q;
    if (!q.exec(sql)) {
        // Fallback: try without NAME column (older schema) and simpler sort
        QString sql2 = "SELECT * FROM PRODUCT WHERE 1=1";
        if (!keyword.isEmpty()) {
            const QString k = esc(keyword);
            sql2 += QString(" AND (TO_CHAR(ID_PRODUCT) LIKE '%%%1%%' OR UPPER(SKU) LIKE '%%%1%%')").arg(k);
        }
        if (!zone.isEmpty())
            sql2 += QString(" AND UPPER(ZONE) = '%1'").arg(esc(zone));
        if (!status.isEmpty())
            sql2 += QString(" AND UPPER(STATUS) = '%1'").arg(esc(status));
        if (!type.isEmpty()) {
            QString t = type;
            t.replace(QLatin1Char('\''), QLatin1String("''"));
            sql2 += QString(" AND TYPE = '%1'").arg(t);
        }
        sql2 += " ORDER BY SKU";

        if (!q.exec(sql2)) {
            setErr(err, q.lastError().text());
            return false;
        }
    }

    while (q.next()) {
        Row r;
        fillRow(q, r);
        out.push_back(r);
    }
    return true;
}

// ── THRESHOLD ALERTS ─────────────────────────────────────────────────────────
bool Inventory::checkThresholdAlerts(QVector<Row> &out, QString *err)
{
    out.clear();
    QSqlQuery q;
    // Produit en alerte : quantité disponible <= seuil
    // On exclut les produits à seuil 0 (non configuré)
    if (!q.exec(
            "SELECT * FROM PRODUCT "
            "WHERE NVL(THRESHOLD, 0) > 0 "
            "AND NVL(QT_AV, 0) <= NVL(THRESHOLD, 0) "
            "ORDER BY SKU"
            )) {
        setErr(err, q.lastError().text());
        return false;
    }
    while (q.next()) {
        Row r;
        fillRow(q, r);
        out.push_back(r);
    }
    return true;
}
