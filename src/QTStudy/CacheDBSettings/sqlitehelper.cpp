#include "sqlitehelper.h"


SQLiteHelper::SQLiteHelper(const QString& dbname, const QString& pwd,
                           QObject* parent)
  : QObject(parent), m_dbName(dbname), m_password(pwd) {
}

SQLiteHelper::~SQLiteHelper() {
  if (m_db.isValid() && m_db.isOpen()) {
    qDebug() << "Close dbbase;";
    m_db.close();
  }
}

void SQLiteHelper::Execute(const QString& sql, const QVariantList params) {
  Query(sql, params);
}

QVariant SQLiteHelper::Scalar(const QString& sql, const QVariantList params) {
  QSqlQuery query = Query(sql, params);
  if (query.next()) {
    return query.value(0);
  }
  return QVariant();
}

QSqlQuery SQLiteHelper::Query(const QString& sql, const QVariantList params) {
  QSqlQuery query;
  if (Open()) {
    query = QSqlQuery(m_db);
    query.prepare(sql);
    //Binding Params
    if (params.count() > 0) {
      for (int i = 0; i < params.count(); i++) {
        query.bindValue(i, params[i]);
      }
    }
    //执行
    if (!query.exec()) {
      qDebug() << sql;
      qDebug() << params;
      qDebug() << query.lastError().text();
    }
  }
  return query;
}

bool SQLiteHelper::Exist(const QString& name) {
  QString sql = "SELECT count(1) count FROM [sqlite_master] where [name]=?";
  return Scalar(sql, QVariantList{name})>0;
}

bool SQLiteHelper::Open() {
  QMutexLocker lock(&m_mutex);

  if (!m_db.isValid()) {
    qDebug() << QSqlDatabase::drivers();
    m_db = QSqlDatabase::addDatabase("QSQLITE", "defautl_connection");
    m_db.setDatabaseName(m_dbName);
  }
  if (!m_db.isOpen()) {
    return m_db.open();
  }
  return true;
}
