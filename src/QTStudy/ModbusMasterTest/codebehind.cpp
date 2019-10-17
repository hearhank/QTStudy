#include "codebehind.hpp"

CodeBehind::CodeBehind(QObject *parent) : QObject(parent)
{
}

CodeBehind::~CodeBehind() {}

void CodeBehind::start(const QString& ip) {
  if (m_client == nullptr) {
    m_client = new ModbusNetClient(this);
    connect(m_client, &ModbusNetClient::netStateChanged, this,
            &CodeBehind::stateChanged);
    //    connect(m_client, &ModbusNetClient::error, this, &CodeBehind::error);
    m_client->startServer(QUrl::fromUserInput(ip + ":502"));
  }
}

void CodeBehind::stop() { m_client->stopServer(); }

void CodeBehind::write(int offset, const QVariant& data) {
  if (m_client != nullptr)
    m_client->writeToServer(
        offset, QVector<quint16>{static_cast<quint16>(data.toInt())});
}

void CodeBehind::stateChanged(int state, const QString& msg) {
  qDebug() << Q_FUNC_INFO << state << msg;
}
