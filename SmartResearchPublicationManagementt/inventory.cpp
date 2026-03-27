#include "inventory.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QVariant>
#include <QDebug>

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
        "(ID_PRODUCT, SKU, QT_AV, STATUS, IDEMP, NAME, PRICE, TYPE, QT_RS, THRESHOLD, UNIT, ZONE, SHELF, DESCR) "
        "VALUES (:id, :sku, :qt, :status, (SELECT NVL(MIN(ID_EMPLOYE), 0) FROM EMPLOYES), :name, :price, :type, :qtr, :thr, :unit, :zone, :shelf, :desc)"
    );
    q.bindValue(":id",     newId);
    q.bindValue(":sku",    m_sku);
    q.bindValue(":qt",     QString::number(m_qtAv));
    q.bindValue(":status", m_status);
    q.bindValue(":name",   m_name);
    q.bindValue(":price",  m_price);
    q.bindValue(":type",   m_type);
    q.bindValue(":qtr",    QString::number(m_qtRs));
    q.bindValue(":thr",    QString::number(m_threshold));
    q.bindValue(":unit",   m_unit);
    q.bindValue(":zone",   m_zone);

    // SHELF is NUMBER in DB, but UI has "RDC", "1st floor" etc.
    // Try to convert to number, or use 0 if it's text to prevent ORA-01722
    bool ok;
    int shelfNum = m_shelf.toInt(&ok);
    q.bindValue(":shelf", ok ? shelfNum : 0); 

    q.bindValue(":desc",   m_description);

    if (!q.exec()) {
        QString e = q.lastError().text();
        if (e.contains("ORA-00904")) {
             QSqlQuery alter;
             // Add columns one by one if they might be missing. This avoids failure if some exist.
             alter.exec("ALTER TABLE PRODUCT ADD NAME VARCHAR2(200)");
             alter.exec("ALTER TABLE PRODUCT ADD PRICE NUMBER");
             alter.exec("ALTER TABLE PRODUCT ADD TYPE VARCHAR2(100)");
             alter.exec("ALTER TABLE PRODUCT ADD QT_RS NUMBER");
             alter.exec("ALTER TABLE PRODUCT ADD THRESHOLD NUMBER");
             alter.exec("ALTER TABLE PRODUCT ADD UNIT VARCHAR2(50)");
             alter.exec("ALTER TABLE PRODUCT ADD ZONE VARCHAR2(100)");
             alter.exec("ALTER TABLE PRODUCT ADD SHELF VARCHAR2(100)");
             alter.exec("ALTER TABLE PRODUCT ADD DESCR VARCHAR2(2000)");
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
    q.bindValue(":qt",     QString::number(qtAv));
    q.bindValue(":status", status);
    q.bindValue(":sku",    sku);
    q.bindValue(":name",   name);
    q.bindValue(":price",  price);
    q.bindValue(":type",   type);
    q.bindValue(":qtr",    QString::number(qtRs));
    q.bindValue(":thr",    QString::number(threshold));
    q.bindValue(":unit",   unit);
    q.bindValue(":zone",   zone);

    bool ok;
    int shelfNum = shelf.toInt(&ok);
    q.bindValue(":shelf", ok ? shelfNum : 0);

    q.bindValue(":desc",   description);
    q.bindValue(":id",     idProduct);

    if (!q.exec()) {
        QString e = q.lastError().text();
        if (e.contains("ORA-00904")) {
             QSqlQuery alter;
             alter.exec("ALTER TABLE PRODUCT ADD DESCR VARCHAR2(2000)");
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

// ── SEARCH ───────────────────────────────────────────────────────────────────
bool Inventory::chercher(QVector<Row> &out, const QString &keyword, const QString &status, const QString &orderBy, QString *err)
{
    out.clear();
    QString sql = "SELECT * FROM PRODUCT WHERE 1=1";
    
    // Search in ID, SKU, and NAME
    if (!keyword.isEmpty()) {
        sql += " AND (TO_CHAR(ID_PRODUCT) LIKE :kw OR UPPER(SKU) LIKE UPPER(:kw2) OR UPPER(NAME) LIKE UPPER(:kw3))";
    }
    if (!status.isEmpty()) {
        sql += " AND STATUS=:status";
    }
    sql += " ORDER BY " + orderBy;

    QSqlQuery q;
    q.prepare(sql);
    if (!keyword.isEmpty()) {
        QString like = "%" + keyword + "%";
        q.bindValue(":kw",  like);
        q.bindValue(":kw2", like);
        q.bindValue(":kw3", like);
    }
    if (!status.isEmpty()) q.bindValue(":status", status);

    if (!q.exec()) { 
        // Fallback search if NAME doesn't exist yet
        sql = "SELECT * FROM PRODUCT WHERE 1=1";
        if (!keyword.isEmpty()) sql += " AND (UPPER(SKU) LIKE UPPER(:kw))";
        if (!status.isEmpty()) sql += " AND STATUS=:status";
        sql += " ORDER BY SKU";
        q.prepare(sql);
        if (!keyword.isEmpty()) {
            QString l = "%" + keyword + "%";
            q.bindValue(":kw",  l);
        }
        if (!status.isEmpty()) q.bindValue(":status", status);
        if (!q.exec()) { setErr(err, q.lastError().text()); return false; }
    }

    while (q.next()) {
        Row r;
        fillRow(q, r);
        out.push_back(r);
    }
    return true;
}
