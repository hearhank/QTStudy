#include "dataitem.hpp"

DataItem::DataItem(QObject *parent) : QObject(parent),
    m_value(QVariant()),
    m_convertType(ConverterType::DataConverter::None),
    m_load(false),
    m_desc(nullptr)
{

}

DataItem::~DataItem() {
    if (m_desc != nullptr)
        m_desc->deleteLater();
}

void DataItem::Load(const QList<DataItem*> datas) {
    if (m_load)
        return;

    if (m_refNames.count() > 0) {
        QListIterator<DataItem*> i(datas);
        while (i.hasNext()) {
            const DataItem* item = i.next();
            if (m_refNames.contains(item->name())) {
                m_refItems.append(const_cast<DataItem*>(item));
            }
        }
        //TODO
        //this->setConvertType(ConverterType::NameC);
    }
    m_load = true;
}

QVariant DataItem::value() const {
    return m_value;
}

void DataItem::setValue(const QVariant &Value) {
    if (m_value != Value) {
        m_value = Value;
        emit valueChanged(m_value);
    }
}

QString DataItem::name() const
{
    return m_name;
}

void DataItem::setName(const QString &Name)
{
    m_name = Name;
}

QStringList DataItem::refNames() const
{
    return m_refNames;
}

void DataItem::setRefNames(const QStringList &RefNames)
{
    m_refNames = RefNames;
}

bool DataItem::isLoad() const
{
    return m_load;
}

ConverterType::DataConverter DataItem::convertType() const
{
    return m_convertType;
}

void DataItem::setConvertType(const ConverterType::DataConverter &converter)
{
    m_convertType = converter;
}

QList<DataItem *> DataItem::refItems() const
{
    return m_refItems;
}

DataDesc *DataItem::desc() const
{
    return m_desc;
}

void DataItem::setDesc(DataDesc *desc)
{
    m_desc = desc;
}

