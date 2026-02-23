#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "databasemanager.h"
#include "filemanager.h"
#include "userabstractlistmodel.h"
#include "userabstracttablemodel.h"

int main(int argc, char *argv[])
{
	QGuiApplication app(argc, argv);

	DatabaseManager* dbManager = new DatabaseManager(&app);
	FileManager* fileManager = new FileManager();
	UserAbstractListModel* userAbstractListModel = new UserAbstractListModel();
	userAbstractListModel->fetchUsers();
	UserAbstractTableModel* userAbstractTableModel = new UserAbstractTableModel(dbManager);
	userAbstractTableModel->fetchUsers();

	fileManager->syncToCsv(); // Needed to do the very first sync

	QQmlApplicationEngine engine;

	engine.rootContext()->setContextProperty("dbManager", dbManager);
	engine.rootContext()->setContextProperty("fileManager", fileManager);
	engine.rootContext()->setContextProperty("userAbstractListModel", userAbstractListModel);
	engine.rootContext()->setContextProperty("userAbstractTableModel", userAbstractTableModel);

	QObject::connect(dbManager,
					 &DatabaseManager::databaseChanged,
					 fileManager,
					 &FileManager::syncToCsv);
	QObject::connect(
		&engine,
		&QQmlApplicationEngine::objectCreationFailed,
		&app,
		[]() { QCoreApplication::exit(-1); },
		Qt::QueuedConnection);
	engine.loadFromModule("loginAndRegistration", "Main");

	return app.exec();
}
