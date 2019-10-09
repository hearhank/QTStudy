#include "datanodes.hpp"

DataNodes::DataNodes(QObject *parent) : QObject(parent)
{

}
DataNodes::~DataNodes(){
    //    qDeleteAll(m_items);
    qDebug() << "~DataNodes()";
}

QQmlListProperty<DataNode> DataNodes::nodes(){
    return QQmlListProperty<DataNode>(this, m_nodes);
//,
//                                      &DataItems::add,
//                                      &DataItems::count,
//                                      &DataItems::at,
//                                      &DataItems::clear);
}

void DataNodes::add(DataNode *item) {
    m_nodes.append(item);
    emit nodesChanged(m_nodes.count());
}

int DataNodes::count()  {
    return m_nodes.size();
}

DataNode * DataNodes::at(int index) const {
    if(index >= 0 && m_nodes.count() > index) {
        return m_nodes.at(index);
    }else{
        return nullptr;
    }
}

void DataNodes::clear(){
    m_nodes.clear();
    emit nodesChanged(0);
}

// DataNode *DataNodes::getStore(const QString &name) {
//    return Singleton<AppStores>::getInstance().getDataItem(name);
//}

void DataNodes::add(QQmlListProperty<DataNode>* list, DataNode *item)
{
    reinterpret_cast<DataNodes*>(list->data)->add(item);
}

void DataNodes::clear(QQmlListProperty<DataNode> *list)
{
    reinterpret_cast<DataNodes*>(list->data)->clear();
}

QString DataNodes::name() const
{
    return m_name;
}

void DataNodes::setName(const QString& name) { m_name = name; }

void DataNodes::load(QList<DataNode*> nodes) {}

QList<DataNode *> DataNodes::nodeList()
{
    return m_nodes;
}

void DataNodes::Load(QHash<QString, DataNode*> nodes) {
  //  qDebug() << name() << " Load" << m_nodes.count();
  if (m_nodes.count() == 0)
    return;
  foreach (auto node, m_nodes) {
    if (!node->isLoad()) {
      node->Load(nodes);
    }
  }
}

DataNode* DataNodes::at(QQmlListProperty<DataNode> *list, int index)
{
    return reinterpret_cast<DataNodes*>(list->data)->at(index);
}

int DataNodes::count(QQmlListProperty<DataNode> *list)
{
    return reinterpret_cast<DataNodes*>(list->data)->count();
}
