#ifndef FINANCE_H
#define FINANCE_H

#include <QString>
#include <QDate>
#include <QVector>
#include <utility>

class Finance
{
public:
    struct Row {
        QString id;
        QString code;
        QString type;
        QString montant;
        QString categorie;
        QString description;
        QString dateTransaction; // "YYYY-MM-DD"
        QString modePaiement;
        QString dateCreation;    // "YYYY-MM-DD"
    };

    Finance() = default;

    Finance(QString code,
            QString type,
            double montant,
            QString categorie,
            QString description,
            QDate dateTransaction,
            QString modePaiement,
            QDate dateCreation,
            int IDEMP)
        : m_code(std::move(code)),
        m_type(std::move(type)),
        m_montant(montant),
        m_categorie(std::move(categorie)),
        m_description(std::move(description)),
        m_dateTransaction(dateTransaction),
        m_modePaiement(std::move(modePaiement)),
        m_dateCreation(dateCreation),
        m_IDEMP(std::move(IDEMP))
    {}

    // CRUD
    bool ajouter(QString *err = nullptr) const;
    static bool modifier(const QString& idFinance,
                         const QString& code,
                         const QString& type,
                         double montant,
                         const QString& categorie,
                         const QString& description,
                         const QDate& dateTransaction,
                         const QString& modePaiement,
                         const QDate& dateCreation,
                         QString *err = nullptr);

    static bool supprimer(const QString& idFinance, QString *err = nullptr);

    static bool chargerTout(QVector<Row> &out, QString *err = nullptr);

private:
    static bool nextId(int &outId, QString *err = nullptr);

    QString m_code;
    QString m_type;
    double  m_montant = 0.0;
    QString m_categorie;
    QString m_description;
    QDate   m_dateTransaction;
    QString m_modePaiement;
    QDate   m_dateCreation;
    int m_IDEMP;
};

#endif // FINANCE_H
