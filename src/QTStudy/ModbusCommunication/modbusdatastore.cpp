#include "modbusdatastore.hpp"

ModbusDataStore::ModbusDataStore(QObject *parent) : QObject(parent)
{
  
}

void ModbusDataStore::readFinished() {
  //  qDebug() << Q_FUNC_INFO;
  auto reply = qobject_cast<QModbusReply*>(sender());
  if (reply == nullptr)
    return;
  if (reply->error() == QModbusDevice::NoError) {
    auto data = reply->result();
    // TODO
    // qDebug() << "Read OK of address " << data.startAddress() << ",with "
    //         << data.valueCount() << " of length.";
  } else if (reply->error() == QModbusDevice::ProtocolError) {
    emit failed(reply->errorString());
  } else {
    emit failed(reply->errorString());
  }
  reply->deleteLater();
  // qDebug() << "reply->deleteLater";
}

void ModbusDataStore::writeFinished() {
  auto reply = qobject_cast<QModbusReply*>(sender());
  if (reply == nullptr)
    return;
  if (reply->error() == QModbusDevice::NoError) {
    auto data = reply->result();
    qDebug() << "Write OK of address " << data.startAddress();
    // TODO
  } else if (reply->error() == QModbusDevice::ProtocolError) {
    emit failed(reply->errorString());
  } else {
    emit failed(reply->errorString());
  }
  reply->deleteLater();
}
