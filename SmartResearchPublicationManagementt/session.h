#ifndef SESSION_H
#define SESSION_H

#include <QString>

class Session {
public:
    static Session& instance() {
        static Session _instance;
        return _instance;
    }

    void login(const QString& id, const QString& nom, const QString& role) {
        m_id = id;
        m_nomComplet = nom;
        m_role = role; // Ex: 'Responsable_financier'
        m_isConnected = true;
    }

    // --- Tests de rôles précis ---
    bool isRH()          const { return m_role == "RH"; }
    bool isFinance()     const { return m_role == "Responsable_financier"; }
    bool isStock()       const { return m_role == "Responsable_de_stock"; }
    bool isChercheur()   const { return m_role == "Chercheur"; }
    bool isLabo()        const { return m_role == "Responsable_Labos"; }
    bool isDirecteur()   const { return m_role == "Directeur_de_projet"; }
    bool isSimpleEmploye() const { return m_role == "Employe"; }

    QString getRole() const { return m_role; }
    QString getNom()  const { return m_nomComplet; }

private:
    Session() : m_isConnected(false) {}
    QString m_id;
    QString m_nomComplet;
    QString m_role;
    bool m_isConnected;
};

#endif
