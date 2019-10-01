#ifndef SQLITEHELPER_H
#define SQLITEHELPER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QObject>
#include <QtDebug>
#include <QMutexLocker>
#include <QFileInfo>


class SQLiteHelper : public QObject {
Q_OBJECT
public:
explicit SQLiteHelper(const QString& dbname, const QString& pwd = "",
                      QObject* parent = nullptr);
~SQLiteHelper();

void Execute(const QString& sql, const QVariantList params=QVariantList());
QVariant Scalar(const QString& sql, const QVariantList params=QVariantList());
QSqlQuery Query(const QString& sql, const QVariantList params=QVariantList());
bool Exist(const QString& name);
signals:
void onFailed(const QString& msg);
public slots:
private:
bool Open();
QString m_dbName;
QString m_password;
QMutex m_mutex;
QSqlDatabase m_db;
};

#endif // SQLITEHELPER_H
