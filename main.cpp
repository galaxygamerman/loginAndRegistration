#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "databasemanager.h"

int main(int argc, char *argv[])
{
	QGuiApplication app(argc, argv);

	DatabaseManager* dbManager = new DatabaseManager(&app);

	QQmlApplicationEngine engine;

	engine.rootContext()->setContextProperty("dbManager", dbManager);

	QObject::connect(
		&engine,
		&QQmlApplicationEngine::objectCreationFailed,
		&app,
		[]() { QCoreApplication::exit(-1); },
		Qt::QueuedConnection);
	engine.loadFromModule("loginAndRegistration", "Main");

	return app.exec();
}
