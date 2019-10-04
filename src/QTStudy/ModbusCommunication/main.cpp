#include <QtCore/QCoreApplication>
#include <QtCore/qglobal.h>

#include "communication.hpp"

int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);

  Communication comm;
  comm.setRead(QModbusDataUnit::InputRegisters, 0, 10);
  comm.setRead(QModbusDataUnit::HoldingRegisters, 0, 10);
  comm.startTCP("127.0.0.1");
  comm.setWrite(0, QList<quint16>{16});
  qDebug() << Q_FUNC_INFO;
  return a.exec();
}
