#include "labs.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>

static void setErr(QString *err, const QString& msg) {
    if (err) *err = msg;
}

bool Labs::nextId(int &outId, QString *err)
{
    QSqlQuery qid;
    if (!qid.exec("SELECT NVL(MAX(IDLABO),0)+1 FROM HICHEM.LABS")) {
        setErr(err, qid.lastError().text());
        return false;
    }
    if (!qid.next()) {
        setErr(err, "Impossible de récupérer l'IDLABO.");
        return false;
    }
    outId = qid.value(0).toInt();
    return true;
}

bool Labs::ajouter(QString *err) const
{
    int newId = 0;
    if (!nextId(newId, err)) return false;

    QSqlQuery q;
<<<<<<< HEAD:SmartResearchPublicationManagementt_V4/labs.cpp
    q.prepare(
        "INSERT INTO HICHEM.LABS "
        "(IDLABO, RESPONSABLE, LOCALISATION, NUMERO, SPECIALITE, DISPONIBILITE, "
        " RESULTAT, QRLABS, NOMLABO) "
        "VALUES (:id, :resp, :loc, :num, :spec, :disp, :res, :qr, :nom)"
        );

    q.bindValue(":id", newId);
    q.bindValue(":resp", m_responsable);
    q.bindValue(":loc",  m_localisation);
    q.bindValue(":num",  m_numero);
    q.bindValue(":spec", m_specialite);
    q.bindValue(":disp", m_disponibilite);
    q.bindValue(":res",  m_resultat);
    q.bindValue(":qr",   m_qrlabs);
    q.bindValue(":nom",  m_nomlabo);
    //q.bindValue(":cin",  m_IDEMP);
=======
    q.prepare(R"(
        INSERT INTO HICHEM.LABS
        (IDLABO, NOMLABO, RESPONSABLE, NUMERO, LOCALISATION,
         SPECIALITE, DISPONIBILITE, RESULTAT, QRLABS, IDEMP)
        VALUES
        (:id, :nom, :resp, :num, :loc,
         :spec, :disp, :res, :qr, :idemp)
    )");

    q.bindValue(":id",    newId);
    q.bindValue(":nom",   m_nomlabo);
    q.bindValue(":resp",  m_responsable);
    q.bindValue(":num",   m_numero);
    q.bindValue(":loc",   m_localisation);
    q.bindValue(":spec",  m_specialite);
    q.bindValue(":disp",  m_disponibilite);
    q.bindValue(":res",   m_resultat);
    q.bindValue(":qr",    m_qrlabs);
    q.bindValue(":idemp", m_IDEMP);   // IMPORTANT
>>>>>>> 9fd98e05953d86978b42c6fda2f7a3b994435af5:SmartResearchPublicationManagement_V003/labs.cpp

    if (!q.exec()) {
        setErr(err, q.lastError().text());
        return false;
    }
    return true;
}

bool Labs::modifier(const QString& idLabo,
                    const QString& nomlabo,
                    const QString& responsable,
                    const QString& numero,
                    const QString& localisation,
                    const QString& specialite,
                    const QString& disponibilite,
                    const QString& resultat,
                    const QString& qrlabs,
                    QString *err)
{
    QSqlQuery q;
    q.prepare(
        "UPDATE HICHEM.LABS SET "
        "NOMLABO=:nom, "
        "RESPONSABLE=:resp, "
        "NUMERO=:num, "
        "LOCALISATION=:loc, "
        "SPECIALITE=:spec, "
        "DISPONIBILITE=:disp, "
        "RESULTAT=:res, "
        "QRLABS=:qr "
        "WHERE IDLABO=:id"
        );

    q.bindValue(":nom",  nomlabo);
    q.bindValue(":resp", responsable);
    q.bindValue(":num",  numero);
    q.bindValue(":loc",  localisation);
    q.bindValue(":spec", specialite);
    q.bindValue(":disp", disponibilite);
    q.bindValue(":res",  resultat);
    q.bindValue(":qr",   qrlabs);
    q.bindValue(":id",   idLabo);

    if (!q.exec()) {
        setErr(err, q.lastError().text());
        return false;
    }
    return true;
}

bool Labs::supprimer(const QString& idLabo, QString *err)
{
    QSqlQuery q;
    q.prepare("DELETE FROM HICHEM.LABS WHERE IDLABO=:id");
    q.bindValue(":id", idLabo);

    if (!q.exec()) {
        setErr(err, q.lastError().text());
        return false;
    }
    return true;
}

bool Labs::chargerTout(QVector<Row> &out, QString *err)
{
    out.clear();

    QSqlQuery q;
    q.prepare(
        "SELECT IDLABO, NOMLABO, RESPONSABLE, NUMERO, LOCALISATION, "
        "       DISPONIBILITE, SPECIALITE, RESULTAT, QRLABS "
        "FROM HICHEM.LABS "
        "ORDER BY IDLABO DESC"
        );

    if (!q.exec()) {
        setErr(err, q.lastError().text());
        return false;
    }

    while (q.next()) {
        Row r;
        r.id            = q.value(0).toString();
        r.nomlabo       = q.value(1).toString();
        r.responsable   = q.value(2).toString();
        r.numero        = q.value(3).toString();
        r.localisation  = q.value(4).toString();
        r.disponibilite = q.value(5).toString();
        r.specialite    = q.value(6).toString();
        r.resultat      = q.value(7).toString();
        r.qrlabs        = q.value(8).toString();
        out.push_back(r);
    }

    return true;
}
