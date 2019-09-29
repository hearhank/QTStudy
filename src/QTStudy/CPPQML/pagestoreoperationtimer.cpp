//#include "pagestoreoperationtimer.hpp"

//PageStoreOperationTimer::PageStoreOperationTimer(QObject *parent) : QObject(parent), m_interval(500)
//{

//}

//void PageStoreOperationTimer::start() {
//    connect(&m_timer, &QTimer::timeout, this,
//            &PageStoreOperationTimer::runSync);
//    m_timer.start(500);
//}

//void PageStoreOperationTimer::stop() {
//    m_timer.stop();
//    disconnect(&m_timer, &QTimer::timeout, this,
//               &PageStoreOperationTimer::runSync);
//}

//void PageStoreOperationTimer::runSync() {
//    if (m_flag)
//        return;
//    m_flag = true;
//    QtConcurrent::run(this, &PageStoreOperationTimer::doRead);
//}

//void PageStoreOperationTimer::doRead() {
//    auto items = Singleton<AppStores>::getInstance().getDataItems();
////    qDebug() << "==============" << items.count();
//    foreach (auto item, items) {
////        qDebug() << item->name();
//        item->setValue(ReadDataItem(item));
//    }
//    m_flag = false;
//}

//QVariant PageStoreOperationTimer::ReadDataItem(const DataItem *item) {
//    return item->value();
//}

//void PageStoreOperationTimer::WriteDataItem(const DataItem *item, const QVariant &val)
//{

//}

//int PageStoreOperationTimer::interval() const
//{
//    return m_interval;
//}

//void PageStoreOperationTimer::setInterval(int interval)
//{
//    m_interval = interval;
//}
