#ifndef CODEBEHIND_HPP
#define CODEBEHIND_HPP

#include <QtCore/QObject>
#include <QtCore/qglobal.h>
#include "udpsenderreceiver.hpp"

class CodeBehind : public QObject
{
  Q_OBJECT
public:
  explicit CodeBehind(QObject *parent = nullptr);
  ~CodeBehind();
  Q_INVOKABLE void send(const QString str);
signals:
  void receiveMsg(const QString& msg);
public slots:
  void receive(const QString& msg);
private:
  UDPSenderReceiver* helper;
};

#endif // CODEBEHIND_HPP
