#include "sqlitedbstore.hpp"


SqliteDBStore::SqliteDBStore(const QString &dbname, const QString &pwd) {
    m_dbname = dbname;
    m_password = pwd;

    Init();
}

QList<CacheItem> SqliteDBStore::Load() {
    QString sql = "SELECT * from [KeyValues]";
    QSqlQuery query = Query(sql);
    QList<CacheItem> results;
    while (query.next()) {
        CacheItem item;
        item.setGroup(query.value(0).toString());
        item.setKey(query.value(1).toString());
        item.setValue(query.value(2));
//        item.setNotes(query.value(3).toString());
        //(query.value(1).toString(), query.value(2), query.value(0).toString(),query.value(3).toString());
        results.append(item);
    }
    qDebug() << QT_MESSAGELOG_FILE << QT_MESSAGELOG_FUNC << "Load datas count:" << results.count();
    return results;
}

void SqliteDBStore::Add(const CacheItem &item)
{
    QList<QVariant> params;
    params.append(item.Group());
    params.append(item.Key());
    params.append(item.Value());
    Exec("INSERT into KeyValues([Group],[Key],[Value]) values(?,?,?)", params);
}

void SqliteDBStore::Update(const CacheItem &item)
{
    QList<QVariant> params;
    params.append(item.Value());
    params.append(item.Group());
    params.append(item.Key());
    Exec("UPDATE [KeyValues] SET [Value] = ? WHERE [Group] = ? and [Key] = ?", params);
}

bool SqliteDBStore::Open() {
    if (!m_db.isValid()) {
        m_db = QSqlDatabase::addDatabase("QSQLITE");
        m_db.setDatabaseName(m_dbname);
        m_db.setPassword(m_password);
    }
    if (!m_db.isOpen()) {
        return m_db.open();
    }
    return true;
}

void SqliteDBStore::Close()  {
    if (m_db.isValid() && m_db.isOpen())
        m_db.close();
}

bool SqliteDBStore::Exec(const QString &sql) {
    const QList<QVariant> nData;
    return Exec(sql, nData);
}

bool SqliteDBStore::Exec(const QString &sql, const QList<QVariant> &params) {
    if (Open()) {
        QSqlQuery query;
        bool flag = false;
        if (params.count() > 0) {
            query.prepare(sql);
            for (int i = 0; i < params.count(); i++) {
                query.bindValue(i, params[i]);
            }
            flag = query.exec();
        } else {
            flag = query.exec(sql);
        }
        if (!flag) {
            qDebug() << query.lastError().text();
        } else {
            m_db.commit();
        }
        return flag;
    }
    return false;
}

QSqlQuery SqliteDBStore::Query(const QString &sql) {
    const QList<QVariant> nData;
    return Query(sql, nData);
}

QSqlQuery SqliteDBStore::Query(const QString &sql, const QList<QVariant> &params)
{
    if (Open()) {
        QSqlQuery query;
        bool flag = false;
        if (params.count() > 0) {
            query.prepare(sql);
            for (int i = 0; i < params.count(); i++) {
                query.bindValue(i, params[i]);
            }
            flag = query.exec();
        } else {
            flag = query.exec(sql);
        }
        if (!flag) {
            qDebug() << query.lastError().text();
        }else
            return query;
    }
    return QSqlQuery();
}

bool SqliteDBStore::Exists(const QString &sql) {
    const QList<QVariant> nData;
    return Exists(sql, nData);
}

bool SqliteDBStore::Exists(const QString &sql,
                           const QList<QVariant> &params) {
    if (Open()) {
        QSqlQuery query;
        bool flag = false;
        if (params.count() > 0) {
            query.prepare(sql);
            for (int i = 0; i < params.count(); i++) {
                query.bindValue(i, params[i]);
            }
            flag = query.exec();
        } else {
            flag = query.exec(sql);
        }
        if (flag) {
            if(query.next())
            {
                return !query.isNull(0) && query.value(0).toInt() > 0;
            }
        } else {
            qDebug() << query.lastError().text();
        }
    }
    return false;
}

void SqliteDBStore::Init()
{
    m_db = QSqlDatabase::database(m_dbname);
    if (!m_db.isValid()) {

        if (!Exists(checkTable)) {
            Exec(createTable);
            Exec(createIndex);
        }
        qDebug() << m_db.databaseName();
    }
}
