#include "datacache.hpp"
#include <QDebug>


DataCache::DataCache(QObject *parent) : QObject(parent) {


}

void DataCache::Load(const QString &dgroup) {
    m_group = dgroup;
    m_store = new SqliteDBStore("kvcnf");
    QList<CacheItem> datas = m_store->Load(m_group);
    if (m_datas.contains(m_group)) {
        m_datas[m_group].clear();
    } else {
        m_datas.insert(m_group, QHash<QString, CacheItem>());
    }
    foreach (CacheItem item, datas) {
        m_datas[m_group].insert(item.Key(), item);
    }
}

void DataCache::Set(const QString &key, const QVariant val,
                    const QString &group) {
    bool addFlag = true;
    if (Contains(key, group)) {
        Update(key, val, group);
        addFlag = false;
    } else {
        AddCache(key, CacheItem(key, val, group));
    }
    if (m_store != nullptr) {
        if (!addFlag) {
            m_store->Update(CacheItem(key, val, group));
        } else {
            m_store->Add(CacheItem(key, val, group));
        }
    }
}


CacheItem* DataCache::Get(const QString &key, QVariant dval, const QString &group)
{
    CacheItem *item = nullptr;
    if (Contains(key, group)) {
        item = &m_datas[group][key];
    }else{
        item = new CacheItem(key, dval, group);
    }
    return item;
}

QList<CacheItem> DataCache::GetByGroup(const QString &group) {
    QList<CacheItem> items;
    if (m_datas.contains(group)) {

    }else{

    }
    return items;
}

void DataCache::Update(const QString &key, const QVariant val, const QString &group) {
    if (Contains(key, group)) {
        if(m_store != nullptr)
            m_store->Update(CacheItem(key, val, group));
        m_datas[group][key].setValue(val);
    }
}

bool DataCache::Remove(const QString &key, const QString &group) {
    if (m_datas.contains(group)) {
        if(m_store != nullptr)
            m_store->Delete(group, key);
        return m_datas[group].remove(key) > 0;
    }
    return false;
}

bool DataCache::RemoveGroup(const QString &group) {
    if (m_datas.contains(group)) {
        if(m_store != nullptr)
            m_store->Delete(group);
        return m_datas.remove(group) > 0;
    }
    return false;
}

void DataCache::Print() {
    QHashIterator<QString, QHash<QString, CacheItem> > i(m_datas);
    while (i.hasNext()) {
        i.next();
        qDebug() << i.key();
        QHashIterator<QString, CacheItem> j(i.value());
        while (j.hasNext()) {
            j.next();
            qDebug() << j.key() << "=" << j.value().Value().toString();
        }
    }
}

void DataCache::AddCache(const QString &key, const CacheItem &item) {
    if (!m_datas.contains(item.Group())) {
        m_datas.insert(item.Group(), QHash<QString, CacheItem>());
    }
    m_datas[item.Group()].insert(key, item);
}


bool DataCache::Contains(const QString &key, const QString &group = "") {
    if (m_datas.contains(group)) {
        return m_datas[group].contains(key);
    }
    return false;
}

DataCache::~DataCache() {
    if (m_store != nullptr) {
        m_store->Close();
        delete m_store;
    }
    m_datas.clear();
    qDebug() << "~Destory DataCache";
}
