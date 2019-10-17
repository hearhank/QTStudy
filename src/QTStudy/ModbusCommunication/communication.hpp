#ifndef COMMUNICATION_HPP
#define COMMUNICATION_HPP

#include "modbusdatastore.hpp"
#include <QModbusClient>
#include <QModbusDataUnit>
#include <QModbusDevice>
#include <QModbusRtuSerialMaster>
#include <QModbusTcpClient>
#include <QMutexLocker>
#include <QObject>
#include <QQueue>
#include <QTimer>
#include <QVariant>
#include <QtDebug>
#include <QtSerialPort/QSerialPort>

class Communication : public QObject
{
  Q_OBJECT
public:
  explicit Communication(QObject *parent = nullptr);
  ~Communication();

  void startTCP(const QString& ip, const int port = 502, const int id = 1);
  void startRtu(const QString& com, const QSerialPort::Parity parity,
                const QSerialPort::BaudRate baudRate,
                const QSerialPort::DataBits dataBits,
                const QSerialPort::StopBits stopBits);
  void close();

  int interval() const;
  void setInterval(int interval);

  int serverAddr() const;
  void setServerAddr(int serverAddr);

  int port() const;
  void setPort(int port);

  QString ipaddress() const;
  void setIpaddress(const QString& ipaddress);

  void setRead(const QModbusDataUnit::RegisterType regType,
               const int startAddress, const quint16 length);
  void setWrite(const int startAddress, const QVector<quint16>& datas);

signals:
  void failed(const QString& msg, const int state = 1);
public slots:
  void stateChanged(QModbusDevice::State state);
private slots:
  void runSync();

private:
  bool open();
  QModbusClient* m_client;
  QMutex m_mutex;
  int m_interval = 100;
  QTimer m_timer;
  bool m_flag = false;
  int m_serverAddr = 1;
  int m_port = 502;
  QString m_ipaddress;
  QList<QModbusDataUnit> m_reads;

  QQueue<QModbusDataUnit> m_writes;

  ModbusDataStore m_store;
};

#endif // COMMUNICATION_HPP
