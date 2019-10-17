#include "modbusnetclient.hpp"

ModbusNetClient::ModbusNetClient(QObject* parent) : QObject(parent) {
  m_reads.append(QModbusDataUnit(QModbusDataUnit::InputRegisters, 0, 10));
  m_reads.append(QModbusDataUnit(QModbusDataUnit::HoldingRegisters, 0, 10));
}

ModbusNetClient::~ModbusNetClient() { qDebug() << "~ModbusNetClient()"; }

void ModbusNetClient::startServer(const QUrl& url, int interval) {
  if (interval >= 100)
    m_interval = interval;
  else
    m_interval = 100;
  m_url = url;

  if (client == nullptr) {
    client = new QModbusTcpClient(this);

    client->setTimeout(m_timeout);
    client->setNumberOfRetries(3);

    connect(client, &QModbusTcpClient::errorOccurred, this,
            &ModbusNetClient::onErrorOccured);
    connect(client, &QModbusTcpClient::stateChanged, this,
            &ModbusNetClient::onStateChanged);
  } else {
    client->disconnectDevice();
  }

  client->setConnectionParameter(QModbusDevice::NetworkAddressParameter,
                                 m_url.host());
  client->setConnectionParameter(QModbusDevice::NetworkPortParameter,
                                 m_url.port());

  if (m_timer == nullptr) {
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &ModbusNetClient::exec);
  }
  if (!m_timer->isActive())
    m_timer->start(interval);
  qDebug() << "Modbus:Connect to " << m_url.toString();
  m_flag = false;
}

void ModbusNetClient::writeToServer(int offset, const QVector<quint16>& datas) {
  if (connectServer()) {
    auto reply = client->sendWriteRequest(
        QModbusDataUnit(QModbusDataUnit::HoldingRegisters, offset, datas), 1);
    if (reply == nullptr) {
      qDebug() << client->errorString();
      return;
    }

    if (!reply->isFinished()) {
      connect(reply, &QModbusReply::finished, this,
              &ModbusNetClient::writeReady);
    } else {
      reply->deleteLater();
      qDebug() << "Remove only[write]";
      // delete  reply;
    }
  }
}

bool ModbusNetClient::connectServer() {
  if (client->state() == QModbusDevice::ConnectedState) {
    return true;
  }

  return client->connectDevice();
}

void ModbusNetClient::stopServer() {
  m_flag = true;
  if (client == nullptr || client->state() != QModbusDevice::ConnectedState)
    return;

  if (m_timer != nullptr) {
    m_timer->stop();
    qDebug() << "timer stopped.";
  }
  if (client != nullptr) {
    client->disconnectDevice();
    qDebug() << "client disconnect" << client->state();
  }

  qDebug() << "Modbus:Disonnect from " << m_url.toString();
}

void ModbusNetClient::readReady() {
  QModbusReply* reply = qobject_cast<QModbusReply*>(sender());
  if (reply == nullptr)
    return;
  if (reply->error() != QModbusDevice::NoError) {
    qDebug() << reply->errorString();
    reply->deleteLater();
    return;
  }
  const QModbusDataUnit data = reply->result();
  if (data.registerType() == QModbusDataUnit::InputRegisters) {
    qDebug() << data.values();
  } else if (data.registerType() == QModbusDataUnit::HoldingRegisters) {
    qDebug() << data.values();
  }
  reply->deleteLater();
}

void ModbusNetClient::exec() {
  doQuery();
  //  doWrite();
}

void ModbusNetClient::doQuery() {
  if (!connectServer()) {
    return;
  }
  for (int i = 0; i < m_reads.length(); i++) {
    if (m_flag)
      break;
    QModbusReply* reply;
    try {
      reply = client->sendReadRequest(
          static_cast<QModbusDataUnit>(m_reads.at(i)), 1);
    } catch (QException& e) {
      qDebug() << e.what();
      return;
    }

    if (reply != nullptr) {
      if (!reply->isFinished()) {
        connect(reply, &QModbusReply::finished, this,
                &ModbusNetClient::readReady);
      } else {
        qDebug() << "Remove reply.";
        reply->deleteLater();
      }
    } else {
      emit netStateChanged(client->error(), client->errorString());
    }
    QEventLoop loop;
    QTimer::singleShot(10, &loop, SLOT(quit()));
    loop.exec();
  }
}

void ModbusNetClient::onStateChanged(QModbusDevice::State state) {
  //  AppSetting.SetConnected(state == QModbusDevice::ConnectedState);
  if (state == QModbusDevice::ConnectedState) {
    emit netStateChanged(0, "Ethernet communication OK.");
  } else if (state == QModbusDevice::UnconnectedState) {
    emit netStateChanged(-1, "Ethernet communication failed.");
  } else {
    // Other skip
  }
}

void ModbusNetClient::onErrorOccured(QModbusDevice::Error error) {
  Q_UNUSED(error)
  qDebug() << client->errorString();
  emit netStateChanged(-1, "Ethernet communication failed.");
}

void ModbusNetClient::writeReady() {
  QModbusReply* reply = qobject_cast<QModbusReply*>(sender());
  if (reply == nullptr)
    return;

  if (reply->error() != QModbusDevice::NoError) {
    qDebug() << Q_FUNC_INFO << reply->errorString();
    emit writeErrored(reply->errorString());
  } else {
    qDebug() << Q_FUNC_INFO << "write successful";
  }
  reply->deleteLater();
}
