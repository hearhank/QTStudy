#include "codebehind.hpp"

CodeBehind::CodeBehind(QObject* parent) : QObject(parent) {
  //  helper = new UDPSenderReceiver(UDPSenderReceiver::Sender, 8848, 8845);
  m_server = (ServerSkt*)new ServerSktUdp();
  m_server->start(QHostAddress("127.0.0.1"), 8848);

  //connect(helper, &UDPSenderReceiver::receive, this, &CodeBehind::receive);
}

void CodeBehind::send(const QString str) {
  //  helper->send(str.toUtf8());
  m_server->send("key", str.toUtf8());
}

void CodeBehind::receive(const QString& msg) {
  qDebug() << Q_FUNC_INFO << msg;
  emit receiveMsg(msg);
}

CodeBehind::~CodeBehind() {
  //  helper->deleteLater();
  m_server->kill("key");
  m_server->stop();
  m_server->deleteLater();
}
