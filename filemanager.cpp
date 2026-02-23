#include "filemanager.h"

FileManager::FileManager(DatabaseManager *dbPtr, QObject *parent)
	: QObject{parent}
	, dbManager(dbPtr) {}

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
	QString src = this->pathToCsvFile,
			dest = QDir(drivePath).filePath(QFileInfo(this->pathToCsvFile).fileName());

	if (QFile::exists(dest)) { QFile::remove(dest); }

	if (!QFile::copy(src, dest)) {
		qFatal() << "CSV file transfer not successful.";
		return false;
	}

	qDebug() << "CSV file transfered successful.";
	return true;
}

bool FileManager::syncToCsv() {
	QFile theFile(this->pathToCsvFile);
	if (!theFile.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text)) {
		qFatal() << theFile.fileName()
				 << "not created because the script file could not be opened.";
		return false;
	}

	QTextStream print(&theFile);
	print << "username,password,fullname,email,phone,age,gender,userrole\n";

	QVariantList usersList = dbManager->getAllUserData();

	for (const auto &row : std::as_const(usersList)) {
		QVariantMap user = row.toMap();
		print << QString("%1,%2,%3,%4,%5,%6,%7,%8\n")
					 .arg(user["username"].toString(),
						  user["password"].toString(),
						  user["fullname"].toString(),
						  user["email"].toString(),
						  user["phone"].toString(),
						  user["age"].toString(),
						  user["gender"].toString(),
						  user["userrole"].toString());
	}

	qDebug() << "CSV file" << theFile.fileName() << "is synced up.";
	theFile.close();
	return true;
}
