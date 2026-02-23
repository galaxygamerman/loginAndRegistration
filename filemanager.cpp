#include "filemanager.h"

FileManager::FileManager(QObject *parent)
	: QObject{parent} {}

QStringList FileManager::getUsbDrives() {
	QStringList drives;
	for (const QStorageInfo &drive : QStorageInfo::mountedVolumes()) {
		if (drive.isValid() && drive.isReady() && !drive.isReadOnly()) {
			drives << drive.rootPath();
		}
	}
	return drives;
}

bool FileManager::copyCsvToDrive(QString drivePath) {
	QString src = "database/user.csv", dest = QDir(drivePath).filePath("user.csv");

	if (QFile::exists(dest)) { QFile::remove(dest); }

	if (!QFile::copy(src, dest)) {
		qFatal() << "CSV file transfer not successful.";
		return false;
	}

	qDebug() << "CSV file transfered successful.";
	return true;
}
