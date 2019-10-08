#include "pageoperationtimer.hpp"

PageOperationTimer::PageOperationTimer(QObject* parent)
    : QObject(parent), m_items(), m_interval(500) {
}

PageOperationTimer::~PageOperationTimer() {
    stop();
    qDebug() << "~Page Operation Timer";
}

void PageOperationTimer::setDataItems(DataNodes* items) {
    if (!m_items.contains(items->name()))
        m_items.insert(items->name(), items);
}

void PageOperationTimer::start() {
    foreach (auto item, m_items.values()) {
        item->Load();
    }
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
    foreach (auto group, m_items.values()) {
        foreach (auto item, group->nodeList()) {
            item->setValue(ReadDataItem(item));
        }
    }
}


QVariant PageOperationTimer::ReadDataItem(const DataNode *item) {
    //TODO
    //    int r = item->value().toInt();
    //    r += 1;
    //    return r;
    return item->value();
}

void PageOperationTimer::WriteDataItem(const DataNode *item,
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


