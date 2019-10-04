#include "communication.hpp"

Communication::Communication(QObject* parent)
    : QObject(parent), m_client(nullptr) {
  connect(&m_store, &ModbusDataStore::failed, this, &Communication::failed);
}

Communication::~Communication() { close(); }

void Communication::startTCP(const QString& ip, const int port, const int id) {
  if (m_flag)
    return;
  m_port = port;
  m_serverAddr = id;
  m_ipaddress = ip;
  if (m_client == nullptr) {
    m_client = new QModbusTcpClient(this);
    m_client->setConnectionParameter(QModbusDevice::NetworkAddressParameter,
                                     QVariant(m_ipaddress));
    m_client->setConnectionParameter(QModbusDevice::NetworkPortParameter,
                                     QVariant(m_port));

    connect(m_client, &QModbusClient::stateChanged, this,
            &Communication::stateChanged);
  }

  connect(&m_timer, &QTimer::timeout, this, &Communication::runSync);
  m_timer.start(m_interval);
  m_flag = true;
}

void Communication::close() {
  m_timer.stop();
  disconnect(&m_timer, &QTimer::timeout, this, &Communication::runSync);
  m_flag = false;
  disconnect(&m_store, &ModbusDataStore::failed, this, &Communication::failed);
  if (m_client != nullptr) {
    if (m_client->state() != QModbusDevice::State::UnconnectedState)
      m_client->disconnectDevice();
    m_client->deleteLater();
  }
}

void Communication::runSync() {
  if (!m_flag)
    return;

  // QMutexLocker lock(&m_mutex);
  if (open()) {

    // read
    foreach (auto item, m_reads) {
      if (!m_flag)
        break;
      auto reply = m_client->sendReadRequest(
          QModbusDataUnit(item.registerType(), item.startAddress(),
                          static_cast<quint16>(item.valueCount())),
          m_serverAddr);
      if (reply == nullptr) {
        if (m_client->error() != QModbusDevice::NoError)
          emit failed(m_client->errorString());
        return;
      }

      if (!reply->isFinished()) {
        connect(reply, &QModbusReply::finished, &m_store,
                &ModbusDataStore::readFinished);
      } else {
        delete reply;
      }
    }

    // write
    while (m_writes.count() > 0) {
      if (!m_flag)
        break;
      auto reply = m_client->sendWriteRequest(m_writes.dequeue(), m_serverAddr);
      if (reply == nullptr) {
        if (m_client->error() != QModbusDevice::NoError)
          emit failed(m_client->errorString());
        return;
      }

      if (!reply->isFinished()) {
        connect(reply, &QModbusReply::finished, &m_store,
                &ModbusDataStore::writeFinished);
      } else {
        delete reply;
      }
    }
  }
}

int Communication::interval() const { return m_interval; }

void Communication::setInterval(int interval) { m_interval = interval; }

bool Communication::open() {
  if (m_client == nullptr) {
    // TODO
    m_client = new QModbusTcpClient(nullptr);
    m_client->setConnectionParameter(QModbusDevice::NetworkAddressParameter,
                                     QVariant(m_ipaddress));
    m_client->setConnectionParameter(QModbusDevice::NetworkPortParameter,
                                     QVariant(m_port));
  }
  if (m_client->state() == QModbusDevice::State::UnconnectedState) {
    return m_client->connectDevice();
  } else {
    return (m_client->state() == QModbusDevice::State::ConnectedState);
  }
}

QString Communication::ipaddress() const { return m_ipaddress; }

void Communication::setIpaddress(const QString& ipaddress) {
  m_ipaddress = ipaddress;
}

void Communication::setRead(const QModbusDataUnit::RegisterType regType,
                            const int startAddress, const quint16 length) {
  m_reads.append(QModbusDataUnit(regType, startAddress, length));
}

void Communication::setWrite(const int startAddress,
                             const QList<quint16>& datas) {
  QModbusDataUnit unit(QModbusDataUnit::RegisterType::HoldingRegisters);
  unit.setStartAddress(startAddress);
  unit.setValues(datas.toVector());
  m_writes.append(unit);
}

void Communication::stateChanged(QModbusDevice::State state) {
  qDebug() << "Comm State Changed:" << state;
}

int Communication::port() const { return m_port; }

void Communication::setPort(int port) { m_port = port; }

int Communication::serverAddr() const { return m_serverAddr; }

void Communication::setServerAddr(int slaveID) { m_serverAddr = slaveID; }
