#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "databasemanager.h"
#include "userabstractlistmodel.h"
#include "userabstracttablemodel.h"

int main(int argc, char *argv[])
{
	QGuiApplication app(argc, argv);

	DatabaseManager* dbManager = new DatabaseManager(&app);
	UserAbstractListModel* userAbstractListModel = new UserAbstractListModel();
	userAbstractListModel->fetchUsers();
	UserAbstractTableModel* userAbstractTableModel = new UserAbstractTableModel(dbManager);
	userAbstractTableModel->fetchUsers();

	QQmlApplicationEngine engine;

	engine.rootContext()->setContextProperty("dbManager", dbManager);
	engine.rootContext()->setContextProperty("userAbstractListModel", userAbstractListModel);
	engine.rootContext()->setContextProperty("userAbstractTableModel", userAbstractTableModel);

	QObject::connect(
		&engine,
		&QQmlApplicationEngine::objectCreationFailed,
		&app,
		[]() { QCoreApplication::exit(-1); },
		Qt::QueuedConnection);
	engine.loadFromModule("loginAndRegistration", "Main");

	return app.exec();
}
