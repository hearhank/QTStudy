#include "udpsenderreceiver.hpp"

UDPSenderReceiver::UDPSenderReceiver(UDPSenderReceiver::SenderReceiver sr,
                                     quint16 port1, quint16 port2,
                                     QObject* parent)
    : QObject(parent), groupAddrIP4(QStringLiteral("239.255.43.21")) {
  m_readPort = port1;
  m_writePort = port2;
   socket = new QUdpSocket(this);
  if (sr == SenderReceiver::Sender) {
    socket->bind(QHostAddress(QHostAddress::AnyIPv4), m_readPort);
    socket->setSocketOption(QAbstractSocket::MulticastTtlOption, 1);
  } else {
    socket->bind(QHostAddress(QHostAddress::AnyIPv4), m_readPort,
                 QUdpSocket::ShareAddress);
  }
  socket->joinMulticastGroup(groupAddrIP4);
  connect(socket, &QUdpSocket::readyRead, this, &UDPSenderReceiver::receiver);
}

void UDPSenderReceiver::send(const QString& str) {

  socket->writeDatagram(QString("%1 from %2").arg(str,getIP()).toUtf8(), groupAddrIP4, m_writePort);
}

QString UDPSenderReceiver::getIP() const {
  QString strIpAddress;
  QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
  // 获取第一个本主机的IPv4地址
  int nListSize = ipAddressesList.size();
  for (int i = 0; i < nListSize; ++i) {
    if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
        ipAddressesList.at(i).toIPv4Address()) {
      strIpAddress = ipAddressesList.at(i).toString();
      break;
    }
  }
  // 如果没有找到，则以本地IP地址为IP
  if (strIpAddress.isEmpty())
    strIpAddress = QHostAddress(QHostAddress::LocalHost).toString();
  return strIpAddress;
}

void UDPSenderReceiver::receiver() {
  QByteArray datagram;

  // using QUdpSocket::readDatagram (API since Qt 4)
  while (socket->hasPendingDatagrams()) {
    datagram.resize(int(socket->pendingDatagramSize()));
    socket->readDatagram(datagram.data(), datagram.size());
    emit receive(QString(datagram));
    qDebug() << QString(datagram);
  }
}
