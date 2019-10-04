#include "trendingtimer.hpp"

QT_CHARTS_USE_NAMESPACE

Q_DECLARE_METATYPE(QAbstractSeries*)
Q_DECLARE_METATYPE(QAbstractAxis*)
Q_DECLARE_METATYPE(QChartView*)

TrendingTimer::TrendingTimer(QObject* parent) : QObject(parent), m_item() {
  qRegisterMetaType<QAbstractSeries*>();
  qRegisterMetaType<QAbstractAxis*>();
  qRegisterMetaType<QChartView*>();

  m_datas.append("Average Speed");
  m_datas.append("Average Length");
  qsrand(static_cast<uint>(QTime(0, 0, 0).secsTo(QTime::currentTime())));
}

TrendingTimer::~TrendingTimer() {
  if (m_item != nullptr) {
    delete m_item;
  }
  m_item = nullptr;
}

void TrendingTimer::change(QAbstractSeries* series, QAbstractAxis* axis) {
  QChart* chart = series->chart();
  auto axes = chart->axes();
  chart->removeAxis(axis);
  chart->addAxis(axis, Qt::AlignRight);
  series->attachAxis(axis);
  qDebug() << axis->titleText();
}

void TrendingTimer::setRefLines(DataItems* items) {
  QList<QString> names;
  foreach (auto item, items->items()) {
    if (!m_refes.contains(item)) {
      m_refes.append(item);
      names.append(item->name());
    }
  }
  emit load(names, 1);
}

void TrendingTimer::start(DataItems* items) {

  foreach (auto item, items->items()) {
    if (m_datas.contains(item->name())) {
      m_enables.append(item);
    }
  }
  emit load(m_datas);
  connect(&m_timer, &QTimer::timeout, this, &TrendingTimer ::runSync);
  m_timer.start(m_interval);
}

void TrendingTimer::setRange(QAbstractSeries* series) {

  QXYSeries* xyServices = static_cast<QXYSeries*>(series);
  auto axes = xyServices->attachedAxes();

  //  qDebug() << series->name() << "=======" << axes.count();
  //  foreach (auto axis, axes) { qDebug() << axis->titleText(); }
  QDateTimeAxis* timeAxis = static_cast<QDateTimeAxis*>(axes[0]);
  auto datas = xyServices->points();
  if (timeAxis != nullptr && datas.count() > 1) {
    int index = 0;
    do {
      if (m_timeLength < 1)
        break;
      auto timeSpan = QDateTime::fromMSecsSinceEpoch(
          static_cast<int64_t>(datas.last().x() - datas[index].x()));
      if (timeSpan.toMSecsSinceEpoch() > m_timeLength * 1000) {
        index++;
      } else {
        break;
      }
    } while (true);
    if (index > 0) {

      xyServices->removePoints(0, index);
      auto ftime = QDateTime::fromMSecsSinceEpoch(
          static_cast<int64_t>(xyServices->points().first().x()));
      auto ltime = QDateTime::fromMSecsSinceEpoch(
          static_cast<int64_t>(xyServices->points().last().x()));
      timeAxis->setRange(ftime, ltime);
      //      qDebug() << "Change Range " << ftime << ltime;
    }
  } else {
    if (datas.count() == 1) {
      auto ftime = QDateTime::fromMSecsSinceEpoch(
          static_cast<int64_t>(xyServices->points().first().x()));
      auto ltime = ftime.addSecs(m_timeLength);
      timeAxis->setRange(ftime, ltime);
      //      qDebug() << "Change Range " << ftime << ltime;
    }
  }

  if (datas.length() > 0) {
    if (series->name() == m_datas.first()) {
      //      qDebug() << series->name();
      axes.last()->setRange(m_main_range.y(), m_main_range.x());
    } else {
      setAxis(static_cast<QValueAxis*>(axes.last()), datas);
    }
  }
}

void TrendingTimer::setAxis(QValueAxis* yAxis, QList<QPointF> datas) {

  qreal min, max;
  min = max = datas.first().y();
  for (int i = 0; i < datas.length(); i++) {
    if (datas[i].y() < min) {
      min = datas[i].y();
    } else if (datas[i].y() > max) {
      max = datas[i].y();
    }
  }
  yAxis->setRange(min * 0.9, max * 1.1);
}

int TrendingTimer::interval() const { return m_interval; }

void TrendingTimer::setInterval(int interval) { m_interval = interval; }

void TrendingTimer::doRead() {
  QMutexLocker lock(&m_mutex);
  auto xValue = QDateTime::currentMSecsSinceEpoch();

  if (m_item == nullptr)
    m_item = new RefCalcItem();
  m_item->clear();
  foreach (auto item, m_refes) { m_item->append(item->value().toReal()); }
  m_main_range = m_item->getRangeValues();
  //  qDebug() << m_main_range;
  emit refsUpdate(m_item->getRefValues());

  QList<qreal> yValues;
  foreach (auto item, m_enables) {
    yValues.append(item->value().toReal() + (qrand() % 10));
  }
  emit dataUpdate(xValue, yValues);
}

void TrendingTimer::runSync() {
  QFuture<void> future = QtConcurrent::run(this, &TrendingTimer::doRead);
  future.waitForFinished();
}

int TrendingTimer::timeLength() const { return m_timeLength; }

void TrendingTimer::setTimeLength(int timeLength) { m_timeLength = timeLength; }
