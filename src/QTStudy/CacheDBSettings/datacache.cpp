#include "datacache.hpp"
#include <QDebug>


DataCache::DataCache(QObject *parent) : QObject(parent) {


}

void DataCache::load(const QString &group) {
    m_load = false;

    m_store = new SqliteDBStore("kvcnf");
    QHash<QString, QVariant> datas = m_store->Load(group);
    if (m_datas.contains(group)) {
        m_datas[group].clear();
    } else {
        m_datas.insert(group, QHash<QString, CacheItem>());
    }
    QHashIterator<QString, QVariant> i(datas);
    while (i.hasNext()) {
        auto item = i.next();
        m_datas[group].insert(item.key(),
                              CacheItem(item.key(), item.value(), group));
    }
    m_load = true;
}

void DataCache::set(QString key, QVariant val, QString group) {
    bool addFlag = true;
    if (Contains(key, group)) {
        Update(key, val, group);
        addFlag = false;
    } else {
        AddCache(key, CacheItem(key, val, group));
    }
    if (m_store != nullptr) {
//        qDebug() << group << "[" << key << "=" << val << "]";
        if (!addFlag) {
            m_store->Update(group, key, val);
        } else {
            m_store->Add(group, key, val);
        }
    }
}


QVariant DataCache::get(const QString &key, QVariant dval, const QString &group)
{
    if (Contains(key, group)) {
        return m_datas[group][key].value();
    }else{
        return dval;
    }
}

QHash<QString, QVariant> DataCache::getByGroup(const QString &group) {
    QHash<QString, QVariant> datas;
    if (m_datas.contains(group)) {
        QList<CacheItem> gValues = m_datas[group].values();
        QListIterator<CacheItem> i(gValues);
        while (i.hasNext()) {
            CacheItem *item = const_cast<CacheItem *>(&i.next());
            datas.insert(item->key(), item->value());
        }
    }
    return datas;
}

void DataCache::Update(const QString &key, const QVariant val, const QString &group) {
    if (Contains(key, group)) {
        if(m_store != nullptr)
            m_store->Update(group, key, val);
        m_datas[group][key].setValue(val);
    }
}

bool DataCache::remove(const QString &key, const QString &group) {
    if (m_datas.contains(group)) {
        if(m_store != nullptr)
            m_store->Delete(group, key);
        return m_datas[group].remove(key) > 0;
    }
    return false;
}

bool DataCache::removeGroup(const QString &group) {
    if (m_datas.contains(group)) {
        if(m_store != nullptr)
            m_store->Delete(group);
        return m_datas.remove(group) > 0;
    }
    return false;
}

void DataCache::print() {
    QHashIterator<QString, QHash<QString, CacheItem> > i(m_datas);
    qDebug() << "=========================================================";
    while (i.hasNext()) {
        i.next();
        qDebug() << "# " << i.key();
        QHashIterator<QString, CacheItem> j(i.value());
        while (j.hasNext()) {
            j.next();
            qDebug() << j.key() << "=" << j.value().value().toString();
        }
    }
}

void DataCache::AddCache(const QString &key, const CacheItem &item) {
    if (!m_datas.contains(item.group())) {
        m_datas.insert(item.group(), QHash<QString, CacheItem>());
    }
    m_datas[item.group()].insert(key, item);
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
        m_store = nullptr;
    }
    m_datas.clear();
    qDebug() << "~Destory DataCache";
}
