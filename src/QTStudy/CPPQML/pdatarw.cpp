#include "pdatarw.hpp"

bool PDataReadWriter::isLittleEndian = true;

PDataReadWriter::PDataReadWriter(QObject *parent) : QObject(parent)
{

}

QVariant PDataReadWriter::Read(const DataNode *node) {
    try {
        if (node->desc() != nullptr) {
            if (node->desc()->dataArea() != DataDesc::Local) {
                return Read(node->desc());
            } else {
                return PSingleton<DataCache>::Installace()->get(node->name());
            }
        }
    } catch (QException ex) {
        LError() << ex.what();
    }
    return QVariant();
}

void PDataReadWriter::Write(const DataNode *node, const QVariant &val) {
}

QVariant PDataReadWriter::Read(const DataDesc *desc) {
    QVariant val;
    if (desc->dataArea() == DataDesc::Input) {
        if (desc->dataType() == DataDesc::Bit) {
            val = BitConvter::GetBitValue(
                BitConvter::ToUInt16(
                    BitConvter::GetBytes(appconf::inputArr[desc->offset()],
                                         PDataReadWriter::isLittleEndian)),
                desc->bitOffset(), desc->bitLength());
        } else {
            val = ReadInput(desc->offset(), desc->length(), desc->dataType(),
                            PDataReadWriter::isLittleEndian);
        }
    } else if (desc->dataArea() == DataDesc::Hold) {
        if (desc->dataType() == DataDesc::Bit) {
            val = BitConvter::GetBitValue(
                BitConvter::ToUInt16(
                    BitConvter::GetBytes(appconf::holdingArr[desc->offset()],
                                         PDataReadWriter::isLittleEndian)),
                desc->bitOffset(), desc->bitLength());
        } else {
            val = ReadHold(desc->offset(), desc->length(), desc->dataType(),
                           PDataReadWriter::isLittleEndian);
        }
    }
    return val;
}

QVariant PDataReadWriter::ReadInput(int offset, int length,
                                    DataDesc::DataType type, bool revers) {
    QVariant val;
    switch (type) {
    case DataDesc::Byte:
        val = BitConvter::ToByte(
            BitConvter::GetBytes(appconf::inputArr.at(offset), revers));
    case DataDesc::Boolean:
        val = BitConvter::ToBool(
            BitConvter::GetBytes(appconf::inputArr.at(offset), revers));
        break;
    case DataDesc::Short:
        val = BitConvter::ToInt16(
            BitConvter::GetBytes(appconf::inputArr.at(offset), revers));
        break;
    case DataDesc::UShort:
        val = BitConvter::ToUInt16(
            BitConvter::GetBytes(appconf::inputArr.at(offset), revers));
        break;
    case DataDesc::Int:
        val = BitConvter::ToInt32(
            BitConvter::GetBytes(appconf::inputArr.mid(offset, 2), revers));
        break;
    case DataDesc::UInt:
        val = BitConvter::ToUInt32(
            BitConvter::GetBytes(appconf::inputArr.mid(offset, 2), revers));
        break;
    case DataDesc::Float:
        throw "not support of float";
        break;
    case DataDesc::Long:
        val = BitConvter::ToInt64(
            BitConvter::GetBytes(appconf::inputArr.mid(offset, 4), revers));
        break;
    case DataDesc::ULong:
        val = BitConvter::ToUInt64(
            BitConvter::GetBytes(appconf::inputArr.mid(offset, 4), revers));
        break;
    case DataDesc::Double:
        throw "not support of double";
        break;
    case DataDesc::String:
        val = BitConvter::ToString(BitConvter::GetBytes(
                                       appconf::inputArr.mid(offset, length), revers));
        break;
    default:
        throw "not support of unknow";
        break;
    }
    return val;
}

QVariant PDataReadWriter::ReadHold(int offset, int length, DataDesc::DataType type, bool revers)
{
    QVariant val;
    switch (type) {
    case DataDesc::Byte:
        val = BitConvter::ToByte(
            BitConvter::GetBytes(appconf::holdingArr.at(offset), revers));
    case DataDesc::Boolean:
        val = BitConvter::ToBool(
            BitConvter::GetBytes(appconf::holdingArr.at(offset), revers));
        break;
    case DataDesc::Short:
        val = BitConvter::ToInt16(
            BitConvter::GetBytes(appconf::holdingArr.at(offset), revers));
        break;
    case DataDesc::UShort:
        val = BitConvter::ToUInt16(
            BitConvter::GetBytes(appconf::holdingArr.at(offset), revers));
        break;
    case DataDesc::Int:
        val = BitConvter::ToInt32(
            BitConvter::GetBytes(appconf::holdingArr.mid(offset, 2), revers));
        break;
    case DataDesc::UInt:
        val = BitConvter::ToUInt32(
            BitConvter::GetBytes(appconf::holdingArr.mid(offset, 2), revers));
        break;
    case DataDesc::Float:
        throw "not support of float";
        break;
    case DataDesc::Long:
        val = BitConvter::ToInt64(
            BitConvter::GetBytes(appconf::holdingArr.mid(offset, 4), revers));
        break;
    case DataDesc::ULong:
        val = BitConvter::ToUInt64(
            BitConvter::GetBytes(appconf::holdingArr.mid(offset, 4), revers));
        break;
    case DataDesc::Double:
        throw "not support of double";
        break;
    case DataDesc::String:
        val = BitConvter::ToString(BitConvter::GetBytes(
                                       appconf::holdingArr.mid(offset, length), revers));
        break;
    default:
        throw "not support of unknow";
        break;
    }
    return val;
}
