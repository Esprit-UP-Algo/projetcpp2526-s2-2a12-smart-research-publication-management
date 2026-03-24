#include "finance.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>

static void setErr(QString *err, const QString& msg) {
    if (err) *err = msg;
}

bool Finance::nextId(int &outId, QString *err)
{
    QSqlQuery qid;
    if (!qid.exec("SELECT NVL(MAX(IDFINANCE),0)+1 FROM HICHEM.FINANCE")) {
        setErr(err, qid.lastError().text());
        return false;
    }
    if (!qid.next()) {
        setErr(err, "Impossible de récupérer l'IDFINANCE.");
        return false;
    }
    outId = qid.value(0).toInt();
    return true;
}

bool Finance::ajouter(QString *err) const
{
    int newId = 0;
    if (!nextId(newId, err)) return false;

    QSqlQuery q;
    q.prepare(
        "INSERT INTO HICHEM.FINANCE "
        "(IDFINANCE, CODETRANSA, TYPETRANSACTION, MONTANT, CATEGORIE, DESCRIPTION, "
        " DATETRANSACTION, MODEPAIEMENT, DATECREATION, IDEMP) "
<<<<<<< HEAD:SmartResearchPublicationManagementt_V4/finance.cpp
        "VALUES (:id, :code, :type, :montant, :cat, :desc, :dt, :mode, :dc, :cin)"
=======
        "VALUES (:id, :code, :type, :montant, :cat, :desc, :dt, :mode, :dc, :idemp)"
>>>>>>> 9fd98e05953d86978b42c6fda2f7a3b994435af5:SmartResearchPublicationManagement_V003/finance.cpp
        );

    q.bindValue(":id", newId);
    q.bindValue(":code", m_code);
    q.bindValue(":type", m_type);
    q.bindValue(":montant", m_montant);
    q.bindValue(":cat", m_categorie);
    q.bindValue(":desc", m_description);
    q.bindValue(":dt", m_dateTransaction);
    q.bindValue(":mode", m_modePaiement);
    q.bindValue(":dc", m_dateCreation);
<<<<<<< HEAD:SmartResearchPublicationManagementt_V4/finance.cpp
    q.bindValue(":cin", m_IDEMP);
=======
    q.bindValue(":idemp", m_IDEMP);
>>>>>>> 9fd98e05953d86978b42c6fda2f7a3b994435af5:SmartResearchPublicationManagement_V003/finance.cpp

    if (!q.exec()) {
        setErr(err, q.lastError().text());
        return false;
    }
    return true;
}

bool Finance::modifier(const QString& idFinance,
                       const QString& code,
                       const QString& type,
                       double montant,
                       const QString& categorie,
                       const QString& description,
                       const QDate& dateTransaction,
                       const QString& modePaiement,
                       const QDate& dateCreation,
                       QString *err)
{
    QSqlQuery q;
    q.prepare(
        "UPDATE HICHEM.FINANCE SET "
        "CODETRANSA=:code, "
        "TYPETRANSACTION=:type, "
        "MONTANT=:montant, "
        "CATEGORIE=:cat, "
        "DESCRIPTION=:desc, "
        "DATETRANSACTION=:dt, "
        "MODEPAIEMENT=:mode, "
        "DATECREATION=:dc "
        "WHERE IDFINANCE=:id"
        );

    q.bindValue(":code", code);
    q.bindValue(":type", type);
    q.bindValue(":montant", montant);
    q.bindValue(":cat", categorie);
    q.bindValue(":desc", description);
    q.bindValue(":dt", dateTransaction);
    q.bindValue(":mode", modePaiement);
    q.bindValue(":dc", dateCreation);
    q.bindValue(":id", idFinance);

    if (!q.exec()) {
        setErr(err, q.lastError().text());
        return false;
    }
    return true;
}

bool Finance::supprimer(const QString& idFinance, QString *err)
{
    QSqlQuery q;
    q.prepare("DELETE FROM HICHEM.FINANCE WHERE IDFINANCE=:id");
    q.bindValue(":id", idFinance);

    if (!q.exec()) {
        setErr(err, q.lastError().text());
        return false;
    }
    return true;
}

bool Finance::chargerTout(QVector<Row> &out, QString *err)
{
    out.clear();

    QSqlQuery q;
    q.prepare(
        "SELECT IDFINANCE, CODETRANSA, TYPETRANSACTION, MONTANT, CATEGORIE, "
        "       DESCRIPTION, TO_CHAR(DATETRANSACTION,'YYYY-MM-DD'), "
        "       MODEPAIEMENT, TO_CHAR(DATECREATION,'YYYY-MM-DD') "
        "FROM HICHEM.FINANCE "
        "ORDER BY DATETRANSACTION DESC"
        );

    if (!q.exec()) {
        setErr(err, q.lastError().text());
        return false;
    }

    while (q.next()) {
        Row r;
        r.id = q.value(0).toString();
        r.code = q.value(1).toString();
        r.type = q.value(2).toString();
        r.montant = q.value(3).toString();
        r.categorie = q.value(4).toString();
        r.description = q.value(5).toString();
        r.dateTransaction = q.value(6).toString();
        r.modePaiement = q.value(7).toString();
        r.dateCreation = q.value(8).toString();
        out.push_back(r);
    }
    return true;
}
