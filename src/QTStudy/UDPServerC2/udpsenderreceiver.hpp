#ifndef UDPSENDERRECEIVER_HPP
#define UDPSENDERRECEIVER_HPP

#include <QtCore/QObject>
#include <QtCore/qglobal.h>
#include <QUdpSocket>
#include <QNetworkInterface>


class UDPSenderReceiver : public QObject
{

  Q_OBJECT
public:
  enum SenderReceiver { Sender, Receiver };
  explicit UDPSenderReceiver(SenderReceiver sr, quint16 port1, quint16 port2,
                             QObject* parent = nullptr);

  Q_INVOKABLE void send(const QString& str);
  Q_INVOKABLE QString getIP() const;

signals:
  void receive(const QString& str);
public slots:
  void receiver();

private:
  QUdpSocket* socket=nullptr;
  QHostAddress groupAddrIP4;
  quint16 m_readPort = 8848;
  quint16 m_writePort = 8858;
};

#endif // UDPSENDERRECEIVER_HPP
