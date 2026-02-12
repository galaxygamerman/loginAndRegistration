#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QDebug>
#include <QObject>
#include <QtSql>

class DatabaseManager : public QObject
{
private:
	Q_OBJECT
	QSqlDatabase myDB;

public:
	explicit DatabaseManager(QObject *parent = nullptr);

	// Q_INVOKABLE allows this to be called from QML
	Q_INVOKABLE bool registerUser(const QString &username,
								  const QString &password,
								  const QString &fullname,
								  const QString &email,
								  const QString &phone,
								  const QString &age,
								  const QString &gender,
								  const QString &userrole);

	Q_INVOKABLE bool checkUser(const QString &username, const QString &password, const QString &userrole);

	Q_INVOKABLE QVariantHash getUserData(const QString &username);

	Q_INVOKABLE QVariantList getAllUserData();
};

#endif // DATABASEMANAGER_H
