#ifndef SMSSENDER_H
#define SMSSENDER_H

#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QEventLoop>

class SmsSender
{
public:
    // Returns true on success, sets erreur on failure
    static bool envoyerSMS(const QString &to,
                           const QString &message,
                           QString &erreur);

private:
    static const QString ACCOUNT_SID;
    static const QString AUTH_TOKEN;
    static const QString FROM_NUMBER;
};

#endif // SMSSENDER_H
