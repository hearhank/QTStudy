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
    ~DataCache();

    Q_INVOKABLE void load(const QString &group);

    Q_INVOKABLE void set(QString key, QVariant val, QString group);

    Q_INVOKABLE QVariant get(const QString &key, QVariant dval = QVariant(), const QString &group = "");

    QHash<QString, QVariant> getByGroup(const QString &group);

    Q_INVOKABLE bool remove(const QString &key, const QString &group);

    Q_INVOKABLE bool removeGroup(const QString &group);

    Q_INVOKABLE void print();
signals:

public slots:

private:
    void AddCache(const QString &key, const CacheItem &item);
    void Update(const QString &key, const QVariant val, const QString &group = "");
    bool Contains(const QString &key, const QString &group);
    QHash<QString, QHash<QString, CacheItem> > m_datas;

    SqliteDBStore *m_store = nullptr;
    bool m_load = false;

};

#endif // DATACACHE_HPP
