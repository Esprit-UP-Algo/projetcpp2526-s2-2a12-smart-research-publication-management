#include "publication.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>

Publication::Publication(
    const QString& titre,
    const QString& resume,
    const QString& inventeurs,
    const QString& domaineFabrication,
    const QString& typeBrevet,
    int numeroBrevet,
    const QDate& dateDepot,
    const QString& statutBrevet,
    const QString& idEmp
    )
    : m_titre(titre),
    m_resume(resume),
    m_inventeurs(inventeurs),
    m_domaineFabrication(domaineFabrication),
    m_typeBrevet(typeBrevet),
    m_numeroBrevet(numeroBrevet),
    m_dateDepot(dateDepot),
    m_statutBrevet(statutBrevet),
    m_idEmp(idEmp)
{
}

bool Publication::nextId(int &outId, QString *err)
{
    QSqlQuery query;
    if (!query.exec("SELECT NVL(MAX(ID_PUBLICATION), 0) + 1 FROM PUBLICATIONS")) {
        if (err) *err = query.lastError().text();
        return false;
    }

    if (query.next()) {
        outId = query.value(0).toInt();
        return true;
    }

    if (err) *err = "Impossible de générer l'identifiant de la publication.";
    return false;
}

bool Publication::ajouter(QString *err) const
{
    int id = 0;
    if (!nextId(id, err))
        return false;

    QSqlQuery query;
    query.prepare(
        "INSERT INTO PUBLICATIONS ("
        "ID_PUBLICATION, TITRE, RESUME, INVENTEURS, DOMAINE_FABRICATION, "
        "TYPE_BREVET, NUMERO_BREVET, DATE_DEPOT, STATUT_BREVET, LIEN_DOCUMENT, IDEMP"
        ") VALUES ("
        ":id, :titre, :resume, :inventeurs, :domaine, "
        ":typeBrevet, :numeroBrevet, :dateDepot, :statutBrevet, NULL, :idEmp)"
        );

    query.bindValue(":id", id);
    query.bindValue(":titre", m_titre);
    query.bindValue(":resume", m_resume);
    query.bindValue(":inventeurs", m_inventeurs);
    query.bindValue(":domaine", m_domaineFabrication);
    query.bindValue(":typeBrevet", m_typeBrevet);

    if (m_numeroBrevet <= 0)
        query.bindValue(":numeroBrevet", QVariant(QVariant::Int));
    else
        query.bindValue(":numeroBrevet", m_numeroBrevet);

    query.bindValue(":dateDepot", m_dateDepot);
    query.bindValue(":statutBrevet", m_statutBrevet);
    query.bindValue(":idEmp", m_idEmp);

    if (!query.exec()) {
        if (err) *err = "Erreur ajout publication : " + query.lastError().text();
        return false;
    }

    return true;
}

bool Publication::modifier(const QString& idPublication, QString *err) const
{
    QSqlQuery query;
    query.prepare(
        "UPDATE PUBLICATIONS SET "
        "TITRE = :titre, "
        "RESUME = :resume, "
        "INVENTEURS = :inventeurs, "
        "DOMAINE_FABRICATION = :domaine, "
        "TYPE_BREVET = :typeBrevet, "
        "NUMERO_BREVET = :numeroBrevet, "
        "DATE_DEPOT = :dateDepot, "
        "STATUT_BREVET = :statutBrevet "
        "WHERE ID_PUBLICATION = :id"
        );

    query.bindValue(":titre", m_titre);
    query.bindValue(":resume", m_resume);
    query.bindValue(":inventeurs", m_inventeurs);
    query.bindValue(":domaine", m_domaineFabrication);
    query.bindValue(":typeBrevet", m_typeBrevet);

    if (m_numeroBrevet <= 0)
        query.bindValue(":numeroBrevet", QVariant(QVariant::Int));
    else
        query.bindValue(":numeroBrevet", m_numeroBrevet);

    query.bindValue(":dateDepot", m_dateDepot);
    query.bindValue(":statutBrevet", m_statutBrevet);
    query.bindValue(":id", idPublication);

    if (!query.exec()) {
        if (err) *err = "Erreur modification publication : " + query.lastError().text();
        return false;
    }

    return true;
}

bool Publication::supprimer(const QString& idPublication, QString *err)
{
    QSqlQuery query;
    query.prepare("DELETE FROM PUBLICATIONS WHERE ID_PUBLICATION = :id");
    query.bindValue(":id", idPublication);

    if (!query.exec()) {
        if (err) *err = "Erreur suppression publication : " + query.lastError().text();
        return false;
    }

    return true;
}

bool Publication::chargerTout(QVector<Row> &out, QString *err)
{
    QSqlQuery query;
    if (!query.exec(
            "SELECT ID_PUBLICATION, TITRE, RESUME, INVENTEURS, DOMAINE_FABRICATION, "
            "TYPE_BREVET, NUMERO_BREVET, DATE_DEPOT, STATUT_BREVET, IDEMP "
            "FROM PUBLICATIONS "
            "ORDER BY ID_PUBLICATION ASC")) {
        if (err) *err = "Erreur chargement publications : " + query.lastError().text();
        return false;
    }

    out.clear();

    while (query.next()) {
        Row r;
        r.idPublication      = query.value(0).toString();
        r.titre              = query.value(1).toString();
        r.resume             = query.value(2).toString();
        r.inventeurs         = query.value(3).toString();
        r.domaineFabrication = query.value(4).toString();
        r.typeBrevet         = query.value(5).toString();
        r.numeroBrevet       = query.value(6).toInt();
        r.dateDepot          = query.value(7).toDate().toString("yyyy-MM-dd");
        r.statutBrevet       = query.value(8).toString();
        r.idEmp              = query.value(9).toString();
        out.push_back(r);
    }

    return true;
}
