#ifndef CODEBEHIND_HPP
#define CODEBEHIND_HPP

#include "modbusnetclient.hpp"
#include <QDebug>
#include <QtCore/QObject>
#include <QtCore/qglobal.h>

class CodeBehind : public QObject
{
  Q_OBJECT
public:
  explicit CodeBehind(QObject* parent = nullptr);
  ~CodeBehind();

  Q_INVOKABLE void start(const QString& ip);
  Q_INVOKABLE void stop();
  Q_INVOKABLE void write(int offset, const QVariant& data);
signals:
  void msgChanged(const QString& msg);
public slots:
  void stateChanged(int state, const QString& msg);

private:
  ModbusNetClient* m_client = nullptr;
};

#endif // CODEBEHIND_HPP
