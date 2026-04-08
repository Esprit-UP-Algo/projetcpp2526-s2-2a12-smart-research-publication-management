#include "employe.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QRegularExpression>
#include "session.h"

namespace {
const int kMotDePasseSeuilFort = 62; // aligné sur la barre « Fort » / « Très fort »
}

int Employe::motDePasseForcePourcent(const QString &password)
{
    if (password.isEmpty())
        return 0;

    int pts = 0;
    if (password.length() >= 6)
        pts += 1;
    if (password.length() >= 10)
        pts += 1;
    if (password.length() >= 14)
        pts += 1;
    static const QRegularExpression reLower(QStringLiteral("[a-z]"));
    static const QRegularExpression reUpper(QStringLiteral("[A-Z]"));
    static const QRegularExpression reDigit(QStringLiteral("[0-9]"));
    static const QRegularExpression reSpec(QStringLiteral("[^a-zA-Z0-9]"));
    if (password.contains(reLower))
        pts += 1;
    if (password.contains(reUpper))
        pts += 1;
    if (password.contains(reDigit))
        pts += 1;
    if (password.contains(reSpec))
        pts += 1;

    return qBound(0, pts * 13 + (password.length() >= 12 ? 8 : 0), 100);
}

bool Employe::motDePasseAcceptable(const QString &password)
{
    return motDePasseForcePourcent(password) >= kMotDePasseSeuilFort;
}

// Constructeur (Utilisation de std::move pour la performance)
Employe::Employe(
    QString cin, QString nom, QString prenom, QString username, QString passwordHash,
    QString email, QString poste, QString departement,
    QDate dateEmbauche, double salaire, QString role
    )
    : m_cin(std::move(cin)), m_nom(std::move(nom)), m_prenom(std::move(prenom)),
    m_username(std::move(username)), m_passwordHash(std::move(passwordHash)),
    m_email(std::move(email)), m_poste(std::move(poste)),
    m_departement(std::move(departement)), m_dateEmbauche(dateEmbauche),
    m_salaire(salaire), m_role(std::move(role))
{}

// Génération d'ID automatique (Oracle/SQLite style)
bool Employe::nextId(int &outId, QString *err)
{
    QSqlQuery query;
    if (!query.exec("SELECT NVL(MAX(ID_EMPLOYE), 0) + 1 FROM EMPLOYES")) {
        if (err) *err = query.lastError().text();
        return false;
    }
    if (query.next()) {
        outId = query.value(0).toInt();
        return true;
    }
    if (err) *err = "Impossible de générer l'ID";
    return false;
}

// CREATE : Ajouter un employé
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
        if (err) *err = "Échec de l'ajout : " + query.lastError().text();
        return false;
    }
    return true;
}

// UPDATE : Modifier un employé (Appelé via l'objet instance dans MainWindow)
bool Employe::modifier(const QString& idEmploye, QString *err)
{
    QSqlQuery query;
    query.prepare(
        "UPDATE EMPLOYES SET "
        "CIN = :cin, NOM = :nom, PRENOM = :prenom, USERNAME = :username, "
        "EMAIL = :email, POSTE = :poste, DEPARTEMENT = :departement, "
        "DATE_EMBAUCHE = :dateEmbauche, SALAIRE = :salaire, ROLE = :role "
        "WHERE ID_EMPLOYE = :id"
        );

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
bool Employe::supprimer(const QString& idEmploye, QString *err)
{
    QSqlQuery query;
    query.prepare("DELETE FROM EMPLOYES WHERE ID_EMPLOYE = :id");
    query.bindValue(":id", idEmploye);

    if (!query.exec()) {
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
        return false;
    }

    out.clear();
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
bool Employe::usernameExiste(const QString &username)
{
    QSqlQuery query;
    query.prepare("SELECT 1 FROM EMPLOYES WHERE USERNAME = :username");
    query.bindValue(":username", username);
    return query.exec() && query.next();
}

bool Employe::emailExiste(const QString &email, const QString &excludeIdEmploye)
{
    QSqlQuery query;
    const QString e = email.trimmed();
    if (e.isEmpty())
        return false;

    if (excludeIdEmploye.isEmpty()) {
        query.prepare(
            "SELECT 1 FROM EMPLOYES WHERE UPPER(TRIM(EMAIL)) = UPPER(TRIM(:email))");
    } else {
        query.prepare(
            "SELECT 1 FROM EMPLOYES WHERE UPPER(TRIM(EMAIL)) = UPPER(TRIM(:email)) "
            "AND TO_CHAR(ID_EMPLOYE) <> :id");
    }

    query.bindValue(":email", e);
    if (!excludeIdEmploye.isEmpty())
        query.bindValue(":id", excludeIdEmploye);

    return query.exec() && query.next();
}

//verifier si cin existant
// Dans employe.cpp
bool Employe::existe(const QString &cin, const QString &excludeId)
{
    QSqlQuery query;
    // Si excludeId est vide, on cherche partout.
    // Si excludeId n'est pas vide, on cherche partout SAUF pour cet ID (utile en MODIF)
    if (excludeId.isEmpty()) {
        query.prepare("SELECT CIN FROM EMPLOYES WHERE CIN = :cin");
    } else {
        query.prepare("SELECT CIN FROM EMPLOYES WHERE CIN = :cin AND CIN != :ex");
        query.bindValue(":ex", excludeId);
    }

    query.bindValue(":cin", cin);

    if (query.exec() && query.next()) {
        return true; // Le CIN existe déjà
    }
    return false; // Le CIN est libre
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
}
