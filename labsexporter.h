#ifndef LABSEXPORTER_H
#define LABSEXPORTER_H

#include <QObject>
#include <QString>

class QPainter;

// ── Exportateur PDF pour Gestion Labs ────────────────────────────────────────
// Génère un PDF A4 avec les informations du laboratoire.
class LabsExporter : public QObject
{
    Q_OBJECT

public:
    struct LabData {
        QString nomLabo;
        QString responsable;
        QString telephone;
        QString localisation;   // coordonnées GPS ou adresse textuelle
        QString montant;        // montant total (sans "DT")
        QString montantPaye;
        QString reste;
        QString disponibilite;
        QString paiement;
    };

    explicit LabsExporter(QObject *parent = nullptr);

    // Génère le PDF dans outputFolder.
    // Retourne le chemin complet du fichier créé, ou une chaîne vide en cas d'erreur.
    QString exportToPdf(const LabData &data,
                        const QString &outputFolder = "C:/GestionLabs");

private:
    // Dessine le contenu du PDF sur le QPainter fourni
    void renderPage(QPainter &p, int pageWidth,
                    const LabData &data) const;
};

#endif // LABSEXPORTER_H
