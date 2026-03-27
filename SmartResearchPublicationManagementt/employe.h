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
    // Structure pour le transfert de données vers l'UI (Tableau)
    struct Row {
        QString idEmploye;
        QString cin;
        QString nom;
        QString prenom;
        QString username;
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
};

#endif // EMPLOYE_H
