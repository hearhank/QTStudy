#ifndef MODBUSNETCLIENT_HPP
#define MODBUSNETCLIENT_HPP

#include <QCoreApplication>
#include <QDebug>
#include <QException>
#include <QModbusDataUnit>
#include <QModbusDevice>
#include <QModbusTcpClient>
#include <QMutex>
#include <QObject>
#include <QQueue>
#include <QThread>
#include <QTimer>
#include <QUrl>
#include <QVariant>
#include <exception>

class ModbusNetClient : public QObject {
  Q_OBJECT
public:
  explicit ModbusNetClient(QObject* parent = nullptr);
  ~ModbusNetClient();
  void startServer(const QUrl& url, int interval = 100);

  bool IsConnected() {
    QMutexLocker lock(&m_mutex);
    return client != nullptr &&
           client->state() == QModbusDevice::ConnectedState;
  }
  void writeToServer(int offset, const QVector<quint16>& datas);
signals:
  //  void error(const QString& s);
  void writeErrored(const QString errmsg);
  void netStateChanged(int state, const QString& msg);
public slots:
  void stopServer();
private slots:
  void readReady();
  void writeReady();
  void doQuery();
  void exec();

  void onStateChanged(QModbusDevice::State state);
  void onErrorOccured(QModbusDevice::Error error);

private:
  bool connectServer();
  QModbusTcpClient* client = nullptr;
  QTimer* m_timer = nullptr;
  static const int m_timeout = 500;

  QVector<QModbusDataUnit> m_reads;

  QUrl m_url;
  int m_interval;
  bool m_flag = false;
  QMutex m_mutex;
};

#endif // MODBUSNETCLIENT_HPP
