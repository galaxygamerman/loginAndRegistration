#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QObject>
#include <QDebug>
#include <QStorageInfo>

class FileManager : public QObject
{
	Q_OBJECT
public:
	explicit FileManager(QObject *parent = nullptr);

	Q_INVOKABLE QStringList getUsbDrives();
	Q_INVOKABLE bool copyCsvToDrive(QString drivePath);
};

#endif // FILEMANAGER_H
