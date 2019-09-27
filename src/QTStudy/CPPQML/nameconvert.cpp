#include "nameconvert.hpp"

NameConvert::NameConvert(QObject *parent) : QObject(parent)
{

}

QVariant NameConvert::Convert(const QList<DataItem *> datas) {
    QString str;
    QListIterator<DataItem *> i(datas);
    while (i.hasNext()) {
        str += i.next()->value().toString();
    }
    return str;
}
