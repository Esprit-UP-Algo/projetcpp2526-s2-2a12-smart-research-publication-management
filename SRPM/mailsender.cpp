#include "mailsender.h"

#include <QSslSocket>
#include <QByteArray>
#include <QStringList>

QString MailSender::encoderBase64(const QString &text) const
{
    return text.toUtf8().toBase64();
}

bool MailSender::envoyerMail(const QString &smtpUser,
                             const QString &smtpPass,
                             const QString &destinataire,
                             const QString &sujet,
                             const QString &contenu,
                             QString &erreur)
{
    QSslSocket socket;
    socket.connectToHostEncrypted("smtp.gmail.com", 465);

    if (!socket.waitForEncrypted(10000)) {
        erreur = "Connexion SSL impossible : " + socket.errorString();
        return false;
    }

    auto lireReponse = [&](const QString &codeAttendu) -> bool {
        if (!socket.waitForReadyRead(10000)) {
            erreur = "Aucune réponse du serveur SMTP.";
            return false;
        }

        QString response = QString::fromUtf8(socket.readAll());
        while (socket.waitForReadyRead(200)) {
            response += QString::fromUtf8(socket.readAll());
        }

        if (!response.startsWith(codeAttendu)) {
            erreur = "Réponse SMTP inattendue : " + response;
            return false;
        }
        return true;
    };

    auto envoyerCommande = [&](const QString &cmd, const QString &codeAttendu) -> bool {
        socket.write(cmd.toUtf8());
        if (!socket.waitForBytesWritten(10000)) {
            erreur = "Échec d'envoi de la commande SMTP.";
            return false;
        }
        return lireReponse(codeAttendu);
    };

    if (!lireReponse("220")) return false;
    if (!envoyerCommande("EHLO localhost\r\n", "250")) return false;
    if (!envoyerCommande("AUTH LOGIN\r\n", "334")) return false;
    if (!envoyerCommande(encoderBase64(smtpUser) + "\r\n", "334")) return false;
    if (!envoyerCommande(encoderBase64(smtpPass) + "\r\n", "235")) return false;
    if (!envoyerCommande("MAIL FROM:<" + smtpUser + ">\r\n", "250")) return false;
    if (!envoyerCommande("RCPT TO:<" + destinataire + ">\r\n", "250")) return false;
    if (!envoyerCommande("DATA\r\n", "354")) return false;

    QString message;
    message += "From: <" + smtpUser + ">\r\n";
    message += "To: <" + destinataire + ">\r\n";
    message += "Subject: " + sujet + "\r\n";
    message += "MIME-Version: 1.0\r\n";
    message += "Content-Type: text/plain; charset=UTF-8\r\n";
    message += "Content-Transfer-Encoding: 8bit\r\n";
    message += "\r\n";
    message += contenu + "\r\n.\r\n";

    if (!envoyerCommande(message, "250")) return false;
    if (!envoyerCommande("QUIT\r\n", "221")) return false;

    return true;
}
