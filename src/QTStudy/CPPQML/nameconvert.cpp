#include "nameconvert.hpp"

NameConvert::NameConvert(QObject *parent) : QObject(parent)
{

}

QVariant NameConvert::Convert(const QList<DataNode *> datas) {
    QString str;
    QListIterator < DataNode * > i(datas);
    while (i.hasNext()) {
        str += i.next()->value().toString();
    }
    return str;
}
