#ifndef PROJET_H
#define PROJET_H

#include <QString>
#include <QVector>
#include <QDate>

class Projet
{
public:
    struct Row {
        QString id;
        QString nom;
        QString description;
        QString objectifs;
        QString dateDebut;
        QString dateFinPrevue;
        QString dateFinReelle;
        QString statut;
        QString priorite;
        int     idemp = 0;
    };

    Projet() = default;
    Projet(QString nom, QString description, QString objectifs,
           QDate dateDebut, QDate dateFinPrevue, QDate dateFinReelle,
           QString statut, QString priorite);

    bool ajouter(int idemp, QString *err=nullptr) const;

    static bool modifier(const QString& id,
                         const QString& nom,
                         const QString& description,
                         const QString& objectifs,
                         const QDate& dateDebut,
                         const QDate& dateFinPrevue,
                         const QDate& dateFinReelle,
                         const QString& statut,
                         const QString& priorite,
                         QString *err=nullptr);

    static bool supprimer(const QString& id, QString *err=nullptr);
    static bool chargerTout(QVector<Row>& out, QString *err=nullptr);

private:
    static bool nextId(int &outId, QString *err=nullptr);

    QString m_nom, m_description, m_objectifs, m_statut, m_priorite;
    QDate   m_dateDebut, m_dateFinPrevue, m_dateFinReelle;
};

#endif
