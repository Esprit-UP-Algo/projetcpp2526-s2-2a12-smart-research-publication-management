// labs.h
#ifndef LABS_H
#define LABS_H

#include <QString>
#include <QVector>

class Labs
{
public:
    struct Row {
        QString id;              // IDLABO
        QString nomlabo;         // NOMLABO
        QString responsable;     // RESPONSABLE
        QString numero;          // NUMERO
        QString localisation;    // LOCALISATION
        QString disponibilite;   // DISPONIBILITE
        QString specialite;      // SPECIALITE
        QString resultat;        // RESULTAT
        QString paiement;        // PAIEMENT
    };

    Labs() = default;

    // Constructeur pour l'ajout
    Labs(const QString& nomlabo,
         const QString& responsable,
         const QString& numero,
         const QString& localisation,
         const QString& specialite,
         const QString& disponibilite,
         const QString& resultat,
         const QString& paiement,
         const QString& idemp = "6");

    // Getters
    QString getId() const { return m_id; }
    QString getNomlabo() const { return m_nomlabo; }
    QString getResponsable() const { return m_responsable; }
    QString getNumero() const { return m_numero; }
    QString getLocalisation() const { return m_localisation; }
    QString getSpecialite() const { return m_specialite; }
    QString getDisponibilite() const { return m_disponibilite; }
    QString getResultat() const { return m_resultat; }
    QString getPaiement() const { return m_paiement; }

    // CRUD
    bool ajouter(QString *err = nullptr) const;

    static bool modifier(const QString& idLabo,
                         const QString& nomlabo,
                         const QString& responsable,
                         const QString& numero,
                         const QString& localisation,
                         const QString& specialite,
                         const QString& disponibilite,
                         const QString& resultat,
                         const QString& paiement,
                         QString *err = nullptr);

    static bool supprimer(const QString& idLabo, QString *err = nullptr);
    static bool chargerTout(QVector<Row> &out, QString *err = nullptr);
    static bool getById(const QString& idLabo, Row &outRow, QString *err = nullptr);
    static QString getNextId(QString *err = nullptr);

private:
    static bool nextId(int &outId, QString *err = nullptr);

    QString m_id;
    QString m_nomlabo;
    QString m_responsable;
    QString m_numero;
    QString m_localisation;
    QString m_specialite;
    QString m_disponibilite;
    QString m_resultat;
    QString m_paiement;
    QString m_idemp;
};

#endif // LABS_H
