#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "databasemanager.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<DatabaseManager>("com.company.database", 1, 0, "DatabaseManager");

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("loginAndRegistration", "Main");

    return app.exec();
}
