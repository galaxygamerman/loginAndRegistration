#include "databasemanager.h"
#include <QDebug>
#include <QObject>
#include <QtSql>

DatabaseManager::DatabaseManager(QObject *parent)
    : QObject(parent)
{
    myDB = QSqlDatabase::addDatabase("QSQLITE");
    myDB.setDatabaseName("users.db");

    if (!myDB.open()) {
        qDebug() << "Error: connection with database failed";
    } else {
        QSqlQuery query;
        query.exec("CREATE TABLE IF NOT EXISTS users("
                   "user_id INTEGER PRIMARY KEY AUTOINCREMENT,"
                   "username TEXT,"
                   "password TEXT,"
                   "fullname TEXT,"
                   "email TEXT,"
                   "phone TEXT,"
                   "age INTEGER,"
                   "gender TEXT,"
                   "userrole TEXT)");
    }
}

bool DatabaseManager::registerUser(const QString &username,
                                   const QString &password,
                                   const QString &fullname,
                                   const QString &email,
                                   const QString &phone,
                                   const QString &age,
                                   const QString &gender,
                                   const QString &userrole)
{
    qDebug() << "In the backend: " << username
             << ' ' << password
             << ' ' << fullname
             << ' ' << email
             << ' ' << phone
             << ' ' << age
             << ' ' << gender
             << ' ' << userrole;
    QSqlQuery query;
    query.prepare("INSERT INTO users (username, password, fullname, email, phone, age, gender, userrole)"
                  "VALUES (:username, :password, :fullname, :email, :phone, :age, :gender, :userrole)");
    query.bindValue(":username", username);
    query.bindValue(":password", password);
    query.bindValue(":fullname", fullname);
    query.bindValue(":email", email);
    query.bindValue(":phone", phone);
    query.bindValue(":age", age);
    query.bindValue(":gender", gender);
    query.bindValue(":userrole", userrole);

    return query.exec();
}
