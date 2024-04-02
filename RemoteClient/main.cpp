#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "../RemoteServer/hosttest.h"
#include "modemanager.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    // QLoggingCategory::setFilterRules("qt.remoteobjects.debug=true\n"
    //                                  "qt.remoteobjects.warning=true\n"
    //                                  "qt.remoteobjects.info=true\n"
    //                                  "qt.remoteobjects.models.debug=true\n"
    //                                  "qt.remoteobjects.models.warning=true\n"
    //                                  "qt.remoteobjects.models.info=true\n"
    //                                  "qt.remoteobjects.io.debug=true\n"
    //                                  "qt.remoteobjects.io.warning=true\n"
    //                                  "qt.remoteobjects.io.info=true\n");
    // QLoggingCategory::setFilterRules("qt.remoteobjects.*=true\n"
    //                                  "qt.remoteobjects.models.*=true\n"
    //                                  "qt.remoteobjects.io.*=true\n");

    QGuiApplication app(argc, argv);

    static ModeManager tugs(QUrl("local:tugs"), QStringLiteral("TiQmlObjectListModel"));

    QQmlApplicationEngine engine;

    qmlRegisterUncreatableType<ModeManager>("ModeManager", 1, 0, "ModeManager", "");
    qmlRegisterType<Data>("Data", 1, 0, "Data");
    qmlRegisterType<Actor>("Actor", 1, 0, "Actor");

    engine.rootContext()->setContextProperty("$tugs", &tugs);

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
