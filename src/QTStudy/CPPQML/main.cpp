#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "EnumTypes.hpp"
#include "Singleton.hpp"
#include "convertservers.hpp"
#include "datacalc.hpp"
#include "datadesc.hpp"
#include "datanode.hpp"
#include "datanodes.hpp"
#include "modbusconvert.hpp"
#include "nameconvert.hpp"
#include "pageoperationtimer.hpp"
#include "pagestoreoperationtimer.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    Singleton<ConvertServers>::getInstance().Register(CH::NameC,
                                                      new NameConvert());
    Singleton<ConvertServers>::getInstance().Register(CH::None,
                                                      new ModbusConvert());

    qmlRegisterType<NodeBase>("Proton.Datas", 1, 0, "NodeBase");
    qmlRegisterType<DataDesc>("Proton.Datas", 1, 0, "DataDesc");
    qmlRegisterType<DataCalc>("Proton.Datas", 1, 0, "DataCalc");
    qmlRegisterType<DataNode>("Proton.Datas", 1, 0, "DataNode");
    qmlRegisterType<DataNodes>("Proton.Datas", 1, 0, "DataNodes");
    qmlRegisterType<PageOperationTimer>("Proton.Datas", 1, 0,
                                        "PageOperationTimer");

    qmlRegisterType<CH>("Proton.Datas", 1, 0, "CH");


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
