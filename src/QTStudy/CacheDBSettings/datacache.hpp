#ifndef DATACACHE_HPP
#define DATACACHE_HPP

#include <QObject>
#include <QVariant>
#include <QHash>
#include <QMap>

#include "sqlitedbstore.hpp"

class DataCache : public QObject
{
    Q_OBJECT
public:
    explicit DataCache(QObject *parent = nullptr);

    void Load(const QString &dgroup);

    void Set(const QString &key, const QVariant val, const QString &group = "");

    CacheItem* Get(const QString &key, QVariant dval = QVariant(), const QString &group = "");
    QList<CacheItem> GetByGroup(const QString &group);

    void Update(const QString &key, const QVariant val, const QString &group = "");

    bool Remove(const QString &key, const QString &group);

    bool RemoveGroup(const QString &group);

//    void SaveToFile(const QString &path);

//    void LoadFromFile(const QString &path);

    void Print();

signals:

public slots:

private:
    void AddCache(const QString &key, const CacheItem &item);
    bool Contains(const QString &key, const QString &group);
    QHash<QString, QHash<QString, CacheItem> > m_datas;
    ~DataCache();
    QString m_LastFile;
    QString m_group;

    SqliteDBStore *m_store = nullptr;

};

#endif // DATACACHE_HPP
