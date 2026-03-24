#include "publication.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>

static void setErr(QString *err, const QString &msg) {
    if (err) *err = msg;
}

Publication::Publication(QString titre, QString resume, QString inventeurs,
                         QString domaine, QString type, int numero,
                         QDate dateDepot, QString statut)
    : m_titre(std::move(titre)),
    m_resume(std::move(resume)),
    m_inventeurs(std::move(inventeurs)),
    m_domaine(std::move(domaine)),
    m_type(std::move(type)),
    m_statut(std::move(statut)),
    m_numero(numero),
    m_dateDepot(dateDepot)
{}

bool Publication::nextId(int &outId, QString *err)
{
    QSqlQuery q;
    if (!q.exec("SELECT NVL(MAX(ID_PUBLICATION),0)+1 FROM HICHEM.PUBLICATIONS")) {
        setErr(err, q.lastError().text());
        return false;
    }
    if (!q.next()) return false;
    outId = q.value(0).toInt();
    return true;
}

bool Publication::ajouter(int idemp, QString *err) const
{
    int newId = 0;
    if (!nextId(newId, err)) return false;

    QSqlQuery q;
    q.prepare(
        "INSERT INTO HICHEM.PUBLICATIONS "
        "(ID_PUBLICATION, TITRE, RESUME, INVENTEURS, DOMAINE_FABRICATION, "
        " TYPE_BREVET, NUMERO_BREVET, DATE_DEPOT, STATUT_BREVET, IDEMP) "
        "VALUES "
        "(:id, :titre, :resume, :inventeurs, :domaine, :type, :numero, :dateDepot, :statut, :idemp)"
        );

    q.bindValue(":id", newId);
    q.bindValue(":titre", m_titre);
    q.bindValue(":resume", m_resume);
    q.bindValue(":inventeurs", m_inventeurs);
    q.bindValue(":domaine", m_domaine);
    q.bindValue(":type", m_type);
    q.bindValue(":numero", m_numero);
    q.bindValue(":dateDepot", m_dateDepot);
    q.bindValue(":statut", m_statut);
    q.bindValue(":idemp", idemp);

    if (!q.exec()) {
        setErr(err, q.lastError().text());
        return false;
    }
    return true;
}

bool Publication::modifier(const QString &id,
                           const QString &titre,
                           const QString &resume,
                           const QString &inventeurs,
                           const QString &domaine,
                           const QString &type,
                           int numero,
                           const QDate &dateDepot,
                           const QString &statut,
                           QString *err)
{
    QSqlQuery q;
    q.prepare(
        "UPDATE HICHEM.PUBLICATIONS SET "
        "TITRE=:titre, RESUME=:resume, INVENTEURS=:inventeurs, "
        "DOMAINE_FABRICATION=:domaine, TYPE_BREVET=:type, "
        "NUMERO_BREVET=:numero, DATE_DEPOT=:dateDepot, STATUT_BREVET=:statut "
        "WHERE ID_PUBLICATION=:id"
        );

    q.bindValue(":titre", titre);
    q.bindValue(":resume", resume);
    q.bindValue(":inventeurs", inventeurs);
    q.bindValue(":domaine", domaine);
    q.bindValue(":type", type);
    q.bindValue(":numero", numero);
    q.bindValue(":dateDepot", dateDepot);
    q.bindValue(":statut", statut);
    q.bindValue(":id", id);

    if (!q.exec()) {
        setErr(err, q.lastError().text());
        return false;
    }
    return true;
}

bool Publication::supprimer(const QString &id, QString *err)
{
    QSqlQuery q;
    q.prepare("DELETE FROM HICHEM.PUBLICATIONS WHERE ID_PUBLICATION=:id");
    q.bindValue(":id", id);

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
        "TYPE_BREVET, TO_CHAR(NUMERO_BREVET), TO_CHAR(DATE_DEPOT,'YYYY-MM-DD'), "
        "STATUT_BREVET, IDEMP "
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
        r.domaine = q.value(4).toString();
        r.type = q.value(5).toString();
        r.numero = q.value(6).toString();
        r.dateDepot = q.value(7).toString();
        r.statut = q.value(8).toString();
        r.idemp = q.value(9).toInt();
        out.push_back(r);
    }
    return true;
}
