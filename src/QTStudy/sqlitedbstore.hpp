#ifndef SQLITEDBSTORE_HPP
#define SQLITEDBSTORE_HPP

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QtDebug>

#include "cacheitem.hpp"

class SqliteDBStore
{
public:
    SqliteDBStore(const QString &dbname, const QString &pwd = "protonmdis");

    QList<CacheItem> Load();


    void Add(const CacheItem &item);
    void Update(const CacheItem &item);


    bool Open();
    void Close();

    bool Exec(const QString &sql);
    bool Exec(const QString &sql, const QList<QVariant> &params);
    QSqlQuery Query(const QString &sql);
    QSqlQuery Query(const QString &sql, const QList<QVariant> &params);

    bool Exists(const QString &sql);
    bool Exists(const QString &sql, const QList<QVariant> &params);

    ~SqliteDBStore() {
        if (m_db.isOpen())
            m_db.close();
    }
private:
    void Init();
    QString m_dbname;
    QString m_password;
    QString m_group;
    QSqlDatabase m_db;

    const QString checkTable = "SELECT COUNT(*) as RC FROM sqlite_master where "
                               "type='table' and name='KeyValues'";
    const QString createTable =
        "CREATE TABLE KeyValues ([Group] varchar(50), [Key] varchar(50), "
        "[Value] nvarchar(254), [Notes] nvarchar(100));";
    const QString createIndex = "CREATE UNIQUE INDEX [Group_Key_Unique]ON KeyValues ([Group], [Key]);";
};

#endif // SQLITEDBSTORE_HPP
