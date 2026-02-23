#include "publication.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>

static void setErr(QString *err, const QString& msg) {
    if (err) *err = msg;
}

bool Publication::nextId(int &outId, QString *err)
{
    QSqlQuery qid;
    if (!qid.exec("SELECT NVL(MAX(ID_PUBLICATION),0)+1 FROM HICHEM.PUBLICATIONS")) {
        setErr(err, qid.lastError().text());
        return false;
    }
    if (!qid.next()) {
        setErr(err, "Impossible de récupérer l'ID_PUBLICATION.");
        return false;
    }
    outId = qid.value(0).toInt();
    return true;
}

bool Publication::ajouter(QString *err) const
{
    int newId = 0;
    if (!nextId(newId, err)) return false;

    // IMPORTANT:
    // Dans ta BD : CINEMP est NOT NULL.
    // Comme tu veux "éliminer CINEMP", on met un placeholder, comme Finance.
    // Il faut que ça respecte ton système (ex: CIN de l'employé connecté).
    const QString CINEMP_PLACEHOLDER = "1234";

    QSqlQuery q;
    q.prepare(
        "INSERT INTO HICHEM.PUBLICATIONS "
        "(ID_PUBLICATION, TITRE, RESUME, INVENTEURS, DOMAINE_FABRICATION, "
        " TYPE_BREVET, NUMERO_BREVET, DATE_DEPOT, STATUT_BREVET, CINEMP) "
        "VALUES "
        "(:id, :titre, :resume, :inventeurs, :domaine, :type, :numero, :dateDepot, :statut, :cin)"
        );

    q.bindValue(":id", newId);
    q.bindValue(":titre", m_titre);
    q.bindValue(":resume", m_resume);
    q.bindValue(":inventeurs", m_inventeurs);
    q.bindValue(":domaine", m_domaineFabrication);
    q.bindValue(":type", m_typeBrevet);
    q.bindValue(":numero", m_numeroBrevet);
    q.bindValue(":dateDepot", m_dateDepot);
    q.bindValue(":statut", m_statutBrevet);
    q.bindValue(":cin", CINEMP_PLACEHOLDER);

    if (!q.exec()) {
        setErr(err, q.lastError().text());
        return false;
    }
    return true;
}

bool Publication::modifier(const QString& idPublication,
                           const QString& titre,
                           const QString& resume,
                           const QString& inventeurs,
                           const QString& domaineFabrication,
                           const QString& typeBrevet,
                           int numeroBrevet,
                           const QDate& dateDepot,
                           const QString& statutBrevet,
                           QString *err)
{
    QSqlQuery q;
    q.prepare(
        "UPDATE HICHEM.PUBLICATIONS SET "
        "TITRE=:titre, "
        "RESUME=:resume, "
        "INVENTEURS=:inventeurs, "
        "DOMAINE_FABRICATION=:domaine, "
        "TYPE_BREVET=:type, "
        "NUMERO_BREVET=:numero, "
        "DATE_DEPOT=:dateDepot, "
        "STATUT_BREVET=:statut "
        "WHERE ID_PUBLICATION=:id"
        );

    q.bindValue(":titre", titre);
    q.bindValue(":resume", resume);
    q.bindValue(":inventeurs", inventeurs);
    q.bindValue(":domaine", domaineFabrication);
    q.bindValue(":type", typeBrevet);
    q.bindValue(":numero", numeroBrevet);
    q.bindValue(":dateDepot", dateDepot);
    q.bindValue(":statut", statutBrevet);
    q.bindValue(":id", idPublication);

    if (!q.exec()) {
        setErr(err, q.lastError().text());
        return false;
    }
    return true;
}

bool Publication::supprimer(const QString& idPublication, QString *err)
{
    QSqlQuery q;
    q.prepare("DELETE FROM HICHEM.PUBLICATIONS WHERE ID_PUBLICATION=:id");
    q.bindValue(":id", idPublication);

    if (!q.exec()) {
        setErr(err, q.lastError().text());
        return false;
    }
    return true;
}

bool Publication::chargerTout(QVector<Row> &out, QString *err)
{
    out.clear();

    QSqlQuery q;
    q.prepare(
        "SELECT ID_PUBLICATION, TITRE, RESUME, INVENTEURS, DOMAINE_FABRICATION, "
        "       TYPE_BREVET, TO_CHAR(NUMERO_BREVET), "
        "       TO_CHAR(DATE_DEPOT,'YYYY-MM-DD'), STATUT_BREVET "
        "FROM HICHEM.PUBLICATIONS "
        "ORDER BY DATE_DEPOT DESC"
        );

    if (!q.exec()) {
        setErr(err, q.lastError().text());
        return false;
    }

    while (q.next()) {
        Row r;
        r.id = q.value(0).toString();
        r.titre = q.value(1).toString();
        r.resume = q.value(2).toString();
        r.inventeurs = q.value(3).toString();
        r.domaineFabrication = q.value(4).toString();
        r.typeBrevet = q.value(5).toString();
        r.numeroBrevet = q.value(6).toString();
        r.dateDepot = q.value(7).toString();
        r.statutBrevet = q.value(8).toString();
        out.push_back(r);
    }

    return true;
}
