#include "cacheitem.hpp"

CacheItem::CacheItem()
{

}

CacheItem::~CacheItem() {
    qDebug() << "~CacheItem()";
}

CacheItem::CacheItem(const QString &key, const QVariant &Value,
                     const QString &Group) {
    m_value = Value;
    m_group = Group;
    m_key = key;
}

QVariant CacheItem::value() const
{
    return m_value;
}

void CacheItem::setValue(const QVariant &value)
{
    m_value = value;
}

QString CacheItem::group() const
{
    return m_group;
}

void CacheItem::setGroup(const QString &group)
{
    m_group = group;
}

QString CacheItem::key() const
{
    return m_key;
}

void CacheItem::setKey(const QString &key)
{
    m_key = key;
}

QString CacheItem::notes() const
{
    return m_notes;
}

void CacheItem::setNotes(const QString &notes)
{
    m_notes = notes;
}
