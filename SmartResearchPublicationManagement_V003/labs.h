#ifndef LABS_H
#define LABS_H

#include <QString>
#include <QVector>
#include <utility>

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
        QString qrlabs;          // QRLABS
    };

    Labs() = default;

    Labs(QString nomlabo,
         QString responsable,
         QString numero,
         QString localisation,
         QString specialite,
         QString disponibilite,
         QString resultat,
         QString qrlabs,
         QString IDEMP)
        : m_nomlabo(std::move(nomlabo)),
        m_responsable(std::move(responsable)),
        m_numero(std::move(numero)),
        m_localisation(std::move(localisation)),
        m_specialite(std::move(specialite)),
        m_disponibilite(std::move(disponibilite)),
        m_resultat(std::move(resultat)),
        m_qrlabs(std::move(qrlabs)),
        m_IDEMP(std::move(IDEMP))
    {}

    bool ajouter(QString *err = nullptr) const;

    static bool modifier(const QString& idLabo,
                         const QString& nomlabo,
                         const QString& responsable,
                         const QString& numero,
                         const QString& localisation,
                         const QString& specialite,
                         const QString& disponibilite,
                         const QString& resultat,
                         const QString& qrlabs,
                         QString *err = nullptr);

    static bool supprimer(const QString& idLabo, QString *err = nullptr);
    static bool chargerTout(QVector<Row> &out, QString *err = nullptr);

private:
    static bool nextId(int &outId, QString *err = nullptr);

    QString m_nomlabo;
    QString m_responsable;
    QString m_numero;
    QString m_localisation;
    QString m_specialite;
    QString m_disponibilite;
    QString m_resultat;
    QString m_qrlabs;
    QString m_IDEMP;
};

#endif // LABS_H
