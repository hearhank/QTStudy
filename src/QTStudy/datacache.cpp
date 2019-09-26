#include "datacache.hpp"
#include <QDebug>


DataCache::DataCache(QObject *parent) : QObject(parent) {
    m_store = new SqliteDBStore("kvcnf");
    m_store->Load();
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

void DataCache::Update(const QString &key, const QVariant val, const QString &group) {
    if (Contains(key, group)) {
        m_datas[group][key].setValue(val);
    }
}

bool DataCache::Remove(const QString &key, const QString &group) {
    if (m_datas.contains(group)) {
        return m_datas[group].remove(key) > 0;
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
    m_datas.clear();
    qDebug() << "~Destory DataCache";
}
