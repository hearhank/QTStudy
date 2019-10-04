#ifndef MODBUSDATASTORE_HPP
#define MODBUSDATASTORE_HPP

#include <QDebug>
#include <QModbusDataUnit>
#include <QModbusDevice>
#include <QModbusReply>
#include <QtCore/QObject>
#include <QtCore/qglobal.h>

class ModbusDataStore : public QObject
{
  Q_OBJECT
public:
  explicit ModbusDataStore(QObject *parent = nullptr);

signals:
  void failed(const QString& msg, const int state = 1);
public slots:
  void readFinished();
  void writeFinished();
};

#endif // MODBUSDATASTORE_HPP
