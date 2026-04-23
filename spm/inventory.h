#ifndef INVENTORY_H
#define INVENTORY_H

#include <QString>
#include <QVector>

class Inventory
{
public:
    // ── Data carrier ──────────────────────────────────────────────────────────
    struct Row {
        QString idProduct;
        QString name;
        QString sku;
        QString type;
        int     qtAv;
        int     qtRs;
        int     threshold;
        QString unit;
        double  price;
        QString status;
        QString zone;
        QString shelf;
        QString description;
        int     useCount;
        int     idemp;
    };

    // ── Constructor ───────────────────────────────────────────────────────────
    Inventory() = default;
    Inventory(QString name, QString sku, QString type, int qtAv, int qtRs,
              int threshold, QString unit, double price, QString status,
              QString zone, QString shelf, QString description);

    // ── CRUD ──────────────────────────────────────────────────────────────────
    bool ajouter(QString *err = nullptr) const;

    static bool nextId(int &outId, QString *err = nullptr);

    static bool modifier(const QString &idProduct,
                         const QString &name, const QString &sku, const QString &type,
                         int qtAv, int qtRs, int threshold, const QString &unit,
                         double price, const QString &status, const QString &zone,
                         const QString &shelf, const QString &description,
                         QString *err = nullptr);

    static bool supprimer(const QString &idProduct,
                          const QString &sku,
                          QString *err = nullptr);

    static bool chargerTout(QVector<Row> &out, const QString &orderBy = "SKU", QString *err = nullptr);

    /// Types distincts présents en base (pour le filtre inventaire).
    static bool typesDistincts(QVector<QString> &out, QString *err = nullptr);

    // ── Search / filter ───────────────────────────────────────────────────────
    static bool chercher(QVector<Row> &out,
                         const QString &keyword,
                         const QString &zone,
                         const QString &status,
                         const QString &type,
                         const QString &orderBy = "SKU",
                         QString *err = nullptr);
    // Dans la section "Search / filter", après chercher(...)
    static bool checkThresholdAlerts(QVector<Row> &outAlerts, QString *err = nullptr);

private:
    QString m_idProduct;
    QString m_name;
    QString m_sku;
    QString m_type;
    int     m_qtAv;
    int     m_qtRs;
    int     m_threshold;
    QString m_unit;
    double  m_price;
    QString m_status;
    QString m_zone;
    QString m_shelf;
    QString m_description;
    int     m_idemp;
};

#endif // INVENTORY_H
