#include "dataitem.hpp"

DataItem::DataItem(QObject *parent) : QObject(parent),
    m_value(QVariant()),
    m_refNames(),
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
    qDebug() << "~DataItem()";
}

void DataItem::Load(const QList<DataItem*> datas) {
    if (m_load)
        return;

    if (m_refNames.count() > 0) {
        QListIterator<DataItem*> i(datas);
        while (i.hasNext()) {
            const DataItem* item = i.next();
            if (m_refNames.contains(item->name())) {
                connect(item, &DataItem::valueChanged, this, &DataItem::getValueChanged);
                m_refItems.append(const_cast<DataItem*>(item));
            }
        }
        qDebug() << name() << " Load";
    }
    m_load = true;
}
void DataItem::getValueChanged(const QVariant &newVal) {
    QList<QVariant> list;
    QListIterator<DataItem *> i(this->m_refItems);
    while (i.hasNext()) {
        list.append(i.next()->value());
    }
    emit valueChanged(this->value(), list);
}

bool DataItem::getHidden() const
{
    return m_hidden;
}

void DataItem::setHidden(bool hidden)
{
    m_hidden = hidden;
}

QVariant DataItem::value() const {
    return m_value;
}

void DataItem::setValue(const QVariant &value) {

    if (m_value != value) {
        m_value = value;
        if(m_refItems.count() == 0)
            emit valueChanged(m_value, QList<QVariant>());
        else
            getValueChanged(m_value);
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

int DataItem::eletype() const {
    return m_eletype;
}


void DataItem::setEletype(const int &elementType) {
    if (m_eletype != elementType) {
        m_eletype = (DataItem::EleType)elementType;
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

//bool DataItem::getStore() const
//{
//    return m_store;
//}

//void DataItem::setStore(bool store)
//{
//    m_store = store;
//}


