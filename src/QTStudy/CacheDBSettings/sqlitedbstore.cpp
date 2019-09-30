#include "sqlitedbstore.hpp"

SqliteDBStore::SqliteDBStore(const QString& dbname, const QString& pwd,
                             QObject* parent)
  : QObject(parent), m_helper(dbname, pwd) {
  Init(dbname);
}
void SqliteDBStore::Init(const QString &name) {
  QFileInfo f(QString("./%1").arg(name));
  if (f.exists() == false) {
    m_helper.Execute(createTable);
    m_helper.Execute(createIndex);
  } else {
    // Create Table
    if (!m_helper.Exist("key_values")) {
      m_helper.Execute(createTable);
    }
    // Create Index with table key_values;
    if (!m_helper.Exist("group_key_unique")) {
      m_helper.Execute(createIndex);
    }
  }
}

QHash<QString, QHash<QString, QVariant> >
SqliteDBStore::Load(const QString &group) {
  QHash<QString, QHash<QString, QVariant> > datas;
  if (group != "") {
    datas.insert(group, loadGroup(group));
  } else {
    QList<QString> groups = getGroups();
    foreach (QString gName, groups) {
      datas.insert(gName, loadGroup(gName));
    }
  }
  return datas;
}

void SqliteDBStore::Add(const QString &group, const QString &key, const QVariant &val)
{
  m_helper.Execute(
    "INSERT into [key_values]([group],[key],[Value]) values(?,?,?)",
    QVariantList{group,key,val});
}

void SqliteDBStore::Update(const QString &group, const QString &key, const QVariant &val)
{
  m_helper.Execute("UPDATE [key_values] SET [value] = ? WHERE [group] = ? and [key] = ?",
                   QVariantList{val,group,key});
}

void SqliteDBStore::Delete(const QString &group, const QString &key)
{
  m_helper.Execute("DELETE FROM [key_values] WHERE [group] = ? and [key] = ?",
                   QVariantList{group,key});
}

void SqliteDBStore::Delete(const QString &group)
{
  m_helper.Execute("DELETE [key_values] WHERE [group] = ? ", QVariantList{group});
}

QHash<QString, QVariant> SqliteDBStore::loadGroup(const QString& group) {
  QString sql = "SELECT * from [key_values] where [group]=?";
  QHash<QString, QVariant> datas;

  QSqlQuery query = m_helper.Query(sql, QVariantList{group});
  while (query.next()) {
    datas.insert(query.value(1).toString(), query.value(2));
  }
  return datas;
}

QList<QString> SqliteDBStore::getGroups() {
  QList<QString> groups;
  QString sql = "SELECT distinct [group] FROM [key_values]";
  QSqlQuery query = m_helper.Query(sql);
  while (query.next()) {
    groups.append(query.value(0).toString());
  }
  return groups;
}


