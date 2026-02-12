#include "databasemanager.h"
#include <QDebug>
#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QtSql>

DatabaseManager::DatabaseManager(QObject *parent)
	: QObject(parent)
{
	QString pathToDatabase = "database/users.db";
	bool dbExists = QFile::exists(pathToDatabase);

	if (QSqlDatabase::contains("qt_sql_default_connection")) {
		myDB = QSqlDatabase::database("qt_sql_default_connection");
	} else {
		myDB = QSqlDatabase::addDatabase("QSQLITE");
		myDB.setDatabaseName(pathToDatabase);
	}

	if (!myDB.open()) {
		qDebug() << "Error: connection with database failed";
		return;
	}

	if (dbExists){
		qDebug() << pathToDatabase << "file already detected. No need of running script.";
		return;
	}else{
		qDebug() << pathToDatabase << "file not detected. Creating table now";
	}

	QFile schemaFile("database/schema.sql");
	if (!schemaFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
		qDebug() << "Database could not be created because the script file could not be opened.";
		return;
	}

	QTextStream schemaStream(&schemaFile);
	QString schemaContent = schemaStream.readAll();
	QSqlQuery query;
	query.exec(schemaContent);

	schemaFile.close();
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
	qDebug() << "In the backend:" << username << password << fullname << email << phone << age << gender << userrole;
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
	qDebug() << "In the backend:" << username << password << userrole;
	QSqlQuery query;
	query.prepare(
		"SELECT username, password FROM users WHERE username = :username AND password = :password");
	query.bindValue(":username", username);
	query.bindValue(":password", password);

	if (!query.exec()) {
		qDebug() << "User login failed:" << query.lastError().text();
		return false;
	}

	return query.next();
}

QVariantMap DatabaseManager::getUserData(const QString &username)
{
	qDebug() << "Searching data for" << username << "...";
	QSqlQuery query;
	query.prepare("SELECT * FROM users WHERE username = :username");
	query.bindValue(":username", username);

	QVariantMap userData;
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

QVariantList DatabaseManager::getAllUserData(){
	QVariantList users;
	QSqlQuery query("SELECT * FROM users");

	while (query.next()) {
		QVariantMap user;
		user["username"] = query.value("username");
		user["password"] = query.value("password");
		user["fullname"] = query.value("fullname");
		user["email"] = query.value("email");
		user["phone"] = query.value("phone");
		user["age"] = query.value("age");
		user["gender"] = query.value("gender");
		user["userrole"] = query.value("userrole");
		users.append(user);
	}
	return users;
}
