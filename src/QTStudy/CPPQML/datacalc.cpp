#include "datacalc.hpp"

DataCalc::DataCalc(QObject *parent) : QObject(parent)
{

}

qreal DataCalc::value() const
{
    return m_value;
}

void DataCalc::setValue(qreal value)
{
    m_value = value;
}

DataCalc::CalcType DataCalc::type() const
{
    return m_type;
}

void DataCalc::setType(const CalcType &type)
{
    m_type = type;
}
