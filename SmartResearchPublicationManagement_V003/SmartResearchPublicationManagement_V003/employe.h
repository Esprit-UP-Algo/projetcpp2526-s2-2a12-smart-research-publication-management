#ifndef EMPLOYE_H
#define EMPLOYE_H

#include <QString>
#include <QDate>
#include <QVector>

/**
 * @brief Classe représentant un employé avec ses informations principales,
 *        ses demandes et ses pointages.
 */
class Employe
{
public:

    /**
     * @brief Structure représentant une ligne complète d'employé (pour chargerTout)
     */
    struct Row {
        QString idEmploye;        // ID_EMPLOYE (clé primaire)
        QString cin;
        QString nom;
        QString prenom;
        QString username;
        QString passwordHash;     // Hash du mot de passe (SHA256 recommandé)
        QString email;
        QString poste;
        QString departement;
        QString typeContrat;
        QString dateEmbauche;     // Format "yyyy-MM-dd"
        double  salaire = 0.0;
        QString role;

        // ──── Partie demande (optionnelle) ────
        QString typeDemande;
        QString dateDebut;        // "yyyy-MM-dd"
        QString dateFin;          // "yyyy-MM-dd"
        QString description;
        QString dateDemande;      // "yyyy-MM-dd"
        QString statutDemande;
        QString commentaireRH;

        // ──── Partie pointage (optionnelle) ────
        QString datePointage;     // "yyyy-MM-dd"
        QString heureArrivee;     // "HH:mm"
        QString heureDepart;      // "HH:mm"
        QString statutJournalier;
    };

    Employe() = default;

    /**
     * @brief Constructeur complet avec valeurs par défaut pour les parties demande/pointage
     */
    Employe(QString cin,
            QString nom,
            QString prenom,
            QString username,
            QString passwordHash,
            QString email,
            QString poste,
            QString departement,
            QString typeContrat,
            QDate dateEmbauche,
            double salaire,
            QString role,
            QString typeDemande = "",
            QDate dateDebut = QDate(),
            QDate dateFin = QDate(),
            QString description = "",
            QDate dateDemande = QDate(),
            QString statutDemande = "",
            QString commentaireRH = "aucun",
            QDate datePointage = QDate(),
            QString heureArrivee = "",
            QString heureDepart = "",
            QString statutJournalier = "")
        : m_cin(std::move(cin)),
        m_nom(std::move(nom)),
        m_prenom(std::move(prenom)),
        m_username(std::move(username)),
        m_passwordHash(std::move(passwordHash)),
        m_email(std::move(email)),
        m_poste(std::move(poste)),
        m_departement(std::move(departement)),
        m_typeContrat(std::move(typeContrat)),
        m_dateEmbauche(dateEmbauche),
        m_salaire(salaire),
        m_role(std::move(role)),
        m_typeDemande(std::move(typeDemande)),
        m_dateDebut(dateDebut),
        m_dateFin(dateFin),
        m_description(std::move(description)),
        m_dateDemande(dateDemande),
        m_statutDemande(std::move(statutDemande)),
        m_commentaireRH(std::move(commentaireRH)),
        m_datePointage(datePointage),
        m_heureArrivee(std::move(heureArrivee)),
        m_heureDepart(std::move(heureDepart)),
        m_statutJournalier(std::move(statutJournalier))
    {}

    // ==================== CRUD ====================

    /**
     * @brief Ajoute l'employé actuel dans la base de données
     * @param err Message d'erreur en cas d'échec (optionnel)
     * @return true si l'ajout a réussi
     */
    bool ajouter(QString *err = nullptr) const;

    /**
     * @brief Modifie un employé existant dans la base
     * @param idEmploye ID de l'employé à modifier
     * @param ... nouveaux champs
     * @param err Message d'erreur en cas d'échec (optionnel)
     * @return true si la modification a réussi
     */
    static bool modifier(const QString& idEmploye,
                         const QString& cin,
                         const QString& nom,
                         const QString& prenom,
                         const QString& username,
                         const QString& email,
                         const QString& poste,
                         const QString& departement,
                         const QString& typeContrat,
                         const QDate& dateEmbauche,
                         double salaire,
                         const QString& role,
                         QString *err = nullptr);

    /**
     * @brief Supprime un employé par son ID
     * @param idEmploye ID de l'employé à supprimer
     * @param err Message d'erreur en cas d'échec (optionnel)
     * @return true si la suppression a réussi
     */
    static bool supprimer(const QString& idEmploye, QString *err = nullptr);


    /**
     * @brief Charge tous les employés de la base dans un QVector<Row>
     * @param out Vecteur rempli avec les lignes
     * @param err Message d'erreur en cas d'échec (optionnel)
     * @return true si le chargement a réussi
     */
    static bool chargerTout(QVector<Row> &out, QString *err = nullptr);
    static bool usernameExiste(const QString &username);

private:
    /**
     * @brief Génère le prochain ID (MAX + 1)
     * @param outId [out] Le prochain ID
     * @param err Message d'erreur en cas d'échec (optionnel)
     * @return true si l'ID a été généré correctement
     */
    static bool nextId(int &outId, QString *err = nullptr);

    // Membres de l'instance (données de base de l'employé)
    QString m_cin;
    QString m_nom;
    QString m_prenom;
    QString m_username;
    QString m_passwordHash;
    QString m_email;
    QString m_poste;
    QString m_departement;
    QString m_typeContrat;
    QDate   m_dateEmbauche;
    double  m_salaire = 0.0;
    QString m_role;

    // Données demande (optionnelles)
    QString m_typeDemande;
    QDate   m_dateDebut;
    QDate   m_dateFin;
    QString m_description;
    QDate   m_dateDemande;
    QString m_statutDemande;
    QString m_commentaireRH;

    // Données pointage (optionnelles)
    QDate   m_datePointage;
    QString m_heureArrivee;
    QString m_heureDepart;
    QString m_statutJournalier;
};

#endif // EMPLOYE_H
