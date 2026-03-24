#include "employe.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
<<<<<<< HEAD:SmartResearchPublicationManagementt_V4/employe.cpp
#include "session.h"

// Constructeur (Utilisation de std::move pour la performance)
Employe::Employe(
    QString cin, QString nom, QString prenom, QString username, QString passwordHash,
    QString email, QString poste, QString departement,
    QDate dateEmbauche, double salaire, QString role
=======

Employe::Employe(
    QString cin, QString nom, QString prenom, QString username, QString passwordHash,
    QString email, QString poste, QString departement,
    QDate dateEmbauche, double salaire, QString role,
    QString typeDemande, QDate dateDebut, QDate dateFin,
    QString description, QDate dateDemande, QString statutDemande,
    QString commentaireRH, QDate datePointage,
    QString heureArrivee, QString heureDepart, QString statutJournalier
>>>>>>> 9fd98e05953d86978b42c6fda2f7a3b994435af5:SmartResearchPublicationManagement_V003/employe.cpp
    )
    : m_cin(std::move(cin)), m_nom(std::move(nom)), m_prenom(std::move(prenom)),
    m_username(std::move(username)), m_passwordHash(std::move(passwordHash)),
    m_email(std::move(email)), m_poste(std::move(poste)),
    m_departement(std::move(departement)), m_dateEmbauche(dateEmbauche),
<<<<<<< HEAD:SmartResearchPublicationManagementt_V4/employe.cpp
    m_salaire(salaire), m_role(std::move(role))
{}

// Génération d'ID automatique (Oracle/SQLite style)
=======
    m_salaire(salaire), m_role(std::move(role)),
    m_typeDemande(std::move(typeDemande)), m_dateDebut(dateDebut),
    m_dateFin(dateFin), m_description(std::move(description)),
    m_dateDemande(dateDemande), m_statutDemande(std::move(statutDemande)),
    m_commentaireRH(std::move(commentaireRH)), m_datePointage(datePointage),
    m_heureArrivee(std::move(heureArrivee)), m_heureDepart(std::move(heureDepart)),
    m_statutJournalier(std::move(statutJournalier))
{}

>>>>>>> 9fd98e05953d86978b42c6fda2f7a3b994435af5:SmartResearchPublicationManagement_V003/employe.cpp
bool Employe::nextId(int &outId, QString *err)
{
    QSqlQuery query;
    if (!query.exec("SELECT NVL(MAX(ID_EMPLOYE), 0) + 1 FROM EMPLOYES")) {
<<<<<<< HEAD:SmartResearchPublicationManagementt_V4/employe.cpp
        if (err) *err = query.lastError().text();
=======
        QString error = query.lastError().text();
        if (err) *err = error;
>>>>>>> 9fd98e05953d86978b42c6fda2f7a3b994435af5:SmartResearchPublicationManagement_V003/employe.cpp
        return false;
    }
    if (query.next()) {
        outId = query.value(0).toInt();
        return true;
    }
    if (err) *err = "Impossible de générer l'ID";
    return false;
}

<<<<<<< HEAD:SmartResearchPublicationManagementt_V4/employe.cpp
// CREATE : Ajouter un employé
=======
>>>>>>> 9fd98e05953d86978b42c6fda2f7a3b994435af5:SmartResearchPublicationManagement_V003/employe.cpp
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
<<<<<<< HEAD:SmartResearchPublicationManagementt_V4/employe.cpp
        if (err) *err = "Échec de l'ajout : " + query.lastError().text();
        return false;
    }
    return true;
}

// UPDATE : Modifier un employé (Appelé via l'objet instance dans MainWindow)
bool Employe::modifier(const QString& idEmploye, QString *err)
=======
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
>>>>>>> 9fd98e05953d86978b42c6fda2f7a3b994435af5:SmartResearchPublicationManagement_V003/employe.cpp
{
    QSqlQuery query;
    query.prepare(
        "UPDATE EMPLOYES SET "
        "CIN = :cin, NOM = :nom, PRENOM = :prenom, USERNAME = :username, "
        "EMAIL = :email, POSTE = :poste, DEPARTEMENT = :departement, "
        "DATE_EMBAUCHE = :dateEmbauche, SALAIRE = :salaire, ROLE = :role "
        "WHERE ID_EMPLOYE = :id"
        );

<<<<<<< HEAD:SmartResearchPublicationManagementt_V4/employe.cpp
    query.bindValue(":cin",          m_cin);
    query.bindValue(":nom",          m_nom);
    query.bindValue(":prenom",       m_prenom);
    query.bindValue(":username",     m_username);
    query.bindValue(":email",        m_email);
    query.bindValue(":poste",        m_poste);
    query.bindValue(":departement",  m_departement);
    query.bindValue(":dateEmbauche", m_dateEmbauche);
    query.bindValue(":salaire",      m_salaire);
    query.bindValue(":role",         m_role);
    query.bindValue(":id",           idEmploye);

    if (!query.exec()) {
        if (err) *err = "Échec modification SQL : " + query.lastError().text();
        return false;
    }
    return true;
}

