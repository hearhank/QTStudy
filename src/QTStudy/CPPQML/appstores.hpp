#ifndef APPSTORES_HPP
#define APPSTORES_HPP

#include <QObject>
#include "dataitem.hpp"

class AppStores : public QObject
{
    Q_OBJECT
public:
    explicit AppStores(QObject *parent = nullptr);
    void addDataItem(const DataItem *item);
    DataItem *getDataItem(const QString &name) const;
    QList<DataItem *> getDataItems() const;
signals:

public slots:
private:
    QHash<QString, DataItem *> m_stores;
};

#endif // APPSTORES_HPP
