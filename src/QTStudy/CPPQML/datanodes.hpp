#ifndef DATAITEMS_HPP
#define DATAITEMS_HPP

#include "Singleton.hpp"
#include "convertservers.hpp"
#include "datanode.hpp"
#include "modbusconvert.hpp"
#include "nodebase.hpp"
#include <QDebug>
#include <QList>
#include <QObject>
#include <QQmlListProperty>
#include <QString>

class DataNodes : public NodeBase {
  Q_OBJECT
public:
    explicit DataNodes(QObject *parent = nullptr);
    ~DataNodes();

    //    void Load(QHash<QString, DataNode*> nodes);
};

#endif // DATAITEMS_HPP
