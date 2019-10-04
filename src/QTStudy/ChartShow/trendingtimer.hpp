#ifndef TRENDINGTIMER_HPP
#define TRENDINGTIMER_HPP

#include <QAbstractAxis>
#include <QAbstractSeries>
#include <QChart>
#include <QChartView>
#include <QDateTimeAxis>
#include <QMutexLocker>
#include <QObject>
#include <QSplineSeries>
#include <QTimer>
#include <QValueAxis>
#include <QtConcurrent/QtConcurrent>

#include "dataitems.hpp"

QT_BEGIN_NAMESPACE
class QQuickView;
QT_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

class TrendingTimer : public QObject
{
  Q_OBJECT
  Q_PROPERTY(int interval READ interval WRITE setInterval)
  Q_PROPERTY(int timeLength READ timeLength WRITE setTimeLength)
public:
  explicit TrendingTimer(QObject* parent = nullptr);
  ~TrendingTimer();

  Q_INVOKABLE void change(QAbstractSeries* series, QAbstractAxis* axis);
  Q_INVOKABLE void setRefLines(DataItems* items);
  Q_INVOKABLE void start(DataItems* items);
  Q_INVOKABLE void setRange(QAbstractSeries* series);

  int interval() const;
  void setInterval(int interval);

  int timeLength() const;
  void setTimeLength(int timeLength);
  class RefCalcItem {
  public:
    RefCalcItem() {}
    void clear() { m_datas.clear(); }
    void append(qreal val) { m_datas.append(val); }
    QList<qreal> getRefValues() {
      QList<qreal> datas;
      if (m_datas.count() != 3)
        return datas;
      auto d1 = m_datas[0] - m_datas[1];
      auto d2 = m_datas[1] - m_datas[2];
      if (d1 > d2) {
        datas.append(0.75);
        datas.append(0.5);
        datas.append(0.25 + d2 * 0.25 / d1);
      } else {
        datas.append(0.5 + d1 * 0.25 / d2);
        datas.append(0.5);
        datas.append(0.25);
      }
      return datas;
    }
    QPointF getRangeValues() {
      QPointF data;
      if (m_datas.count() != 3)
        return data;
      auto d1 = m_datas[0] - m_datas[1];
      auto d2 = m_datas[1] - m_datas[2];
      if (d1 > d2) {
        data.setX(m_datas[1] + d1 * 2);
        data.setY(m_datas[1] - d1 * 2);
      } else {
        data.setX(m_datas[1] + d2 * 2);
        data.setY(m_datas[1] - d2 * 2);
      }
      return data;
    }

  private:
    QList<qreal> m_datas;
  };

signals:
  void load(const QList<QString>& datas, const int flag = 0);
  void dataUpdate(const qreal& xTime, const QList<qreal>& datas);
  void refsUpdate(const QList<qreal>& datas);

public slots:

private:
  void setAxis(QValueAxis* yAxis, QList<QPointF> datas);
  void doRead();
  void runSync();
  QList<QString> m_datas;
  QList<DataItem*> m_enables;
  QList<DataItem*> m_refes;
  int m_interval;
  QTimer m_timer;
  QMutex m_mutex;
  int m_timeLength;
  RefCalcItem* m_item;
  QPointF m_main_range;
};

#endif // TRENDINGTIMER_HPP
