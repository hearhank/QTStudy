#ifndef PAGEOPERATIONTIMER_HPP
#define PAGEOPERATIONTIMER_HPP

#include "datanode.hpp"
#include "datanodes.hpp"
#include <QDateTime>
#include <QMutexLocker>
#include <QObject>
#include <QTimer>
#include <QtConcurrent/QtConcurrent>

class PageOperationTimer : public QObject {
    Q_OBJECT
    Q_PROPERTY(int interval READ interval WRITE setInterval)
public:
    explicit PageOperationTimer(QObject *parent = nullptr);
    ~PageOperationTimer();
    Q_INVOKABLE void setDataItems(DataNodes *items);
    Q_INVOKABLE void start();
    void stop();
    int interval() const;
    void setInterval(int interval);
    void runSync();

signals:

public slots:
  void doReadAll();

private:
  QList<DataNode*> extendNodes(const DataNodes* nodes);
  QList<DataNode*> extend(const DataNode* node);
  void read(const QList<DataNode*> nodes);
  QVariant ReadDataByNode(const DataNode* item);
  void WriteDataItem(const DataNode* item, const QVariant& val);

  QTimer m_timer;
  QHash<QString, DataNodes*> m_items;
  QHash<QString, DataNode*> m_allNodes;
  int m_interval;
  bool m_flag = false;
  QMutex m_mutex;
};

#endif // PAGEOPERATIONTIMER_HPP
