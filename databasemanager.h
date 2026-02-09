#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QDebug>
#include <QObject>
#include <QtSql>
#include <QtQml/qqmlregistration.h>

class DatabaseManager : public QObject
{
private:
	Q_OBJECT
	QML_ELEMENT
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
};

#endif // DATABASEMANAGER_H
