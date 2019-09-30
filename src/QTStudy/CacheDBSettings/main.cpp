#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QJSEngine>

#include "Helper.hpp"
#include "datacache.hpp"


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterSingletonType<DataCache>("Proton.Datas", 1, 0, "Caches", [] (QQmlEngine *engine, QJSEngine *scriptEngine) -> QObject*{
        Q_UNUSED(engine)
        Q_UNUSED(scriptEngine)
        auto item = Singleton<DataCache>::Installace();
        item->load("SLmini");
        return item;
    });


    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url] (QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
