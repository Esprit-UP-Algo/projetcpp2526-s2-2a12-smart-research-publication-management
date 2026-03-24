#include "projet.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>

static void setErr(QString *err, const QString& msg) { if (err) *err = msg; }

Projet::Projet(QString nom, QString description, QString objectifs,
               QDate dateDebut, QDate dateFinPrevue, QDate dateFinReelle,
               QString statut, QString priorite)
    : m_nom(std::move(nom)),
    m_description(std::move(description)),
    m_objectifs(std::move(objectifs)),
    m_statut(std::move(statut)),
    m_priorite(std::move(priorite)),
    m_dateDebut(dateDebut),
    m_dateFinPrevue(dateFinPrevue),
    m_dateFinReelle(dateFinReelle)
{}

bool Projet::nextId(int &outId, QString *err)
{
    QSqlQuery q;
    if (!q.exec("SELECT NVL(MAX(ID_PROJET),0)+1 FROM HICHEM.PROJETS")) {
        setErr(err, q.lastError().text());
        return false;
    }
    if (!q.next()) return false;
    outId = q.value(0).toInt();
    return true;
}

bool Projet::ajouter(int idemp, QString *err) const
{
    int newId = 0;
    if (!nextId(newId, err)) return false;

    QSqlQuery q;
    q.prepare(
        "INSERT INTO HICHEM.PROJETS "
        "(ID_PROJET, NOM_PROJET, DESCRIPTION, OBJECTIFS, DATE_DEBUT, "
        " DATE_FIN_PREVUE, DATE_FIN_REELLE, STATUT, PRIORITE, IDEMP) "
        "VALUES "
        "(:id, :nom, :desc, :obj, :dd, :dfp, :dfr, :statut, :prio, :idemp)"
        );

    q.bindValue(":id", newId);
    q.bindValue(":nom", m_nom);
    q.bindValue(":desc", m_description);
    q.bindValue(":obj", m_objectifs);
    q.bindValue(":dd", m_dateDebut);
    q.bindValue(":dfp", m_dateFinPrevue);

    // date fin réelle peut être NULL
    if (m_dateFinReelle.isValid())
        q.bindValue(":dfr", m_dateFinReelle);
    else
        q.bindValue(":dfr", QVariant(QVariant::Date));

    q.bindValue(":statut", m_statut);
    q.bindValue(":prio", m_priorite);
    q.bindValue(":idemp", idemp);

    if (!q.exec()) {
        setErr(err, q.lastError().text());
        return false;
    }
    return true;
}

bool Projet::modifier(const QString& id,
                      const QString& nom,
                      const QString& description,
                      const QString& objectifs,
                      const QDate& dateDebut,
                      const QDate& dateFinPrevue,
                      const QDate& dateFinReelle,
                      const QString& statut,
                      const QString& priorite,
                      QString *err)
{
    QSqlQuery q;
    q.prepare(
        "UPDATE HICHEM.PROJETS SET "
        "NOM_PROJET=:nom, DESCRIPTION=:desc, OBJECTIFS=:obj, "
        "DATE_DEBUT=:dd, DATE_FIN_PREVUE=:dfp, DATE_FIN_REELLE=:dfr, "
        "STATUT=:statut, PRIORITE=:prio "
        "WHERE ID_PROJET=:id"
        );

    q.bindValue(":nom", nom);
    q.bindValue(":desc", description);
    q.bindValue(":obj", objectifs);
    q.bindValue(":dd", dateDebut);
    q.bindValue(":dfp", dateFinPrevue);

    if (dateFinReelle.isValid())
        q.bindValue(":dfr", dateFinReelle);
    else
        q.bindValue(":dfr", QVariant(QVariant::Date));

    q.bindValue(":statut", statut);
    q.bindValue(":prio", priorite);
    q.bindValue(":id", id);

    if (!q.exec()) {
        setErr(err, q.lastError().text());
        return false;
    }
    return true;
}

bool Projet::supprimer(const QString& id, QString *err)
{
    QSqlQuery q;
    q.prepare("DELETE FROM HICHEM.PROJETS WHERE ID_PROJET=:id");
    q.bindValue(":id", id);

    if (!q.exec()) {
        setErr(err, q.lastError().text());
        return false;
    }
    return true;
}

bool Projet::chargerTout(QVector<Row>& out, QString *err)
{
    out.clear();
    QSqlQuery q;
    q.prepare(
        "SELECT ID_PROJET, NOM_PROJET, DESCRIPTION, OBJECTIFS, "
        "TO_CHAR(DATE_DEBUT,'YYYY-MM-DD'), "
        "TO_CHAR(DATE_FIN_PREVUE,'YYYY-MM-DD'), "
        "TO_CHAR(DATE_FIN_REELLE,'YYYY-MM-DD'), "
        "STATUT, PRIORITE, IDEMP "
        "FROM HICHEM.PROJETS "
        "ORDER BY ID_PROJET DESC"
        );

    if (!q.exec()) {
        setErr(err, q.lastError().text());
        return false;
    }

    while (q.next()) {
        Row r;
        r.id = q.value(0).toString();
        r.nom = q.value(1).toString();
        r.description = q.value(2).toString();
        r.objectifs = q.value(3).toString();
        r.dateDebut = q.value(4).toString();
        r.dateFinPrevue = q.value(5).toString();
        r.dateFinReelle = q.value(6).toString();
        r.statut = q.value(7).toString();
        r.priorite = q.value(8).toString();
        r.idemp = q.value(9).toInt();
        out.push_back(r);
    }
    return true;
}
