#include "dataitems.hpp"

DataItems::DataItems(QObject *parent) : QObject(parent)
{

}
DataItems::~DataItems(){
    //    qDeleteAll(m_items);
    qDebug() << "~DataItems()";
}

QQmlListProperty<DataItem> DataItems::datas(){
    return QQmlListProperty<DataItem>(this, m_items);
//,
//                                      &DataItems::add,
//                                      &DataItems::count,
//                                      &DataItems::at,
//                                      &DataItems::clear);
}

void DataItems::add(DataItem *item) {
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

DataItem *DataItems::getStore(const QString &name) {
    return Singleton<AppStores>::getInstance().getDataItem(name);
}

void DataItems::add(QQmlListProperty<DataItem>* list, DataItem *item)
{
    reinterpret_cast<DataItems*>(list->data)->add(item);
}

void DataItems::clear(QQmlListProperty<DataItem> *list)
{
    reinterpret_cast<DataItems*>(list->data)->clear();
}

QList<DataItem *> DataItems::items()
{
    return m_items;
}

void DataItems::Load() {
    if (m_items.count() == 0)
        return;
    foreach (auto item, m_items) {
        if (!item->isLoad()) {
            item->Load(m_items);
        }
//        if (item->getStore()) {
//            Singleton<AppStores>::getInstance().addDataItem(item);
//            qDebug() << item->parent();
//        }
    }
}

DataItem* DataItems::at(QQmlListProperty<DataItem> *list, int index)
{
    return reinterpret_cast<DataItems*>(list->data)->at(index);
}

int DataItems::count(QQmlListProperty<DataItem> *list)
{
    return reinterpret_cast<DataItems*>(list->data)->count();
}
