    #include "smssender.h"
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QUrl>
#include <QByteArray>
#include <QEventLoop>
#include <QJsonDocument>
#include <QJsonObject>

const QString SmsSender::AUTH_TOKEN  = "9ec6c17f282197e97353f52bcb207276";
const QString SmsSender::FROM_NUMBER = "+17828192041";

bool SmsSender::envoyerSMS(const QString &to, const QString &message, QString &erreur)
{
    QNetworkAccessManager mgr;

    QString urlStr = QString("https://api.twilio.com/2010-04-01/Accounts/%1/Messages.json")
                         .arg(ACCOUNT_SID);

    QUrl url(urlStr);
    QNetworkRequest req;
    req.setUrl(url);

    // Basic auth: AccountSID:AuthToken base64
    QString credentials = ACCOUNT_SID + ":" + AUTH_TOKEN;
    QByteArray authHeader = "Basic " + credentials.toUtf8().toBase64();
    req.setRawHeader("Authorization", authHeader);
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QUrlQuery params;
    params.addQueryItem("To",   to);
    params.addQueryItem("From", FROM_NUMBER);
    params.addQueryItem("Body", message);

    QByteArray postData = params.toString(QUrl::FullyEncoded).toUtf8();

    QEventLoop loop;
    QNetworkReply *reply = mgr.post(req, postData);
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    if (reply->error() != QNetworkReply::NoError) {
        erreur = reply->errorString();
        QByteArray body = reply->readAll();
        if (!body.isEmpty()) {
            QJsonObject obj = QJsonDocument::fromJson(body).object();
            if (obj.contains("message"))
                erreur += " — " + obj["message"].toString();
        }
        reply->deleteLater();
        return false;
    }

    QByteArray body = reply->readAll();
    QJsonObject obj = QJsonDocument::fromJson(body).object();
    reply->deleteLater();

    // Twilio returns "status" field; error_code present means failure
    if (obj.contains("error_code") && !obj["error_code"].isNull()) {
        erreur = obj.value("message").toString("Erreur Twilio inconnue");
        return false;
    }

    return true;
}
