#include "codebehind.hpp"

CodeBehind::CodeBehind(QObject* parent) : QObject(parent) {
  helper = new UDPSenderReceiver(UDPSenderReceiver::Receiver, 8845, 8848);
  connect(helper, &UDPSenderReceiver::receive, this, &CodeBehind::receive);
}

void CodeBehind::receive(const QString &msg) {
  emit receiveMsg(msg);
}
void CodeBehind::send(const QString str) {
  helper->send(str.toUtf8());
}

CodeBehind::~CodeBehind() {
  helper->deleteLater();
}
