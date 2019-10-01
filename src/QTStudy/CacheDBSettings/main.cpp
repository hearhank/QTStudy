#include <QDebug>
#include <QGuiApplication>
#include <QJSEngine>
#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlEngine>

#include "datacache.hpp"
#include "singleton.hpp"

int main(int argc, char* argv[]) {
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QGuiApplication app(argc, argv);

  qmlRegisterSingletonType<DataCache>("Proton.Datas", 1, 0, "Caches", [] (QQmlEngine *engine, QJSEngine *scriptEngine) -> QObject*{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)
    auto item = Singleton<DataCache>::Installace();
    item->load();
    item->print();
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

  // QObject::connect(&app, &QGuiApplication::lastWindowClosed,
  // &helper,&Helper::unload);
  return app.exec();
}
