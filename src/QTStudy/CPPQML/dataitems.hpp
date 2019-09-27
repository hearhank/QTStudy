#ifndef DATAITEMS_HPP
#define DATAITEMS_HPP

#include <QDebug>
#include <QObject>
#include <QList>
#include <QQmlListProperty>
#include "dataitem.hpp"
#include "convertservers.hpp"
#include "Singleton.hpp"
#include "modbusconvert.hpp"

class DataItems : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<DataItem> datas READ datas NOTIFY datasChanged)
public:
    explicit DataItems(QObject *parent = nullptr);
    ~DataItems();


    QQmlListProperty<DataItem> datas();
    void add(DataItem*);
    int count();
    DataItem *at(int) const;
    void clear();

signals:
    void datasChanged(int count);

public slots:
    void upgradeValue(int index, const QVariant &val);
    void update();
private:
    QList<DataItem *> items() const;
    static void add(QQmlListProperty<DataItem>* list, DataItem* at);
    static int count(QQmlListProperty<DataItem>* list);
    static DataItem* at(QQmlListProperty<DataItem>* list, int index);
    static void clear(QQmlListProperty<DataItem>* list);
    QList<DataItem*> m_items;
};

#endif // DATAITEMS_HPP
