#ifndef EMPLOYE_H
#define EMPLOYE_H

#include <QString>
#include <QDate>
#include <QVector>
#include <QSqlQuery>
#include <QSqlError>

class Employe
{
public:
    struct Row {
        QString idEmploye;
        QString cin;
        QString nom;
        QString prenom;
        QString username;
        QString passwordHash;
        QString email;
        QString poste;
        QString departement;
        QString dateEmbauche;     // "yyyy-MM-dd"
        double  salaire = 0.0;
        QString role;             // ADMIN, RH, EMPLOYE

        // ──── Partie demande (optionnelle) ────
        QString typeDemande;
        QString dateDebut;
        QString dateFin;
        QString description;
        QString dateDemande;
        QString statutDemande;
        QString commentaireRH;

        // ──── Partie pointage (optionnelle) ────
        QString datePointage;
        QString heureArrivee;
        QString heureDepart;
        QString statutJournalier;
    };

    Employe() = default;

    Employe(
        QString cin,
        QString nom,
        QString prenom,
        QString username,
        QString passwordHash,
        QString email,
        QString poste,
        QString departement,
        QDate   dateEmbauche,
        double  salaire,
        QString role,
        QString typeDemande    = "",
        QDate   dateDebut      = QDate(),
        QDate   dateFin        = QDate(),
        QString description    = "",
        QDate   dateDemande    = QDate(),
        QString statutDemande  = "",
        QString commentaireRH  = "aucun",
        QDate   datePointage   = QDate(),
        QString heureArrivee   = "",
        QString heureDepart    = "",
        QString statutJournalier = ""
        );

    // ──── GESTION DES RÔLES ET AUTHENTIFICATION ────

    // Méthode classique (Username + Password)
    static bool authentifier(const QString &username, const QString &passwordHash, QString *err = nullptr);

    // AJOUT : Méthode FaceID (Username uniquement après validation visuelle)
    // Elle doit remplir Session::instance() comme la méthode classique
static bool authentifierFaceID(const QString &username, QString *err = nullptr);    // ──── CRUD ET BASE DE DONNÉES ────

    bool ajouter(QString *err = nullptr) const;

    static bool modifier(
        const QString& idEmploye,
        const QString& cin,
        const QString& nom,
        const QString& prenom,
        const QString& username,
        const QString& email,
        const QString& poste,
        const QString& departement,
        const QDate&   dateEmbauche,
        double          salaire,
        const QString& role,
        QString       *err = nullptr
        );

    static bool supprimer(const QString& idEmploye, QString *err = nullptr);
    static bool chargerTout(QVector<Row> &out, QString *err = nullptr);
    static bool usernameExiste(const QString &username);

private:
    static bool nextId(int &outId, QString *err = nullptr);

    // Attributs principaux
    QString m_cin;
    QString m_nom;
    QString m_prenom;
    QString m_username;
    QString m_passwordHash;
    QString m_email;
    QString m_poste;
    QString m_departement;
    QDate   m_dateEmbauche;
    double  m_salaire = 0.0;
    QString m_role;

    // Attributs Demande
    QString m_typeDemande;
    QDate   m_dateDebut;
    QDate   m_dateFin;
    QString m_description;
    QDate   m_dateDemande;
    QString m_statutDemande;
    QString m_commentaireRH;

    // Attributs Pointage
    QDate   m_datePointage;
    QString m_heureArrivee;
    QString m_heureDepart;
    QString m_statutJournalier;
};

#endif // EMPLOYE_H
