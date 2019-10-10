#ifndef PDATARW_HPP
#define PDATARW_HPP

#include <QObject>
#include <QException>
#include "datanode.hpp"
#include "logger.hpp"
#include "appconf.h"
#include "../caches/datacache.hpp"
#include "../caches/psingleton.hpp"

class PDataReadWriter : public QObject
{
    Q_OBJECT
public:
    explicit PDataReadWriter(QObject *parent = nullptr);

    static bool isLittleEndian;
    static QVariant Read(const DataNode *node);
    static void Write(const DataNode *node, const QVariant &val);
signals:

public slots:
private:
    static QVariant Read(const DataDesc *desc);
    static QVariant ReadInput(int offset, int length, DataDesc::DataType type,
                              bool revers);
    static QVariant ReadHold(int offset, int length, DataDesc::DataType type,
                             bool revers);
};

#endif // PDATARW_HPP
