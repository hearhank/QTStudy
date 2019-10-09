#include "pageoperationtimer.hpp"

PageOperationTimer::PageOperationTimer(QObject* parent)
    : QObject(parent), m_items(), m_interval(500) {
}

PageOperationTimer::~PageOperationTimer() {
    stop();
    // qDebug() << "~Page Operation Timer";
}

void PageOperationTimer::setDataItems(DataNodes* nodes) {
  if (!m_items.contains(nodes->name())) {
    m_items.insert(nodes->name(), nodes);
    foreach (auto node, extendNodes(nodes)) {
      //      qDebug() << node->name() << node->refNames();
      m_allNodes.insert(node->name(), node);
    }
  }
}

void PageOperationTimer::start() {
  foreach (auto item, m_items.values()) { item->Load(m_allNodes); }
  connect(&m_timer, &QTimer::timeout, this, &PageOperationTimer::runSync);
  m_timer.start(m_interval);
}

void PageOperationTimer::stop() {
    m_timer.stop();
    disconnect(&m_timer, &QTimer::timeout, this, &PageOperationTimer::runSync);
}

void PageOperationTimer::runSync() {

  QFuture<void> future =
      QtConcurrent::run(this, &PageOperationTimer::doReadAll);
  future.waitForFinished();
}

void PageOperationTimer::doReadAll() {
  QMutexLocker lock(&m_mutex);
  foreach (auto node, m_allNodes.values()) {
    if (node->desc() != nullptr) {
      node->setValue(ReadDataByNode(node));
    }
  }
}

QList<DataNode*> PageOperationTimer::extendNodes(const DataNodes* nodes) {
  QList<DataNode*> datas;
  foreach (auto node, const_cast<DataNodes*>(nodes)->nodeList()) {
    datas.append(extend(node));
  }
  return datas;
}

QList<DataNode*> PageOperationTimer::extend(const DataNode* node) {
  QList<DataNode*> nodes;
  nodes.append(const_cast<DataNode*>(node));
  foreach (auto cnode, const_cast<DataNode*>(node)->nodes()) {
    nodes.append(extend(cnode));
  }
  return nodes;
}

void PageOperationTimer::read(const QList<DataNode*> nodes) {
  if (nodes.count() > 0) {
    foreach (auto node, nodes) {
      if (node->desc() != nullptr)
        node->setValue(ReadDataByNode(node));
      read(node->nodes());
    }
  }
}

QVariant PageOperationTimer::ReadDataByNode(const DataNode* item) {
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


