#include "pageoperationtimer.hpp"

PageOperationTimer::PageOperationTimer(QObject *parent) : QObject(parent),
    m_items(nullptr),
    m_interval(500)
{
}

PageOperationTimer::~PageOperationTimer() {
    stop();
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

void PageOperationTimer::doRead() {
    //    qDebug() << "Read..." << m_items->count();
    foreach (auto item, m_items->items()) {
        item->setValue(ReadDataItem(item));
    }
    m_flag = false;
}

QVariant PageOperationTimer::ReadDataItem(const DataItem *item) {
    //TODO
//    qDebug() << "read from " << item->name() << item->value().typeName();
    int r = item->value().toInt();
    r += 1;
//    qDebug() << r;
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

void PageOperationTimer::runSync() {
    if (m_flag)
        return;
    m_flag = true;
    QtConcurrent::run(this, &PageOperationTimer::doRead);
}
