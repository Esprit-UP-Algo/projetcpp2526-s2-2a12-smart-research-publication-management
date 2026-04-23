#include "smssender.h"
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>

// ON SUPPRIME LES VALEURS EN DUR ICI
bool SmsSender::envoyerSMS(const QString &to, const QString &message, QString &erreur)
{
    // On récupère les clés depuis l'environnement (Configuré dans Qt Creator)
    QString accountSid = qgetenv("TWILIO_ACCOUNT_SID");
    QString authToken  = qgetenv("TWILIO_AUTH_TOKEN");
    QString fromNumber = qgetenv("TWILIO_FROM_NUMBER");

    if (accountSid.isEmpty() || authToken.isEmpty()) {
        erreur = "Configurations Twilio manquantes dans l'environnement.";
        return false;
    }

    QNetworkAccessManager mgr;
    QString urlStr = QString("https://api.twilio.com/2010-04-01/Accounts/%1/Messages.json").arg(accountSid);

    // ... reste du code identique en remplaçant ACCOUNT_SID par accountSid, etc.
