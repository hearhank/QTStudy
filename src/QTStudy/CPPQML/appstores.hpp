#ifndef APPSTORES_HPP
#define APPSTORES_HPP

#include <QObject>
#include <QMutexLocker>
#include "datanode.hpp"

class AppStores : public QObject
{
    Q_OBJECT
public:
    explicit AppStores(QObject *parent = nullptr);
    ~AppStores();
    void addDataItem(DataNode *item);
    DataNode *getDataItem(const QString &name) const;
    QList<DataNode *> getDataItems() const;
    void Load();
signals:

public slots:
private:
    QHash<QString, DataNode *> m_items;
    QMutex m_mutex;

};

#endif // APPSTORES_HPP
