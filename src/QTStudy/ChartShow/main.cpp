#include "dataitems.hpp"
#include "trendingtimer.hpp"
#include <QApplication>
#include <QDateTime>
#include <QDir>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QQuickView>
#include <QtDebug>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);

    qmlRegisterType<DataDesc>("Proton.Datas", 1, 0, "DataDesc");
    qmlRegisterType<DataItem>("Proton.Datas", 1, 0, "DataItem");
    qmlRegisterType<DataItems>("Proton.Datas", 1, 0, "DataItems");
    qmlRegisterType<TrendingTimer>("Proton.Datas", 1, 0, "TrendingTimer");

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
