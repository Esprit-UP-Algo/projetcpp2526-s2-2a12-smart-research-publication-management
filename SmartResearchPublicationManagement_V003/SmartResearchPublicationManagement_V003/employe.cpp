#include "employe.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

////////////////////////////////////////////////////////////
/// GENERER ID SUIVANT (MAX + 1)
////////////////////////////////////////////////////////////
bool Employe::nextId(int &outId, QString *err)
{
    QSqlQuery query;
    if (!query.exec("SELECT COALESCE(MAX(ID_EMPLOYE), 0) + 1 FROM EMPLOYES"))
    {
        QString error = query.lastError().text();
        qDebug() << "[nextId] Erreur SQL :" << error;
        if (err) *err = "Erreur génération ID : " + error;
        return false;
    }
    if (query.next())
    {
        outId = query.value(0).toInt();
        qDebug() << "[nextId] Nouvel ID généré :" << outId;
        return true;
    }
    QString msg = "Aucune valeur retournée pour le prochain ID";
    qDebug() << "[nextId]" << msg;
    if (err) *err = msg;
    return false;
}

////////////////////////////////////////////////////////////
/// AJOUTER UN EMPLOYE
////////////////////////////////////////////////////////////
bool Employe::ajouter(QString *err) const
{
    int next_id = -1;
    QString errorStr;

    if (!nextId(next_id, &errorStr)) {
        if (err) *err = errorStr;
        return false;
    }

    QSqlQuery query;
    query.prepare(
        "INSERT INTO EMPLOYES ("
        "ID_EMPLOYE, CIN, NOM, PRENOM, USERNAME, PASSWORD_HASH, EMAIL, "
        "POSTE, DEPARTEMENT, TYPE_CONTRAT, DATE_EMBAUCHE, SALAIRE, ROLE"
        ") VALUES ("
        ":id, :cin, :nom, :prenom, :username, :passwordHash, :email, "
        ":poste, :departement, :typeContrat, "
        "TO_DATE(:dateEmbauche, 'YYYY-MM-DD'), "   // ← OBLIGATOIRE : TO_DATE + format exact
        ":salaire, :role"
        ")"
        );

    query.bindValue(":id",           next_id);
    query.bindValue(":cin",          m_cin);
    query.bindValue(":nom",          m_nom);
    query.bindValue(":prenom",       m_prenom);
    query.bindValue(":username",     m_username);
    query.bindValue(":passwordHash", m_passwordHash);
    query.bindValue(":email",        m_email);
    query.bindValue(":poste",        m_poste);
    query.bindValue(":departement",  m_departement);
    query.bindValue(":typeContrat",  m_typeContrat);
    query.bindValue(":dateEmbauche", m_dateEmbauche.toString("yyyy-MM-dd"));  // chaîne YYYY-MM-DD
    query.bindValue(":salaire",      m_salaire);
    query.bindValue(":role",         m_role);

    // Log pour voir exactement ce qui est envoyé
    qDebug() << "[Ajout] Date envoyée à Oracle :" << m_dateEmbauche.toString("yyyy-MM-dd");

    if (!query.exec()) {
        errorStr = query.lastError().text();
        qDebug() << "[ajouter] Erreur INSERT :" << errorStr;
        if (err) *err = "Échec de l'ajout : " + errorStr;
        return false;
    }

    qDebug() << "[ajouter] Employé ajouté avec succès - ID =" << next_id;
    return true;
}
bool Employe::modifier(const QString& idEmploye,
                       const QString& cin,
                       const QString& nom,
                       const QString& prenom,
                       const QString& username,
                       const QString& email,
                       const QString& poste,
                       const QString& departement,
                       const QString& typeContrat,
                       const QDate& dateEmbauche,
                       double salaire,
                       const QString& role,
                       QString *err)
{
    QSqlQuery query;
    query.prepare(
        "UPDATE EMPLOYES SET "
        "CIN = :cin, "
        "NOM = :nom, "
        "PRENOM = :prenom, "
        "USERNAME = :username, "
        "EMAIL = :email, "
        "POSTE = :poste, "
        "DEPARTEMENT = :departement, "
        "TYPE_CONTRAT = :typeContrat, "
        "DATE_EMBAUCHE = TO_DATE(:dateEmbauche, 'YYYY-MM-DD'), "
        "SALAIRE = :salaire, "
        "ROLE = :role "
        "WHERE ID_EMPLOYE = :id"
        );

    query.bindValue(":cin",          cin);
    query.bindValue(":nom",          nom);
    query.bindValue(":prenom",       prenom);
    query.bindValue(":username",     username);
    query.bindValue(":email",        email);
    query.bindValue(":poste",        poste);
    query.bindValue(":departement",  departement);
    query.bindValue(":typeContrat",  typeContrat);
    query.bindValue(":dateEmbauche", dateEmbauche.toString("yyyy-MM-dd"));  // format sûr avec TO_DATE
    query.bindValue(":salaire",      salaire);
    query.bindValue(":role",         role);
    query.bindValue(":id",           idEmploye);

    if (!query.exec()) {
        QString error = query.lastError().text();
        qDebug() << "[modifier] Erreur :" << error;
        if (err) *err = "Échec de la modification : " + error;
        return false;
    }

    qDebug() << "[modifier] Employé modifié avec succès - ID =" << idEmploye;
    return true;
}