// DELETE : Supprimer un employé
=======
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

>>>>>>> 9fd98e05953d86978b42c6fda2f7a3b994435af5:SmartResearchPublicationManagement_V003/employe.cpp
bool Employe::supprimer(const QString& idEmploye, QString *err)
{
    QSqlQuery query;
    query.prepare("DELETE FROM EMPLOYES WHERE ID_EMPLOYE = :id");
    query.bindValue(":id", idEmploye);

    if (!query.exec()) {
<<<<<<< HEAD:SmartResearchPublicationManagementt_V4/employe.cpp
        if (err) *err = "Échec suppression : " + query.lastError().text();
        return false;
    }
    return true;
}

// READ : Charger la liste complète
bool Employe::chargerTout(QVector<Row> &out, QString *err)
{
    QSqlQuery query;
    if (!query.exec("SELECT ID_EMPLOYE, CIN, NOM, PRENOM, USERNAME, EMAIL, "
                    "POSTE, DEPARTEMENT, DATE_EMBAUCHE, SALAIRE, ROLE "
                    "FROM EMPLOYES ORDER BY ID_EMPLOYE ASC")) {
        if (err) *err = "Impossible de charger : " + query.lastError().text();
=======
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
>>>>>>> 9fd98e05953d86978b42c6fda2f7a3b994435af5:SmartResearchPublicationManagement_V003/employe.cpp
        return false;
    }

    out.clear();
<<<<<<< HEAD:SmartResearchPublicationManagementt_V4/employe.cpp
    while (query.next()) {
        Row r;
        r.idEmploye    = query.value(0).toString();
        r.cin          = query.value(1).toString();
        r.nom          = query.value(2).toString();
        r.prenom       = query.value(3).toString();
        r.username     = query.value(4).toString();
        r.email        = query.value(5).toString();
        r.poste        = query.value(6).toString();
        r.departement  = query.value(7).toString();
        r.dateEmbauche = query.value(8).toDate().toString("yyyy-MM-dd");
        r.salaire      = query.value(9).toDouble();
        r.role         = query.value(10).toString();
        out.append(r);
    }
    return true;
}

// Vérifier si un username est déjà pris
=======

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

>>>>>>> 9fd98e05953d86978b42c6fda2f7a3b994435af5:SmartResearchPublicationManagement_V003/employe.cpp
bool Employe::usernameExiste(const QString &username)
{
    QSqlQuery query;
    query.prepare("SELECT 1 FROM EMPLOYES WHERE USERNAME = :username");
    query.bindValue(":username", username);
<<<<<<< HEAD:SmartResearchPublicationManagementt_V4/employe.cpp
    return query.exec() && query.next();
}

// Authentification classique (Login)
bool Employe::authentifier(const QString &username, const QString &passwordHash, QString *err)
{
    QSqlQuery query;
    query.prepare("SELECT ID_EMPLOYE, NOM, PRENOM, ROLE FROM EMPLOYES "
                  "WHERE USERNAME = :user AND PASSWORD_HASH = :pass");
    query.bindValue(":user", username);
    query.bindValue(":pass", passwordHash);

    if (!query.exec()) {
        if (err) *err = "Erreur SQL : " + query.lastError().text();
        return false;
    }

    if (query.next()) {
        QString id = query.value("ID_EMPLOYE").toString();
        QString nomComplet = query.value("NOM").toString() + " " + query.value("PRENOM").toString();
        QString role = query.value("ROLE").toString();

        Session::instance().login(id, nomComplet, role);
        return true;
    }

    if (err) *err = "Nom d'utilisateur ou mot de passe incorrect.";
    return false;
}

// Authentification FaceID
bool Employe::authentifierFaceID(const QString &username, QString *err)
{
    QSqlQuery query;
    query.prepare("SELECT ID_EMPLOYE, NOM, PRENOM, ROLE FROM EMPLOYES WHERE USERNAME = :user");
    query.bindValue(":user", username);

    if (!query.exec()) {
        if (err) *err = "Erreur SQL : " + query.lastError().text();
        return false;
    }

    if (query.next()) {
        QString id = query.value("ID_EMPLOYE").toString();
        QString nomComplet = query.value("NOM").toString() + " " + query.value("PRENOM").toString();
        QString role = query.value("ROLE").toString();

        Session::instance().login(id, nomComplet, role);
        return true;
    }

    if (err) *err = "Utilisateur reconnu par FaceID mais introuvable en base.";
    return false;
=======

    if (!query.exec()) return false;
    return query.next();
>>>>>>> 9fd98e05953d86978b42c6fda2f7a3b994435af5:SmartResearchPublicationManagement_V003/employe.cpp
}
