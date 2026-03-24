#ifndef PUBLICATION_H
#define PUBLICATION_H

#include <QString>
#include <QVector>
#include <QDate>

class Publication
{
public:
    struct Row {
        QString id;
        QString titre;
        QString resume;
        QString inventeurs;
        QString domaine;
        QString type;
        QString numero;
        QString dateDepot;
        QString statut;
        int     idemp;
    };

    Publication() = default;
    Publication(QString titre, QString resume, QString inventeurs,
                QString domaine, QString type, int numero,
                QDate dateDepot, QString statut);

    bool ajouter(int idemp, QString *err = nullptr) const;

    static bool nextId(int &outId, QString *err=nullptr);

    static bool modifier(const QString &id,
                         const QString &titre,
                         const QString &resume,
                         const QString &inventeurs,
                         const QString &domaine,
                         const QString &type,
                         int numero,
                         const QDate &dateDepot,
                         const QString &statut,
                         QString *err=nullptr);

    static bool supprimer(const QString &id, QString *err=nullptr);

    static bool chargerTout(QVector<Row> &out, QString *err=nullptr);

private:
    QString m_titre, m_resume, m_inventeurs, m_domaine, m_type, m_statut;
    int     m_numero = 0;
    QDate   m_dateDepot;
};

#endif
