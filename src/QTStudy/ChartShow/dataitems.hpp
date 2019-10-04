#ifndef DATAITEMS_HPP
#define DATAITEMS_HPP

//#include "Singleton.hpp"
//#include "appstores.hpp"
//#include "convertservers.hpp"
#include "dataitem.hpp"
//#include "modbusconvert.hpp"
#include <QDebug>
#include <QList>
#include <QObject>
#include <QQmlListProperty>
#include <QString>

class DataItems : public QObject {
  Q_OBJECT
  Q_PROPERTY(QQmlListProperty<DataItem> datas READ datas NOTIFY datasChanged)
  Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
public:
  explicit DataItems(QObject *parent = nullptr);
  ~DataItems();

  QQmlListProperty<DataItem> datas();
  void add(DataItem *);
  int count();
  DataItem *at(int) const;
  void clear();
  QList<DataItem *> items();

  void Load();

  Q_INVOKABLE DataItem *getStore(const QString &name);
  QString name() const;
  void setName(const QString &name);

signals:
  void datasChanged(int count);
  void nameChanged(const QString &name);
public slots:
  //    void upgradeValue(int index, const QVariant &val);
  //    void update();

private:
  static void add(QQmlListProperty<DataItem> *list, DataItem *at);
  static int count(QQmlListProperty<DataItem> *list);
  static DataItem *at(QQmlListProperty<DataItem> *list, int index);
  static void clear(QQmlListProperty<DataItem> *list);
  QList<DataItem *> m_items;
  QString m_name;
};

#endif // DATAITEMS_HPP
