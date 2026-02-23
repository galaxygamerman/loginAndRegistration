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

	bool syncToCsv();

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
	Q_INVOKABLE QVariantMap getUserData(const QString &username);
	Q_INVOKABLE QVariantList getAllUserData();
	Q_INVOKABLE bool updateUser(const QString &oldUsername,
								const QString &newUsername,
								const QString &password,
								const QString &fullname,
								const QString &email,
								const QString &phone,
								const QString &age,
								const QString &gender,
								const QString &userrole);
	Q_INVOKABLE bool deleteUsers(const QStringList &usernames);

	Q_INVOKABLE QStringList getUsbDrives() {
		QStringList drives;
		for (const QStorageInfo &drive : QStorageInfo::mountedVolumes()) {
			drives << drive.rootPath();
		}
		return drives;
	}
	Q_INVOKABLE bool copyCsvToDrive(QString drivePath){
		QString src = "database/user.csv",
			dest = QDir(drivePath).filePath("user.csv");

		if (QFile::exists(dest)){
			QFile::remove(dest);
		}

		if(!QFile::copy(src,dest)){
			qFatal() << "CSV file transfer not successful.";
			return false;
		}

		qDebug() << "CSV file transfered successful.";
		return true;
	}
};

#endif // DATABASEMANAGER_H
