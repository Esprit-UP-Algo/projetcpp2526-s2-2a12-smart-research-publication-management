#include "connection.h"


// Constructeur privé
Connection::Connection()
{
    db = QSqlDatabase::addDatabase("QODBC");
}

Connection::~Connection()
{
    if (db.isOpen())
        db.close();
}


Connection& Connection::createInstance()
{
    static Connection instance;
    return instance;
}

bool Connection::createConnection()
{

    db.setDatabaseName("Source_Projet2A"); // Nom de ta source ODBC
    db.setUserName("hichem");             // Username Oracle
    db.setPassword("12345");            // Password Oracle

    if (db.open())
    {
        qDebug() << "Connexion établie avec succès !";
        return true;
    }
    else
        qDebug() << "Erreur de connexion :"
                 << db.lastError().text();
    return false;
}
