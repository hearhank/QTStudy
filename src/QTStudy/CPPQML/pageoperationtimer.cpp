#include "pageoperationtimer.hpp"

PageOperationTimer::PageOperationTimer(QObject *parent) : QObject(parent),
    m_items(nullptr),
    m_interval(500)
{
}

PageOperationTimer::~PageOperationTimer() {
    stop();
    qDebug() << "~Page Operation Timer";
}

void PageOperationTimer::start(DataItems *items) {
    qDebug() << items->count();
    m_items = items;
    m_items->Load();
    connect(&m_timer, &QTimer::timeout, this, &PageOperationTimer::runSync);
    m_timer.start(m_interval);
}


void PageOperationTimer::stop() {
    m_timer.stop();
    disconnect(&m_timer, &QTimer::timeout, this, &PageOperationTimer::runSync);
}

void PageOperationTimer::runSync() {

    QFuture<void> future = QtConcurrent::run(this, &PageOperationTimer::doRead);
    future.waitForFinished();
}

void PageOperationTimer::doRead() {
    QMutexLocker lock(&m_mutex);
    foreach (auto item, m_items->items()) {
        item->setValue(ReadDataItem(item));
    }
}


QVariant PageOperationTimer::ReadDataItem(const DataItem *item) {
    //TODO
    int r = item->value().toInt();
    r += 1;
    return r;
}

void PageOperationTimer::WriteDataItem(const DataItem *item,
                                       const QVariant &val) {
    qDebug() << "Write on " << item->name() << " with value " << val;
}

int PageOperationTimer::interval() const
{
    return m_interval;
}

void PageOperationTimer::setInterval(int interval)
{
    m_interval = interval;
}


