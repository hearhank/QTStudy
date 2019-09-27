#include "dataitems.hpp"

DataItems::DataItems(QObject *parent) : QObject(parent)
{

}
DataItems::~DataItems(){
    //    qDeleteAll(m_items);
}

//DataItem *DataItems::Current() const {
//    if(m_items.count() > 0)
//        return m_items.at(0);
//    return nullptr;
//}

QQmlListProperty<DataItem> DataItems::datas(){
    return QQmlListProperty<DataItem>(this, this,
                                      &DataItems::add,
                                      &DataItems::count,
                                      &DataItems::at,
                                      &DataItems::clear);
}

void DataItems::add(DataItem * item){
    //item->setIndex(m_items.count());
    m_items.append(item);
    emit datasChanged(m_items.count());
}

int DataItems::count()  {
    return m_items.size();
}

DataItem * DataItems::at(int index) const {
    if(index >= 0 && m_items.count() > index) {
        return m_items.at(index);
    }else{
        return nullptr;
    }
}

void DataItems::clear(){
    m_items.clear();
    emit datasChanged(0);
}

void DataItems::add(QQmlListProperty<DataItem>* list, DataItem *item)
{
    reinterpret_cast<DataItems*>(list->data)->add(item);
}

void DataItems::clear(QQmlListProperty<DataItem> *list)
{
    reinterpret_cast<DataItems*>(list->data)->clear();
}

QList<DataItem *> DataItems::items() const
{
    return m_items;
}

DataItem* DataItems::at(QQmlListProperty<DataItem> *list, int index)
{
    return reinterpret_cast<DataItems*>(list->data)->at(index);
}

int DataItems::count(QQmlListProperty<DataItem> *list)
{
    return reinterpret_cast<DataItems*>(list->data)->count();
}

void DataItems::upgradeValue(int index, const QVariant &val)
{
    if (!this->at(index)->isLoad()) {
        this->at(index)->Load(this->items());
    }
    this->at(index)->setValue(val);
}

void DataItems::update() {
    qDebug() << "update...";
    QListIterator<DataItem *> i(m_items);
    while (i.hasNext()) {
        // Update
        const DataItem *item = i.next();
        if (!item->isLoad())
            const_cast<DataItem *>(item)->Load(this->items());

        if (item->convertType() != ConverterType::DataConverter::None) {
            auto service = Singleton<ConvertServers>::getInstance().GetService(
                item->convertType());
            if (service != nullptr) {
                auto val = static_cast<NameConvert*>(service)->Convert(item->refItems());
                const_cast<DataItem *>(item)->setValue(val);
            }
        }else{
            //Normal Update
            auto service = Singleton<ConvertServers>::getInstance().GetService(
                item->convertType());
            if (service != nullptr) {
                auto val = static_cast<ModbusConvert>(service).Convert(item->desc());
                const_cast<DataItem *>(item)->setValue(val);
            }
        }
    }
}
