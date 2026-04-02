#ifndef MAILSENDER_H
#define MAILSENDER_H

#include <QString>

class MailSender
{
public:
    bool envoyerMail(const QString &smtpUser,
                     const QString &smtpPass,
                     const QString &destinataire,
                     const QString &sujet,
                     const QString &contenu,
                     QString &erreur);

private:
    QString encoderBase64(const QString &text) const;
};

#endif // MAILSENDER_H
//mail
