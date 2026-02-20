#ifndef PUBLICATION_H
#define PUBLICATION_H

#include <QString>
#include <QDate>
#include <QVector>
#include <utility>

class Publication
{
public:
    struct Row {
        QString id;                 // ID_PUBLICATION
        QString titre;
        QString resume;
        QString inventeurs;
        QString domaineFabrication;
        QString typeBrevet;
        QString numeroBrevet;
        QString dateDepot;          // "YYYY-MM-DD"
        QString statutBrevet;
    };

    Publication() = default;

    Publication(QString titre,
                QString resume,
                QString inventeurs,
                QString domaineFabrication,
                QString typeBrevet,
                int numeroBrevet,
                QDate dateDepot,
                QString statutBrevet)
        : m_titre(std::move(titre)),
        m_resume(std::move(resume)),
        m_inventeurs(std::move(inventeurs)),
        m_domaineFabrication(std::move(domaineFabrication)),
        m_typeBrevet(std::move(typeBrevet)),
        m_numeroBrevet(numeroBrevet),
        m_dateDepot(dateDepot),
        m_statutBrevet(std::move(statutBrevet))
    {}

    // CRUD
    bool ajouter(QString *err = nullptr) const;

    static bool modifier(const QString& idPublication,
                         const QString& titre,
                         const QString& resume,
                         const QString& inventeurs,
                         const QString& domaineFabrication,
                         const QString& typeBrevet,
                         int numeroBrevet,
                         const QDate& dateDepot,
                         const QString& statutBrevet,
                         QString *err = nullptr);

    static bool supprimer(const QString& idPublication, QString *err = nullptr);

    static bool chargerTout(QVector<Row> &out, QString *err = nullptr);

private:
    static bool nextId(int &outId, QString *err = nullptr);

    QString m_titre;
    QString m_resume;
    QString m_inventeurs;
    QString m_domaineFabrication;
    QString m_typeBrevet;
    int     m_numeroBrevet = 0;
    QDate   m_dateDepot;
    QString m_statutBrevet;
};

#endif // PUBLICATION_H
