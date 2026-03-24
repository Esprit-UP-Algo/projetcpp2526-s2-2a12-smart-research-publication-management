#ifndef EMPLOYE_H
#define EMPLOYE_H

#include <QString>
#include <QDate>
#include <QVector>
<<<<<<< HEAD:SmartResearchPublicationManagementt_V4/employe.h
#include <QSqlQuery>
#include <QSqlError>
=======
>>>>>>> 9fd98e05953d86978b42c6fda2f7a3b994435af5:SmartResearchPublicationManagement_V003/employe.h

class Employe
{
public:
<<<<<<< HEAD:SmartResearchPublicationManagementt_V4/employe.h
    // Structure pour le transfert de données vers l'UI (Tableau)
=======
>>>>>>> 9fd98e05953d86978b42c6fda2f7a3b994435af5:SmartResearchPublicationManagement_V003/employe.h
    struct Row {
        QString idEmploye;
        QString cin;
        QString nom;
        QString prenom;
        QString username;
<<<<<<< HEAD:SmartResearchPublicationManagementt_V4/employe.h
        QString email;
        QString poste;
        QString departement;
        QString dateEmbauche;  // Formaté en "yyyy-MM-dd"
        double  salaire = 0.0;
        QString role;          // ADMIN, RH, EMPLOYE
    };

    // Constructeurs
    Employe() = default;

    // Constructeur principal pour le CRUD (Ajout/Modification)
=======
        QString passwordHash;
        QString email;
        QString poste;
        QString departement;
        QString dateEmbauche;     // "yyyy-MM-dd"
        double  salaire = 0.0;
        QString role;

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

>>>>>>> 9fd98e05953d86978b42c6fda2f7a3b994435af5:SmartResearchPublicationManagement_V003/employe.h
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
<<<<<<< HEAD:SmartResearchPublicationManagementt_V4/employe.h
        QString role
        );

    // ──── AUTHENTIFICATION ────
    static bool authentifier(const QString &username, const QString &passwordHash, QString *err = nullptr);
    static bool authentifierFaceID(const QString &username, QString *err = nullptr);

    // ──── CRUD (BASE DE DONNÉES) ────

    // Create
    bool ajouter(QString *err = nullptr) const;

    // Update : Modifie l'employé identifié par 'idEmploye' avec les données de l'instance
    bool modifier(const QString& idEmploye, QString *err = nullptr);

    // Delete
    static bool supprimer(const QString& idEmploye, QString *err = nullptr);

    // Read
    static bool chargerTout(QVector<Row> &out, QString *err = nullptr);

    // Utilitaires
    static bool usernameExiste(const QString &username);

private:
    // Générateur d'ID interne
    static bool nextId(int &outId, QString *err = nullptr);

    // Membres de données
=======
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
        double         salaire,
        const QString& role,
        QString       *err = nullptr
        );

    static bool supprimer(const QString& idEmploye, QString *err = nullptr);

    static bool chargerTout(QVector<Row> &out, QString *err = nullptr);

    static bool usernameExiste(const QString &username);

private:
    static bool nextId(int &outId, QString *err = nullptr);

>>>>>>> 9fd98e05953d86978b42c6fda2f7a3b994435af5:SmartResearchPublicationManagement_V003/employe.h
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
<<<<<<< HEAD:SmartResearchPublicationManagementt_V4/employe.h
=======

    QString m_typeDemande;
    QDate   m_dateDebut;
    QDate   m_dateFin;
    QString m_description;
    QDate   m_dateDemande;
    QString m_statutDemande;
    QString m_commentaireRH;

    QDate   m_datePointage;
    QString m_heureArrivee;
    QString m_heureDepart;
    QString m_statutJournalier;
>>>>>>> 9fd98e05953d86978b42c6fda2f7a3b994435af5:SmartResearchPublicationManagement_V003/employe.h
};

#endif // EMPLOYE_H
