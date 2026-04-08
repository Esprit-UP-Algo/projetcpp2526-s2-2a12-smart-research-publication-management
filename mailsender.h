#ifndef MAILSENDER_H
#define MAILSENDER_H

#include <QString>

class MailSender
{
public:
    /** \a nomExpediteurAffiche : nom affiché ; \a adresseExpediteurAffiche : adresse dans From (ex. rh@…). Si cette adresse est vide, c'est smtpUser qui apparaît. */
    bool envoyerMail(const QString &smtpUser,
                     const QString &smtpPass,
                     const QString &destinataire,
                     const QString &sujet,
                     const QString &contenu,
                     QString &erreur,
                     const QString &nomExpediteurAffiche = QString(),
                     const QString &adresseExpediteurAffiche = QString());

private:
    QString encoderBase64(const QString &text) const;
};

#endif // MAILSENDER_H
