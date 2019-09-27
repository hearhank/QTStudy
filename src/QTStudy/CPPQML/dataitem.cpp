#include "dataitem.hpp"

DataItem::DataItem(QObject *parent) : QObject(parent),
    m_value(QVariant()),
    m_convertType(CH::DataConverter::None),
    m_load(false),
    m_desc(nullptr),
    m_unit(""),
    m_eletype(EleType::Label),
    m_enabled(true)
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

void DataItem::setValue(const QVariant &value) {
    if (m_value != value) {
        m_value = value;
        emit valueChanged(m_value);
    }
}

QString DataItem::name() const
{
    return m_name;
}

void DataItem::setName(const QString &name)
{
    if (m_name != name) {
        m_name = name;
        emit nameChanged(m_name);
    }
}

QStringList DataItem::refNames() const
{
    return m_refNames;
}

void DataItem::setRefNames(const QStringList &refNames)
{
    m_refNames = refNames;
}

bool DataItem::isLoad() const
{
    return m_load;
}

CH::DataConverter DataItem::convertType() const
{
    return m_convertType;
}

void DataItem::setConvertType(const CH::DataConverter &converter)
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

QString DataItem::unit() const {
    return m_unit;
}

void DataItem::setUnit(const QString &unit) {
    if (m_unit != unit) {
        m_unit = unit;
        emit unitChanged(m_unit);
    }
}

DataItem::EleType DataItem::eletype() const {
    return m_eletype;
}

int DataItem::getEletype() {
    qDebug() << m_eletype;
    return m_eletype;
}

void DataItem::setEletype(const EleType &elementType) {
    if (m_eletype != elementType) {
        m_eletype = elementType;
        emit eletypeChanged(m_eletype);
    }
}

bool DataItem::enabled() const {
    return m_enabled;
}

void DataItem::setEnabled(bool enabled) {
    if (m_enabled != enabled) {
        m_enabled = enabled;
        emit enabledChanged(m_enabled);
    }
}

