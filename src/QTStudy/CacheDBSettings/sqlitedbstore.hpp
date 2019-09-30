#ifndef SQLITEDBSTORE_HPP
#define SQLITEDBSTORE_HPP

#include <QSqlQuery>
#include <QSqlError>
#include <QtDebug>
#include <QObject>

#include "sqlitehelper.h"

class SqliteDBStore : public QObject
{
Q_OBJECT
public:
SqliteDBStore(const QString &dbname, const QString &pwd = "protonmdis",QObject *parent=nullptr);

QHash<QString, QHash<QString, QVariant> > Load(const QString &group = "");


void Add(const QString &group, const QString &key, const QVariant &val);
void Update(const QString &group, const QString &key, const QVariant &val);
void Delete(const QString &group, const QString &key);
void Delete(const QString &group);


~SqliteDBStore() {
  m_helper.deleteLater();
}

private:
void Init(const QString &name);
QHash<QString, QVariant> loadGroup(const QString& group);
QList<QString> getGroups();
SQLiteHelper m_helper;

const QString createTable =
  "CREATE TABLE key_values ([group] varchar(50), [key] varchar(50),[value] text);";
const QString createIndex = "CREATE UNIQUE INDEX [group_key_unique]ON key_values ([group], [key]);";
};

#endif // SQLITEDBSTORE_HPP
