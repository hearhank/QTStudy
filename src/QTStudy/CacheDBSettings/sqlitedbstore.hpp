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

    QHash<QString, QHash<QString, QVariant> > Load(const QString &group = "");


    void Add(const QString &group, const QString &key, const QVariant &val);
    void Update(const QString &group, const QString &key, const QVariant &val);
    void Delete(const QString &group, const QString &key);
    void Delete(const QString &group);


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
    QList<QString> getGroups();
    QString m_dbname;
    QString m_password;
    QSqlDatabase m_db;

    const QString checkTable = "SELECT COUNT(*) as RC FROM sqlite_master where "
                               "type='table' and name='key_values'";
    const QString createTable =
        "CREATE TABLE key_values ([group] varchar(50), [key] varchar(50), "
        "[value] text, [notes] nvarchar(100));";
    const QString createIndex = "CREATE UNIQUE INDEX [group_key_unique]ON key_values ([group], [key]);";
};

#endif // SQLITEDBSTORE_HPP