////////////////////////////////////////////////////////////
/// SUPPRIMER UN EMPLOYE
////////////////////////////////////////////////////////////
bool Employe::supprimer(const QString& idEmploye, QString *err)
{
    QSqlQuery query;
    query.prepare("DELETE FROM EMPLOYES WHERE ID_EMPLOYE = :id");
    query.bindValue(":id", idEmploye);

    if (!query.exec())
    {
        QString error = query.lastError().text();
        qDebug() << "[supprimer] Erreur DELETE ID" << idEmploye << ":" << error;
        if (err) *err = "Échec de la suppression : " + error;
        return false;
    }

    qDebug() << "[supprimer] Employé supprimé avec succès - ID =" << idEmploye;
    return true;
}

////////////////////////////////////////////////////////////
/// CHARGER TOUS LES EMPLOYES
////////////////////////////////////////////////////////////
bool Employe::chargerTout(QVector<Row> &out, QString *err)
{
    QSqlQuery query;
    if (!query.exec(
            "SELECT ID_EMPLOYE, CIN, NOM, PRENOM, USERNAME, EMAIL, "
            "POSTE, DEPARTEMENT, TYPE_CONTRAT, "
            "TO_CHAR(DATE_EMBAUCHE, 'YYYY-MM-DD') AS DATE_EMBAUCHE, "
            "SALAIRE, ROLE "
            "FROM EMPLOYES "
            "ORDER BY ID_EMPLOYE ASC"
            ))
    {
        QString error = query.lastError().text();
        qDebug() << "[chargerTout] Erreur SELECT :" << error;
        if (err) *err = "Impossible de charger les employés : " + error;
        return false;
    }

    out.clear();
    int count = 0;
    while (query.next())
    {
        Row r;
        r.idEmploye    = query.value("ID_EMPLOYE").toString();
        r.cin          = query.value("CIN").toString();
        r.nom          = query.value("NOM").toString();
        r.prenom       = query.value("PRENOM").toString();
        r.username     = query.value("USERNAME").toString();
        r.email        = query.value("EMAIL").toString();
        r.poste        = query.value("POSTE").toString();
        r.departement  = query.value("DEPARTEMENT").toString();
        r.typeContrat  = query.value("TYPE_CONTRAT").toString();
        r.dateEmbauche = query.value("DATE_EMBAUCHE").toString();
        r.salaire      = query.value("SALAIRE").toDouble();
        r.role         = query.value("ROLE").toString();

        out.append(r);
        count++;
    }

    qDebug() << "[chargerTout] " << count << " employés chargés avec succès";
    return true;
}
bool Employe::usernameExiste(const QString &username)
{
    QSqlQuery query;
    query.prepare("SELECT 1 FROM EMPLOYES WHERE USERNAME = :username");
    query.bindValue(":username", username);

    if (!query.exec()) {
        qDebug() << query.lastError().text();
        return false;
    }

    if (query.next())
        return true;

    return false;
}
