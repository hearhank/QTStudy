#ifndef NAMECONVERT_HPP
#define NAMECONVERT_HPP

#include <QObject>
#include <dataitem.hpp>

class NameConvert : public QObject
{
    Q_OBJECT
public:
    explicit NameConvert(QObject *parent = nullptr);
    QVariant Convert(const QList<DataItem *> datas);
signals:

public slots:
};

#endif // NAMECONVERT_HPP
