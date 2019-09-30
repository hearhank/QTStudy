#ifndef CACHEITEM_HPP
#define CACHEITEM_HPP

#include <QObject>
#include <QDebug>
#include <QVariant>
#include <QDateTime>

class CacheItem
{
public:
    explicit CacheItem();
    ~CacheItem();
    explicit CacheItem(const QString &key, const QVariant &Value, const QString &Group = "SYSTEM");

    QVariant value() const;
    void setValue(const QVariant &value);

    QString group() const;
    void setGroup(const QString &group);

    QString key() const;
    void setKey(const QString &key);

    QString notes() const;
    void setNotes(const QString &notes);

private:
    QVariant m_value;
    QString m_group;
    QString m_key;
    QString m_notes;
};

#endif // CACHEITEM_HPP
