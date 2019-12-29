#ifndef CLIENTSKT_HPP
#define CLIENTSKT_HPP

#include <QTcpSocket>
#include <QUdpSocket>
#include "LibNet_global.hpp"

class LIBNET_EXPORT ClientSkt : public QObject
{
  Q_OBJECT

public:
  ClientSkt(QObject *parent=nullptr);
  virtual ~ClientSkt();

  virtual QString name() const { return "General"; }

  bool plug(const QHostAddress& ip, quint16 port);
  void unplug();
  void send(const QString& data);

  const QHostAddress& addr() const { return m_ip; }
  quint16 port() const { return m_port; }

signals:
  void unpluged();

  void message(const QString& msg);
  void dumpbin(const QString& title, const char* data, quint32 len);

  void countRecv(qint32 bytes);
  void countSend(qint32 bytes);

protected:
  void dump(const char* buf, qint32 len, bool isSend);
  void show(const QString& msg);
  void setError(const QString& err);

  void recordRecv(qint32 bytes);
  void recordSend(qint32 bytes);

  virtual bool open() =0;
  virtual void close() =0;
  virtual void send(const QByteArray& data) =0;

private:
  QHostAddress m_ip;
  quint16 m_port;

  QString m_error;
};

class LIBNET_EXPORT ClientSktTcp : public ClientSkt
{
  Q_OBJECT

public:
  ClientSktTcp(QObject *parent=nullptr);
  ~ClientSktTcp();

  virtual QString name() const { return "TCP"; }

protected:
  virtual bool open();
  virtual void close();
  virtual void send(const QByteArray& bin);

private slots:
  void asynConn();
  void newData();
  void closed();
  void error();

private:
  QTcpSocket m_socket;
};

class LIBNET_EXPORT ClientSktUdp : public ClientSkt
{
  Q_OBJECT

public:
  ClientSktUdp(QObject *parent=nullptr);
  ~ClientSktUdp();

  virtual QString name() const { return "UDP"; }

protected:
  virtual bool open();
  virtual void close();
  virtual void send(const QByteArray& bin);

private slots:
  void asynConn();
  void newData();
  void closed();
  void error();

private:
  QUdpSocket m_socket;
};
#endif // CLIENTSKT_HPP
