#ifndef MAPDIALOG_H
#define MAPDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QNetworkAccessManager>
#include "tilemapwidget.h"

class MapDialog : public QDialog
{
    Q_OBJECT
public:
    enum Mode {
        ViewMode,   // Affiche une localisation existante (lecture seule)
        PickMode    // L'utilisateur clique pour choisir des coordonnées
    };

    explicit MapDialog(Mode mode, const QString &location = QString(), QWidget *parent = nullptr);

signals:
    void coordinatesSelected(const QString &coords);

private:
    TileMapWidget         *m_map;
    QLabel                *m_coordsLabel  = nullptr;
    QPushButton           *m_btnConfirm   = nullptr;
    QNetworkAccessManager *m_nam          = nullptr;

    // Géocode un texte et centre la carte (utilisé en ViewMode)
    void geocodeAndCenter(const QString &location);
};

#endif // MAPDIALOG_H
