#include "datadesc.hpp"

DataDesc::DataDesc(QObject *parent) : QObject(parent),
    m_offset(0),
    m_length(1),
    m_bitOffset(0),
    m_bitLength(1),
    m_dataType(UShort),
    m_dataArea(Hold)
{

}

DataDesc::~DataDesc() {
}

int DataDesc::offset() const
{
    return m_offset;
}

void DataDesc::setOffset(int offset)
{
    m_offset = offset;
}

int DataDesc::length() const
{
    if (m_dataType == DataType::String)
        return m_length;

    switch (m_dataType) {
    case DataType::Int:
    case DataType::UInt:
    case DataType::Float:
        return 2;
    case DataType::Long:
    case DataType::ULong:
    case DataType::Double:
        return 4;
    default:
        return 1;
    }
}

void DataDesc::setLength(int length)
{
    m_length = length;
}

int DataDesc::bitOffset() const
{
    return m_bitOffset;
}

void DataDesc::setBitOffset(int bitOffset)
{
    m_bitOffset = bitOffset;
}

int DataDesc::bitLength() const
{
    return m_bitLength;
}

void DataDesc::setBitLength(int bitLength)
{
    m_bitLength = bitLength;
}

DataDesc::DataType DataDesc::dataType() const
{
    return m_dataType;
}

void DataDesc::setDataType(const DataType &dataType)
{
    m_dataType = dataType;
}

DataDesc::DataArea DataDesc::dataArea() const
{
    return m_dataArea;
}

void DataDesc::setDataArea(const DataArea &dataArea)
{
    m_dataArea = dataArea;
}
