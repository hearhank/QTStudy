#include "sqlitedbstore.hpp"


SqliteDBStore::SqliteDBStore(const QString &dbname, const QString &pwd) {
    m_dbname = dbname;
    m_password = pwd;

    Init();
}

QHash<QString, QHash<QString, QVariant> >
SqliteDBStore::Load(const QString &group) {
    QString sql = "SELECT * from [key_values]";
    QSqlQuery query;
    if (group != "") {
        sql += " where [group]=? ";
        query = Query(sql, QList<QVariant>{group});
    } else {
        sql += " order by [group]";
        query = Query(sql);
    }
    QHash<QString, QHash<QString, QVariant> > datas;
    if (group != "") {
        QHash<QString, QVariant> results;
        while (query.next()) {
            results.insert(query.value(1).toString(), query.value(2));
        }
        datas.insert(group, results);
    }else{
        QHash<QString, QVariant> results;
        while (query.next()) {
            results.insert(query.value(1).toString(), query.value(2));
        }
        if(results.count() > 0) {
            datas.insert(group, results);
        }
    }
    return datas;
}

void SqliteDBStore::Add(const QString &group, const QString &key, const QVariant &val)
{
    QList<QVariant> params;
    params.append(group);
    params.append(key);
    params.append(val);
    Exec("INSERT into [key_values]([group],[key],[Value]) values(?,?,?)", params);
}

void SqliteDBStore::Update(const QString &group, const QString &key, const QVariant &val)
{
    QList<QVariant> params;
    params.append(val);
    params.append(group);
    params.append(key);
    Exec("UPDATE [key_values] SET [value] = ? WHERE [group] = ? and [key] = ?", params);
}

void SqliteDBStore::Delete(const QString &group, const QString &key)
{
    QList<QVariant> params;
    params.append(group );
    params.append(key);
    Exec("DELETE FROM [key_values] WHERE [group] = ? and [key] = ?", params);
}

void SqliteDBStore::Delete(const QString &group)
{
    QList<QVariant> params;
    params.append(group);
    Exec("DELETE [key_values] WHERE [group] = ? ", params);
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
            qDebug() << sql;
            qDebug() << params;
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

QList<QString> SqliteDBStore::getGroups() {
    QString sql = "SELECT distinct [group] FROM [key_values]";
    QSqlQuery query = Query(sql);
    while (query.next()) {

    }

}


