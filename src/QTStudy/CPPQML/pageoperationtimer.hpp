#ifndef PAGEOPERATIONTIMER_HPP
#define PAGEOPERATIONTIMER_HPP

#include "dataitem.hpp"
#include "dataitems.hpp"
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
  Q_INVOKABLE void setDataItems(DataItems *items);
  Q_INVOKABLE void start();
  void stop();
  int interval() const;
  void setInterval(int interval);
  void runSync();

signals:

public slots:
  void doRead();

private:
  QVariant ReadDataItem(const DataItem *item);
  void WriteDataItem(const DataItem *item, const QVariant &val);

  QTimer m_timer;
  QHash<QString, DataItems *> m_items;
  int m_interval;
  bool m_flag = false;
  QMutex m_mutex;
};

#endif // PAGEOPERATIONTIMER_HPP
