#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "hosttest.h"

int main(int argc, char *argv[])
{
    // QLoggingCategory::setFilterRules("qt.remoteobjects.*=true\n"
    //                                  "qt.remoteobjects.models.*=true\n"
    //                                  "qt.remoteobjects.io.*=true\n");
    QGuiApplication app(argc, argv);
    qmlRegisterType<HostTest>("HostTest", 1, 0, "HostTest");
    qmlRegisterType<ActorO>("ActorO", 1, 0, "ActorO");
    // static HostTest test;
    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
