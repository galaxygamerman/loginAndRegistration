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
				   "username TEXT,"
				   "password TEXT,"
				   "fullname TEXT,"
				   "email TEXT,"
				   "phone TEXT,"
				   "age INTEGER,"
				   "gender TEXT,"
				   "userrole TEXT,"
				   "PRIMARY KEY (username)"
				   ")");
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
	qDebug() << "In the backend: " << username << ' ' << password << ' ' << fullname << ' ' << email
			 << ' ' << phone << ' ' << age << ' ' << gender << ' ' << userrole;
	QSqlQuery query;
	query.prepare(
		"INSERT INTO users (username, password, fullname, email, phone, age, gender, userrole)"
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

bool DatabaseManager::checkUser(const QString &username,
								const QString &password,
								const QString &userrole)
{
	qDebug() << "In the backend: " << username << ' ' << password << ' ' << userrole;
	QSqlQuery query;
	query.prepare(
		"SELECT username, password FROM users WHERE username = :username AND password = :password");
	query.bindValue(":username", username);
	query.bindValue(":password", password);

	if (!query.exec()) {
		qDebug() << "User login failed: " << query.lastError().text();
		// TODO: Upon failed login, show the modal with a "Failed to authenticate" message
		return false;
	}

	return query.next();
}

QVariantHash DatabaseManager::getUserData(const QString &username)
{
	qDebug() << "Searching for " << username << "'s data...";
	QSqlQuery query;
	query.prepare("SELECT * FROM users WHERE username = :username");
	query.bindValue(":username", username);

	QVariantHash userData;
	if (query.exec() && query.next()) {
		userData["username"] = query.value("username");
		userData["password"] = query.value("password");
		userData["fullname"] = query.value("fullname");
		userData["email"] = query.value("email");
		userData["phone"] = query.value("phone");
		userData["age"] = query.value("age");
		userData["gender"] = query.value("gender");
		userData["userrole"] = query.value("userrole");
		userData["success"] = true;
	} else {
		userData["success"] = false;
	}
	return userData;
}
