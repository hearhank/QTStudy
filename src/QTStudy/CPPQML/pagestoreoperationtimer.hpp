//#ifndef PAGESTOREOPERATIONTIMER_HPP
//#define PAGESTOREOPERATIONTIMER_HPP

//#include <QObject>
//#include "dataitem.hpp"
//#include <QDateTime>
//#include <QTimer>
//#include <Singleton.hpp>
//#include <QtConcurrent/QtConcurrent>
//#include "appstores.hpp"

//class PageStoreOperationTimer : public QObject
//{
//    Q_OBJECT
//    Q_PROPERTY(int interval READ interval WRITE setInterval)
//public:
//    explicit PageStoreOperationTimer(QObject *parent = nullptr);
//    ~PageStoreOperationTimer() {
//    }
//    Q_INVOKABLE void start();
//    void stop();
//    void runSync();

//    int interval() const;
//    void setInterval(int interval);

//signals:

//public slots:
//    void doRead();
//private:
//    QVariant ReadDataItem(const DataItem *item);
//    void WriteDataItem(const DataItem *item, const QVariant &val);

//    QTimer m_timer;
//    int m_interval;
//    bool m_flag = false;
//};

//#endif // PAGESTOREOPERATIONTIMER_HPP
