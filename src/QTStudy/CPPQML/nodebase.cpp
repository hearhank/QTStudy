#include "nodebase.hpp"

NodeBase::NodeBase(QObject* parent)
    : QObject(parent), m_name("NodeBase"), m_value(), m_tag(""),
      m_disabled(false), m_enabled(true) {}

QVariant NodeBase::value() const { return m_value; }

void NodeBase::setValue(const QVariant& value) { m_value = value; }

QString NodeBase::name() const { return m_name; }

void NodeBase::setName(const QString& name) {
  if (m_name != name) {
    m_name = name;
    emit nameChanged(m_name);
  }
}

QList<NodeBase*> NodeBase::nodes() const { return m_datas; }

NodeBase* NodeBase::getNode(const int index) {
  if (index >= 0 && index < m_datas.count()) {
    return m_datas.at(index);
  }
  return nullptr;
}

QQmlListProperty<NodeBase> NodeBase::children() {
  return QQmlListProperty<NodeBase>(this, m_datas);
}

void NodeBase::add(NodeBase* node) {
  m_datas.append(node);
  emit childrenChanged(1, QList<NodeBase*>{node});
}

int NodeBase::count() { return m_datas.count(); }

NodeBase* NodeBase::at(int index) const { return m_datas.at(index); }

void NodeBase::clear() {
  m_datas.clear();
  emit childrenChanged(0, QList<NodeBase*>{});
}

QVariant NodeBase::tag() const { return m_tag; }

void NodeBase::setTag(const QVariant& tag) {
  if (m_tag != tag) {
    m_tag = tag;
    emit tagChanged(m_tag);
  }
}

bool NodeBase::selected() const { return m_selected; }

void NodeBase::setSelected(bool val) {
  if (m_selected != val) {
    m_selected = val;
    emit selectedChanged(m_selected);
  }
}

bool NodeBase::disabled() const
{
    return m_disabled;
}

void NodeBase::setDisabled(bool val) {
  if (m_disabled != val) {
    m_disabled = val;
    emit disabledChanged(m_disabled);
  }
}

bool NodeBase::enabled() const { return m_enabled; }

void NodeBase::setEnabled(bool enabled) {
  if (m_enabled != enabled) {
    m_enabled = enabled;
    emit enabledChanged(m_enabled);
  }
}

void NodeBase::add(QQmlListProperty<NodeBase>* list, NodeBase* node) {
    return reinterpret_cast<NodeBase*>(list->data)->add(node);
}

int NodeBase::count(QQmlListProperty<NodeBase>* list) {
  return reinterpret_cast<NodeBase*>(list->data)->count();
}

NodeBase* NodeBase::at(QQmlListProperty<NodeBase>* list, int index) {
  return reinterpret_cast<NodeBase*>(list->data)->at(index);
}

void NodeBase::clear(QQmlListProperty<NodeBase>* list) {
  return reinterpret_cast<NodeBase*>(list->data)->clear();
}
