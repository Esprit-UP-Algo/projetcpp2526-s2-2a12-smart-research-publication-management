#ifndef MAPDIALOG_H
#define MAPDIALOG_H

#include <QDialog>
#include <QWebEngineView>
#include <QWebChannel>

// Bridge QObject exposé à JavaScript via QWebChannel
class MapBridge : public QObject
{
    Q_OBJECT
public:
    explicit MapBridge(QObject *parent = nullptr) : QObject(parent) {}

signals:
    void coordinatesSelected(const QString &coords);

public slots:
    void coordsSelected(const QString &coords) { emit coordinatesSelected(coords); }
};

class MapDialog : public QDialog
{
    Q_OBJECT
public:
    enum Mode {
        ViewMode,  // Affiche une localisation existante
        PickMode   // Permet de cliquer sur la carte pour choisir des coordonnées
    };

    explicit MapDialog(Mode mode, const QString &location = QString(), QWidget *parent = nullptr);

signals:
    void coordinatesSelected(const QString &coords);

private:
    QWebEngineView *m_view;
    MapBridge      *m_bridge;
    Mode            m_mode;

    QString buildViewHtml(const QString &location) const;
    QString buildPickHtml() const;
};

#endif // MAPDIALOG_H
