#include "cacheitem.hpp"


//CacheItem CacheItem::operator=(const CacheItem &item) {

//    if (item.getFlag())
//        return CacheItem(item.getValue(), item.getExpireTime());
//    else
//        return CacheItem(item.getValue());
//}


CacheItem::CacheItem(const QString &key, const QVariant &Value,
                     const QString &Group) {
    m_Value = Value;
    m_Group = Group;
    m_Key = key;
}

QVariant CacheItem::Value() const
{
    return m_Value;
}

void CacheItem::setValue(const QVariant &Value)
{
    m_Value = Value;
}

QString CacheItem::Group() const
{
    return m_Group;
}

void CacheItem::setGroup(const QString &Group)
{
    m_Group = Group;
}

QString CacheItem::Notes() const
{
    return m_Notes;
}

void CacheItem::setNotes(const QString &Notes)
{
    m_Notes = Notes;
}

QString CacheItem::Key() const
{
    return m_Key;
}

void CacheItem::setKey(const QString &Key)
{
    m_Key = Key;
}
