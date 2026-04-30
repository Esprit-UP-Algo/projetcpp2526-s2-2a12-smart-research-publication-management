#include "mailsender.h"

#include <QSslSocket>
#include <QByteArray>
#include <QStringList>
#include <QAbstractSocket>

namespace {
QString prepareSmtpDataBody(const QString &contenu)
{
    QString normalized = contenu;
    normalized.replace(QStringLiteral("\r\n"), QStringLiteral("\n"));
    normalized.replace(QStringLiteral("\r"), QStringLiteral("\n"));
    const QStringList lines = normalized.split(QLatin1Char('\n'));
    QString out;
    for (const QString &line : lines) {
        if (line.startsWith(QLatin1Char('.')))
            out += QLatin1Char('.');
        out += line + QStringLiteral("\r\n");
    }
    return out;
}

bool envoyerViaSmtp(QSslSocket &socket,
                    const QString &smtpUser,
                    const QString &smtpPass,
                    const QString &destinataire,
                    const QString &sujet,
                    const QString &contenu,
                    QString &erreur,
                    const QString &nomExpediteurAffiche,
                    const QString &adresseExpediteurAffiche,
                    bool startTlsMode,
                    bool contenuHtml)
{
    auto lireReponse = [&](const QString &codeAttendu) -> bool {
        if (!socket.waitForReadyRead(12000)) {
            erreur = "Aucune réponse du serveur SMTP.";
            return false;
        }

        QString response = QString::fromUtf8(socket.readAll());
        while (socket.waitForReadyRead(250)) {
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

    if (startTlsMode) {
        if (!envoyerCommande("STARTTLS\r\n", "220")) return false;
        socket.startClientEncryption();
        if (!socket.waitForEncrypted(10000)) {
            erreur = "Activation STARTTLS impossible : " + socket.errorString();
            return false;
        }
        if (!envoyerCommande("EHLO localhost\r\n", "250")) return false;
    }

    if (!envoyerCommande("AUTH LOGIN\r\n", "334")) return false;
    if (!envoyerCommande(smtpUser.toUtf8().toBase64() + "\r\n", "334")) return false;
    if (!envoyerCommande(smtpPass.toUtf8().toBase64() + "\r\n", "235")) return false;
    if (!envoyerCommande("MAIL FROM:<" + smtpUser + ">\r\n", "250")) return false;
    if (!envoyerCommande("RCPT TO:<" + destinataire + ">\r\n", "250")) return false;
    if (!envoyerCommande("DATA\r\n", "354")) return false;

    const QString addrFrom = adresseExpediteurAffiche.isEmpty() ? smtpUser : adresseExpediteurAffiche;
    QString message;
    if (nomExpediteurAffiche.isEmpty()) {
        message += "From: <" + addrFrom + ">\r\n";
    } else {
        QString nom = nomExpediteurAffiche;
        nom.replace(QLatin1Char('"'), QLatin1String("\\\""));
        message += "From: \"" + nom + "\" <" + addrFrom + ">\r\n";
    }
    message += "To: <" + destinataire + ">\r\n";
    message += "Subject: " + sujet + "\r\n";
    message += "MIME-Version: 1.0\r\n";
    if (contenuHtml) {
        message += "Content-Type: text/html; charset=UTF-8\r\n";
    } else {
        message += "Content-Type: text/plain; charset=UTF-8\r\n";
    }
    message += "Content-Transfer-Encoding: 8bit\r\n\r\n";
    message += prepareSmtpDataBody(contenu);
    message += ".\r\n";

    if (!envoyerCommande(message, "250")) return false;
    if (!envoyerCommande("QUIT\r\n", "221")) return false;
    return true;
}
} // namespace

QString MailSender::encoderBase64(const QString &text) const
{
    return text.toUtf8().toBase64();
}

bool MailSender::envoyerMail(const QString &smtpUser,
                             const QString &smtpPass,
                             const QString &destinataire,
                             const QString &sujet,
                             const QString &contenu,
                             QString &erreur,
                             const QString &nomExpediteurAffiche,
                             const QString &adresseExpediteurAffiche,
                             bool contenuHtml)
{
    // 1) SSL direct (465)
    {
        QSslSocket socket;
        socket.connectToHostEncrypted("smtp.gmail.com", 465);
        if (socket.waitForEncrypted(10000)) {
            if (envoyerViaSmtp(socket, smtpUser, smtpPass, destinataire, sujet, contenu,
                               erreur, nomExpediteurAffiche, adresseExpediteurAffiche, false, contenuHtml)) {
                return true;
            }
        } else {
            erreur = "Connexion SSL impossible : " + socket.errorString();
        }
    }

    // 2) Fallback STARTTLS (587)
    {
        QSslSocket socket;
        socket.connectToHost("smtp.gmail.com", 587);
        if (!socket.waitForConnected(10000)) {
            erreur += "\nFallback STARTTLS impossible : " + socket.errorString();
            return false;
        }
        if (envoyerViaSmtp(socket, smtpUser, smtpPass, destinataire, sujet, contenu,
                           erreur, nomExpediteurAffiche, adresseExpediteurAffiche, true, contenuHtml)) {
            return true;
        }
    }

    return false;
}
