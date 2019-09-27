#include "modbusconvert.hpp"

ModbusConvert::ModbusConvert(QObject *parent) : QObject(parent)
{

}

QVariant ModbusConvert::Convert(const DataDesc *desc) {
    //TODO
    if (desc == nullptr)
        return "";
    return QVariant((desc->offset() + 1) * desc->length());
}
