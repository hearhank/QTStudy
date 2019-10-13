#include "datanodes.hpp"

DataNodes::DataNodes(QObject* parent) : NodeBase(parent) {}
DataNodes::~DataNodes() {
  //    qDebug() << "~DataNodes()";
}

// void DataNodes::Load(QHash<QString, DataNode*> nodes) {
//  if (m_datas.count() == 0)
//    return;
//  foreach (auto node, m_datas) {
//    auto temp = dynamic_cast<DataNode*>(node);
//    if (temp != nullptr && !temp->isLoad())
//      temp->Load(nodes);
//  }
//}
