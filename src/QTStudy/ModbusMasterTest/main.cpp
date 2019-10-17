#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQmlEngine>
#include <QQuickView>

#include <QtCore/qglobal.h>
#if QT_VERSION >= 0x050000
#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>
#else
#endif

#include "codebehind.hpp"

int main(int argc, char *argv[])
{
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QGuiApplication app(argc, argv);

  QQmlApplicationEngine engine;
  const QUrl url(QStringLiteral("qrc:/main.qml"));

  QQuickView viewer;
  QObject::connect(viewer.engine(), &QQmlEngine::quit, &viewer,
                   &QWindow::close);

  CodeBehind bCode(&viewer);
  // appContent.setClient(&bCode);

  viewer.rootContext()->setContextProperty("bCode", &bCode);
  viewer.setSource(QUrl("qrc:/main.qml"));

  QObject::connect(&app, &QGuiApplication::lastWindowClosed, &bCode,
                   &CodeBehind::stop);

  //  QObject::connect(
  //      &engine, &QQmlApplicationEngine::objectCreated, &app,
  //      [url](QObject* obj, const QUrl& objUrl) {
  //        if (!obj && url == objUrl)
  //          QCoreApplication::exit(-1);
  //      },
  //      Qt::QueuedConnection);
  //  engine.load(url);

  return app.exec();
}
