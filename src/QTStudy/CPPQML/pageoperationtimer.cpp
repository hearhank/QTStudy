#include "pageoperationtimer.hpp"

PageOperationTimer::PageOperationTimer(QObject* parent)
    : QObject(parent), m_interval(500) {}

PageOperationTimer::~PageOperationTimer() {
    stop();
    // qDebug() << "~Page Operation Timer";
}

void PageOperationTimer::setDataItems(DataNodes* nodes) {
  //  if (!m_items.contains(nodes->name())) {
  //    m_items.insert(nodes->name(), nodes);

  //  }
  foreach (auto node, extendNodes(nodes)) {
    m_allNodes.insert(node->name(), node);
  }
}

void PageOperationTimer::start() {
  foreach (auto item, m_allNodes) {
    if (!item->isLoad()) {
      item->Load(m_allNodes);
    }
  }
  connect(&m_timer, &QTimer::timeout, this, &PageOperationTimer::runSync);
  m_timer.start(m_interval);
}

void PageOperationTimer::stop() {
    m_timer.stop();
    disconnect(&m_timer, &QTimer::timeout, this, &PageOperationTimer::runSync);
}

void PageOperationTimer::runSync() {

  QFuture<void> future = QtConcurrent::run(this, &PageOperationTimer::readAll);
  future.waitForFinished();
}

void PageOperationTimer::readAll() {
  QMutexLocker lock(&m_mutex);
  foreach (auto node, m_allNodes.values()) {
    if (node->desc() != nullptr) {
      node->setValue(ReadDataByNode(node));
    }
  }
}

QList<DataNode*> PageOperationTimer::extendNodes(DataNodes* nodes) {
  QList<DataNode*> datas;
  foreach (auto node, nodes->nodes()) { datas.append(extend(node)); }
  return datas;
}

QList<DataNode*> PageOperationTimer::extend(NodeBase* node) {
  QList<DataNode*> nodes;
  auto temp = dynamic_cast<DataNode*>(node);
  if (temp != nullptr)
    nodes.append(dynamic_cast<DataNode*>(node));

  foreach (auto cnode, node->nodes()) { nodes.append(extend(cnode)); }
  return nodes;
}

QVariant PageOperationTimer::ReadDataByNode(const NodeBase* item) {
  // TODO
  //    int r = item->value().toInt();
  //    r += 1;
  //    return r;
  return item->value();
}

void PageOperationTimer::WriteDataItem(const DataNode *item,
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


