// labs.cpp
#include "labs.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>

static void setErr(QString *err, const QString& msg) {
    if (err) *err = msg;
}

Labs::Labs(const QString& nomlabo,
           const QString& responsable,
           const QString& numero,
           const QString& localisation,
           const QString& specialite,
           const QString& disponibilite,
           const QString& resultat,
           const QString& paiement,
           double  montant,
           double  montantPaye,
           const QString& idemp)
    : m_nomlabo(nomlabo),
    m_responsable(responsable),
    m_numero(numero),
    m_localisation(localisation),
    m_specialite(specialite),
    m_disponibilite(disponibilite),
    m_resultat(resultat),
    m_paiement(paiement),
    m_montant(montant),
    m_montantPaye(montantPaye),
    m_idemp(idemp)
{}

bool Labs::nextId(int &outId, QString *err)
{
    QSqlQuery q;
    if (!q.exec("SELECT NVL(MAX(IDLABO), 0) + 1 FROM LABS")) {
        setErr(err, q.lastError().text());
        return false;
    }
    if (!q.next()) {
        setErr(err, "Impossible de générer un nouvel IDLABO");
        return false;
    }
    outId = q.value(0).toInt();
    return true;
}

QString Labs::getNextId(QString *err)
{
    int id = 0;
    if (!nextId(id, err)) return QString();
    return QString::number(id);
}

bool Labs::ajouter(QString *err) const
{
    // Validation métier : montant_paye ne peut pas dépasser montant
    if (m_montantPaye > m_montant) {
        setErr(err, "Le montant payé ne peut pas être supérieur au montant total.");
        return false;
    }

    int newId = 0;
    if (!nextId(newId, err)) return false;

    QSqlQuery q;
    q.prepare("INSERT INTO LABS "
              "(IDLABO, NOMLABO, RESPONSABLE, NUMERO, LOCALISATION, "
              "SPECIALITE, DISPONIBILITE, RESULTAT, PAIEMENT, MONTANT, MONTANT_PAYE, IDEMP) "
              "VALUES (:id, :nom, :resp, :num, :loc, :spec, :disp, :res, :paiement, "
              ":montant, :montantPaye, :idemp)");

    q.bindValue(":id",          newId);
    q.bindValue(":nom",         m_nomlabo);
    q.bindValue(":resp",        m_responsable);
    q.bindValue(":num",         m_numero);
    q.bindValue(":loc",         m_localisation);
    q.bindValue(":spec",        m_specialite);
    q.bindValue(":disp",        m_disponibilite);
    q.bindValue(":res",         m_resultat);
    q.bindValue(":paiement",    m_paiement);
    q.bindValue(":montant",     m_montant);
    q.bindValue(":montantPaye", m_montantPaye);
    q.bindValue(":idemp",       m_idemp);

    if (!q.exec()) {
        setErr(err, q.lastError().text());
        return false;
    }
    return true;
}

bool Labs::modifier(const QString& idLabo,
                    const QString& nomlabo,
                    const QString& responsable,
                    const QString& numero,
                    const QString& localisation,
                    const QString& specialite,
                    const QString& disponibilite,
                    const QString& resultat,
                    const QString& paiement,
                    double  montant,
                    double  montantPaye,
                    QString *err)
{
    // Validation métier : montant_paye ne peut pas dépasser montant
    if (montantPaye > montant) {
        setErr(err, "Le montant payé ne peut pas être supérieur au montant total.");
        return false;
    }

    QSqlQuery q;
    q.prepare("UPDATE LABS SET "
              "NOMLABO=:nom, RESPONSABLE=:resp, NUMERO=:num, LOCALISATION=:loc, "
              "SPECIALITE=:spec, DISPONIBILITE=:disp, RESULTAT=:res, PAIEMENT=:paiement, "
              "MONTANT=:montant, MONTANT_PAYE=:montantPaye "
              "WHERE IDLABO=:id");

    q.bindValue(":nom",         nomlabo);
    q.bindValue(":resp",        responsable);
    q.bindValue(":num",         numero);
    q.bindValue(":loc",         localisation);
    q.bindValue(":spec",        specialite);
    q.bindValue(":disp",        disponibilite);
    q.bindValue(":res",         resultat);
    q.bindValue(":paiement",    paiement);
    q.bindValue(":montant",     montant);
    q.bindValue(":montantPaye", montantPaye);
    q.bindValue(":id",          idLabo);

    if (!q.exec()) {
        setErr(err, q.lastError().text());
        return false;
    }
    return true;
}

bool Labs::supprimer(const QString& idLabo, QString *err)
{
    QSqlQuery q;
    q.prepare("DELETE FROM LABS WHERE IDLABO = :id");
    q.bindValue(":id", idLabo);

    if (!q.exec()) {
        setErr(err, q.lastError().text());
        return false;
    }
    return true;
}

bool Labs::chargerTout(QVector<Row> &out, QString *err)
{
    out.clear();
    QSqlQuery q;
    q.prepare("SELECT IDLABO, NOMLABO, RESPONSABLE, NUMERO, LOCALISATION, "
              "DISPONIBILITE, SPECIALITE, RESULTAT, PAIEMENT, "
              "MONTANT, MONTANT_PAYE "
              "FROM LABS ORDER BY IDLABO DESC");

    if (!q.exec()) {
        setErr(err, q.lastError().text());
        return false;
    }

    while (q.next()) {
        Row r;
        r.id            = q.value(0).toString();
        r.nomlabo       = q.value(1).toString();
        r.responsable   = q.value(2).toString();
        r.numero        = q.value(3).toString();
        r.localisation  = q.value(4).toString();
        r.disponibilite = q.value(5).toString();
        r.specialite    = q.value(6).toString();
        r.resultat      = q.value(7).toString();
        r.paiement      = q.value(8).toString();
        r.montant       = QString(q.value(9).toString()).replace(',', '.').toDouble();
        r.montantPaye   = QString(q.value(10).toString()).replace(',', '.').toDouble();
        r.reste         = r.montant - r.montantPaye;
        out.append(r);
    }
    return true;
}

bool Labs::getById(const QString& idLabo, Row &outRow, QString *err)
{
    QSqlQuery q;
    q.prepare("SELECT IDLABO, NOMLABO, RESPONSABLE, NUMERO, LOCALISATION, "
              "DISPONIBILITE, SPECIALITE, RESULTAT, PAIEMENT, "
              "MONTANT, MONTANT_PAYE "
              "FROM LABS WHERE IDLABO = :id");
    q.bindValue(":id", idLabo);

    if (!q.exec()) {
        setErr(err, q.lastError().text());
        return false;
    }
    if (!q.next()) {
        setErr(err, "Laboratoire non trouvé");
        return false;
    }

    outRow.id            = q.value(0).toString();
    outRow.nomlabo       = q.value(1).toString();
    outRow.responsable   = q.value(2).toString();
    outRow.numero        = q.value(3).toString();
    outRow.localisation  = q.value(4).toString();
    outRow.disponibilite = q.value(5).toString();
    outRow.specialite    = q.value(6).toString();
    outRow.resultat      = q.value(7).toString();
    outRow.paiement      = q.value(8).toString();
    outRow.montant       = QString(q.value(9).toString()).replace(',', '.').toDouble();
    outRow.montantPaye   = QString(q.value(10).toString()).replace(',', '.').toDouble();
    outRow.reste         = outRow.montant - outRow.montantPaye;

    return true;
}
