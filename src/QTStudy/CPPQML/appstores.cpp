#include "appstores.hpp"

AppStores::AppStores(QObject *parent) : QObject(parent), m_items()
{

}

AppStores::~AppStores() {
    qDeleteAll(m_items.values());
    qDebug() << "~AppStores()";
}

void AppStores::addDataItem(DataItem *item) {
    QMutexLocker lock(&m_mutex);
    if (!m_items.contains(item->name())) {
        item->setParent(this);
        m_items.insert(item->name(), item);
    }
}

DataItem *AppStores::getDataItem(const QString &name) const {
    if (m_items.contains(name))
        return m_items[name];
    return nullptr;
}

QList<DataItem*> AppStores::getDataItems() const {
    return m_items.values();
}

void AppStores::Load() {
    auto items = m_items.values();
    foreach (auto item, items) {
        if (!item->isLoad()) {
            item->Load(items);
        }
    }
}
