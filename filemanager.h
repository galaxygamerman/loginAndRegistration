#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QObject>
#include <QDebug>
#include <QStorageInfo>
#include "databasemanager.h"

class FileManager : public QObject
{
	Q_OBJECT

private:
	DatabaseManager *dbManager;

public:
	explicit FileManager(DatabaseManager *dbPtr = new DatabaseManager(),
						 QObject *parent = nullptr);

	Q_INVOKABLE QStringList getUsbDrives();
	Q_INVOKABLE bool copyCsvToDrive(QString drivePath);

public slots:
	bool syncToCsv();
};

#endif // FILEMANAGER_H
