#ifndef CACHEITEM_HPP
#define CACHEITEM_HPP

#include <QObject>
#include <QVariant>
#include <QDateTime>

class CacheItem
{
public:
    explicit CacheItem(){
    }
    explicit CacheItem(const QString &key, const QVariant &Value, const QString &Group = "SYSTEM");

    QVariant Value() const;
    void setValue(const QVariant &Value);

    QString Group() const;
    void setGroup(const QString &Group);

    QString Notes() const;
    void setNotes(const QString &Notes);

    QString Key() const;
    void setKey(const QString &Key);

private:
    QVariant m_Value;
    QString m_Group;
    QString m_Key;
    QString m_Notes;
};

#endif // CACHEITEM_HPP
