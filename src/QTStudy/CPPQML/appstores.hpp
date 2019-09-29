#ifndef APPSTORES_HPP
#define APPSTORES_HPP

#include <QObject>
#include <QMutexLocker>
#include "dataitem.hpp"

class AppStores : public QObject
{
    Q_OBJECT
public:
    explicit AppStores(QObject *parent = nullptr);
    ~AppStores();
    void addDataItem(DataItem *item);
    DataItem *getDataItem(const QString &name) const;
    QList<DataItem *> getDataItems() const;
    void Load();
signals:

public slots:
private:
    QHash<QString, DataItem *> m_items;
    QMutex m_mutex;

};

#endif // APPSTORES_HPP
