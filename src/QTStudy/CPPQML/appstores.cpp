#include "appstores.hpp"

AppStores::AppStores(QObject *parent) : QObject(parent)
{

}

void AppStores::addDataItem(const DataItem *item) {
    if (!m_stores.contains(item->name())) {
        m_stores.insert(item->name(), const_cast<DataItem *>(item));
    }
}

DataItem *AppStores::getDataItem(const QString &name) const {
    if (m_stores.contains(name))
        return m_stores[name];
    return nullptr;
}

QList<DataItem *> AppStores::getDataItems() const {
    return m_stores.values();
}
