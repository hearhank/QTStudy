#include "datanode.hpp"

DataNode::DataNode(QObject* parent)
    : QObject(parent), m_value(QVariant()), m_refNames(),
      m_convertType(CH::DataConverter::None), m_load(false), m_desc(nullptr),
      m_calc(nullptr), m_unit(""), m_pControlType(PControlType::Label),
      m_enabled(true) {
  // connect(this, &DataNode::valueChanged, this, &DataNode::formatValue);
}

DataNode::~DataNode() {
    if (m_desc != nullptr)
        m_desc->deleteLater();
    //    qDebug() << "~DataNode()";
}

void DataNode::Load(const QHash<QString, DataNode*> datas) {
  if (m_load)
    return;
  //  qDebug() << name() << " =>Load";
  if (m_refNames.count() > 0) {
    foreach (auto name, m_refNames) {
      if (datas.contains(name)) {
        connect(datas[name], &DataNode::valueChanged, this,
                &DataNode::getValueChanged);
        m_refNodes.append(const_cast<DataNode*>(datas[name]));
      }
    }
    qDebug() << name() << " Load";
    getValueChanged();
  }
  m_load = true;
  foreach (auto item, m_children) {
    if (!item->isLoad())
      item->Load(datas);
  }
}
void DataNode::getValueChanged() {
  qDebug() << this->name() << m_refNames;
  QList<QVariant> list;
  QListIterator<DataNode*> i(this->m_refNodes);
  while (i.hasNext()) {
    list.append(i.next()->value());
  }
  qDebug() << this->value();
  emit valueChanged(this->value(), list);
}

void DataNode::add(QQmlListProperty<DataNode> *list, DataNode *node)
{
    reinterpret_cast<DataNode*>(list->data)->add(node);
}

int DataNode::count(QQmlListProperty<DataNode> *list)
{
    return reinterpret_cast<DataNode*>(list->data)->count();
}

DataNode *DataNode::at(QQmlListProperty<DataNode> *list, int index)
{
    return reinterpret_cast<DataNode*>(list->data)->at(index);
}

void DataNode::clear(QQmlListProperty<DataNode> *list)
{
    reinterpret_cast<DataNode*>(list->data)->clear();
}

QVariant DataNode::getFValue() const { return m_fValue; }

void DataNode::setFValue(const QVariant& val) {
  qDebug() << name() << val;
  if (m_fValue != val) {
    m_fValue = val;
    emit fValueChanged(m_fValue);
  }
}

QVariant DataNode::formatValue(const QVariant& val) {
  if (this->m_pControlType == DataNode::ComboBox) {
    return getNode(val.toInt())->name();
  }
  return val;
}
QVariant DataNode::value() const { return m_value; }

void DataNode::setValue(const QVariant& value) {

  if (m_value != value) {
    m_value = value;
    qDebug() << this->name() << value;

    setFValue(formatValue(m_value));
    if (m_refNodes.count() == 0) {
      emit valueChanged(m_value, QList<QVariant>());
    } else {
      getValueChanged();
    }
  }
}

bool DataNode::getSelected() const { return m_selected; }

void DataNode::setSelected(bool selected)
{
    if (m_selected != selected) {
        m_selected = selected;
        emit selectedChanged(m_selected);
    }
}

DataNode* DataNode::getNode(int index) {
  if (index >= 0 && m_children.count() > index) {
    return m_children[index];
  }
  return nullptr;
}
QList<DataNode*> DataNode::nodes() { return m_children; }

QQmlListProperty<DataNode> DataNode::children()
{
    return QQmlListProperty<DataNode>(this, m_children);
}

void DataNode::add(DataNode *node) {
    m_children.append(node);
    emit childrenChanged(m_children.count());
}

int DataNode::count() {
    return m_children.count();
}

DataNode *DataNode::at(int index) const {
    return m_children.at(index);
}

void DataNode::clear() {
    m_children.clear();
    emit childrenChanged(0);
}

DataCalc *DataNode::calc() const
{
    return m_calc;
}

void DataNode::setCalc(DataCalc *calc)
{
    m_calc = calc;
}

bool DataNode::getHidden() const
{
    return m_hidden;
}

void DataNode::setHidden(bool hidden) { m_hidden = hidden; }

QString DataNode::name() const { return m_name; }

void DataNode::setName(const QString &name)
{
    if (m_name != name) {
        m_name = name;
        emit nameChanged(m_name);
    }
}

QStringList DataNode::refNames() const
{
    return m_refNames;
}

void DataNode::setRefNames(const QStringList &refNames)
{
    m_refNames = refNames;
}

bool DataNode::isLoad() const
{
    return m_load;
}

CH::DataConverter DataNode::convertType() const
{
    return m_convertType;
}

void DataNode::setConvertType(const CH::DataConverter &converter)
{
    m_convertType = converter;
}

QList<DataNode *> DataNode::refNodes() const
{
    return m_refNodes;
}

DataDesc *DataNode::desc() const
{
    return m_desc;
}

void DataNode::setDesc(DataDesc *desc)
{
    m_desc = desc;
}

QString DataNode::unit() const {
    return m_unit;
}

void DataNode::setUnit(const QString &unit) {
    if (m_unit != unit) {
        m_unit = unit;
        emit unitChanged(m_unit);
    }
}

int DataNode::pControlType() const {
    return m_pControlType;
}


void DataNode::setPControlType(const int &elementType) {
    if (m_pControlType != elementType) {
        m_pControlType = static_cast<DataNode::PControlType>(elementType);
        emit pControlTypeChanged(m_pControlType);
    }
}

bool DataNode::enabled() const {
    return m_enabled;
}

void DataNode::setEnabled(bool enabled) {
    if (m_enabled != enabled) {
        m_enabled = enabled;
        emit enabledChanged(m_enabled);
    }
}

//bool DataItem::getStore() const
//{
//    return m_store;
//}

//void DataItem::setStore(bool store)
//{
//    m_store = store;
//}


