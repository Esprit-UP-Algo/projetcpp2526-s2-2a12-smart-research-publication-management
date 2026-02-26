#include "employe.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

Employe::Employe(
    QString cin, QString nom, QString prenom, QString username, QString passwordHash,
    QString email, QString poste, QString departement,
    QDate dateEmbauche, double salaire, QString role,
    QString typeDemande, QDate dateDebut, QDate dateFin,
    QString description, QDate dateDemande, QString statutDemande,
    QString commentaireRH, QDate datePointage,
    QString heureArrivee, QString heureDepart, QString statutJournalier
    )
    : m_cin(std::move(cin)), m_nom(std::move(nom)), m_prenom(std::move(prenom)),
    m_username(std::move(username)), m_passwordHash(std::move(passwordHash)),
    m_email(std::move(email)), m_poste(std::move(poste)),
    m_departement(std::move(departement)), m_dateEmbauche(dateEmbauche),
    m_salaire(salaire), m_role(std::move(role)),
    m_typeDemande(std::move(typeDemande)), m_dateDebut(dateDebut),
    m_dateFin(dateFin), m_description(std::move(description)),
    m_dateDemande(dateDemande), m_statutDemande(std::move(statutDemande)),
    m_commentaireRH(std::move(commentaireRH)), m_datePointage(datePointage),
    m_heureArrivee(std::move(heureArrivee)), m_heureDepart(std::move(heureDepart)),
    m_statutJournalier(std::move(statutJournalier))
{}

bool Employe::nextId(int &outId, QString *err)
{
    QSqlQuery query;
    if (!query.exec("SELECT NVL(MAX(ID_EMPLOYE), 0) + 1 FROM EMPLOYES")) {
        QString error = query.lastError().text();
        if (err) *err = error;
        return false;
    }
    if (query.next()) {
        outId = query.value(0).toInt();
        return true;
    }
    if (err) *err = "Impossible de générer l'ID";
    return false;
}

bool Employe::ajouter(QString *err) const
{
    int id;
    if (!nextId(id, err)) return false;

    QSqlQuery query;
    query.prepare(
        "INSERT INTO EMPLOYES ("
        "ID_EMPLOYE, CIN, NOM, PRENOM, USERNAME, PASSWORD_HASH, EMAIL, "
        "POSTE, DEPARTEMENT, DATE_EMBAUCHE, SALAIRE, ROLE"
        ") VALUES ("
        ":id, :cin, :nom, :prenom, :username, :passwordHash, :email, "
        ":poste, :departement, :dateEmbauche, :salaire, :role)"
        );

    query.bindValue(":id",           id);
    query.bindValue(":cin",          m_cin);
    query.bindValue(":nom",          m_nom);
    query.bindValue(":prenom",       m_prenom);
    query.bindValue(":username",     m_username);
    query.bindValue(":passwordHash", m_passwordHash);
    query.bindValue(":email",        m_email);
    query.bindValue(":poste",        m_poste);
    query.bindValue(":departement",  m_departement);
    query.bindValue(":dateEmbauche", m_dateEmbauche);
    query.bindValue(":salaire",      m_salaire);
    query.bindValue(":role",         m_role);

    if (!query.exec()) {
        QString error = query.lastError().text();
        if (err) *err = "Échec de l'ajout : " + error;
        return false;
    }

    return true;
}

bool Employe::modifier(
    const QString& idEmploye,
    const QString& cin,
    const QString& nom,
    const QString& prenom,
    const QString& username,
    const QString& email,
    const QString& poste,
    const QString& departement,
    const QDate&   dateEmbauche,
    double         salaire,
    const QString& role,
    QString       *err)
{
    QSqlQuery query;
    query.prepare(
        "UPDATE EMPLOYES SET "
        "CIN = :cin, NOM = :nom, PRENOM = :prenom, USERNAME = :username, "
        "EMAIL = :email, POSTE = :poste, DEPARTEMENT = :departement, "
        "DATE_EMBAUCHE = :dateEmbauche, SALAIRE = :salaire, ROLE = :role "
        "WHERE ID_EMPLOYE = :id"
        );

    query.bindValue(":cin",          cin);
    query.bindValue(":nom",          nom);
    query.bindValue(":prenom",       prenom);
    query.bindValue(":username",     username);
    query.bindValue(":email",        email);
    query.bindValue(":poste",        poste);
    query.bindValue(":departement",  departement);
    query.bindValue(":dateEmbauche", dateEmbauche);
    query.bindValue(":salaire",      salaire);
    query.bindValue(":role",         role);
    query.bindValue(":id",           idEmploye);

    if (!query.exec()) {
        QString error = query.lastError().text();
        if (err) *err = "Échec modification : " + error;
        return false;
    }

    if (query.numRowsAffected() == 0) {
        if (err) *err = "Aucun employé trouvé";
        return false;
    }

    return true;
}

bool Employe::supprimer(const QString& idEmploye, QString *err)
{
    QSqlQuery query;
    query.prepare("DELETE FROM EMPLOYES WHERE ID_EMPLOYE = :id");
    query.bindValue(":id", idEmploye);

    if (!query.exec()) {
        QString error = query.lastError().text();
        if (err) *err = "Échec suppression : " + error;
        return false;
    }

    if (query.numRowsAffected() == 0) {
        if (err) *err = "Aucun employé trouvé";
        return false;
    }

    return true;
}

bool Employe::chargerTout(QVector<Row> &out, QString *err)
{
    QSqlQuery query;
    if (!query.exec(
            "SELECT ID_EMPLOYE, CIN, NOM, PRENOM, USERNAME, EMAIL, "
            "POSTE, DEPARTEMENT, DATE_EMBAUCHE, SALAIRE, ROLE "
            "FROM EMPLOYES ORDER BY ID_EMPLOYE ASC"
            )) {
        QString error = query.lastError().text();
        if (err) *err = "Impossible de charger : " + error;
        return false;
    }

    out.clear();

    while (query.next()) {
        Row r;
        r.idEmploye    = query.value("ID_EMPLOYE").toString();
        r.cin          = query.value("CIN").toString();
        r.nom          = query.value("NOM").toString();
        r.prenom       = query.value("PRENOM").toString();
        r.username     = query.value("USERNAME").toString();
        r.email        = query.value("EMAIL").toString();
        r.poste        = query.value("POSTE").toString();
        r.departement  = query.value("DEPARTEMENT").toString();
        r.dateEmbauche = query.value("DATE_EMBAUCHE").toDate().toString("yyyy-MM-dd");
        r.salaire      = query.value("SALAIRE").toDouble();
        r.role         = query.value("ROLE").toString();

        out.append(r);
    }

    return true;
}

bool Employe::usernameExiste(const QString &username)
{
    QSqlQuery query;
    query.prepare("SELECT 1 FROM EMPLOYES WHERE USERNAME = :username");
    query.bindValue(":username", username);

    if (!query.exec()) return false;
    return query.next();
}
