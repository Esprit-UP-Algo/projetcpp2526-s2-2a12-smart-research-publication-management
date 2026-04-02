#ifndef PUBLICATION_H
#define PUBLICATION_H

#include <QString>
#include <QDate>
#include <QVector>

class Publication
{
public:
    struct Row {
        QString idPublication;
        QString titre;
        QString resume;
        QString inventeurs;
        QString domaineFabrication;
        QString typeBrevet;
        int numeroBrevet = 0;
        QString dateDepot;      // yyyy-MM-dd
        QString statutBrevet;
        QString idEmp;
    };

    Publication() = default;

    Publication(
        const QString& titre,
        const QString& resume,
        const QString& inventeurs,
        const QString& domaineFabrication,
        const QString& typeBrevet,
        int numeroBrevet,
        const QDate& dateDepot,
        const QString& statutBrevet,
        const QString& idEmp
        );

    bool ajouter(QString *err = nullptr) const;
    bool modifier(const QString& idPublication, QString *err = nullptr) const;
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
    QString m_idEmp;
};

#endif // PUBLICATION_H
