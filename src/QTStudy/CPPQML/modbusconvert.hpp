#ifndef MODBUSCONVERT_HPP
#define MODBUSCONVERT_HPP

#include <QObject>
#include <QVariant>
#include <datadesc.hpp>

class ModbusConvert : public QObject
{
    Q_OBJECT
public:
    explicit ModbusConvert(QObject *parent = nullptr);
    QVariant Convert(const DataDesc* desc);
signals:

public slots:
};

#endif // MODBUSCONVERT_HPP
