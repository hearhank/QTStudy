#include "datanode.hpp"

DataNode::DataNode(QObject* parent)
    : NodeBase(parent), m_load(false), m_refNames(),
      m_converter(CH::DataConverter::None), m_desc(nullptr), m_calc(nullptr),
      m_unit(""), m_controlType(ControlType::TextBox) {}

DataNode::~DataNode() {
    if (m_desc != nullptr)
        m_desc->deleteLater();
}

void DataNode::Load(const QHash<QString, DataNode*> datas) {
  if (m_load)
    return;
  if (m_refNames.size() > 0) {
    foreach (auto name, m_refNames) {
      if (datas.contains(name)) {
        connect(datas[name], &DataNode::valueChanged, this,
                &DataNode::getFvalueSlots);
        m_refNodes.append(datas[name]);
      }
    }
    qDebug() << name() << " Load";
    getFvalueSlots();
  }
  m_load = true;
  //  foreach (auto item, m_datas) {
  //    auto temp = dynamic_cast<DataNode*>(item);
  //    if (temp != nullptr && !temp->isLoad()) {
  //      temp->Load(datas);
  //    }
  //  }
}

void DataNode::Unload() {}
void DataNode::getFvalueSlots() {
  QList<QVariant> list;
  QListIterator<DataNode*> i(this->m_refNodes);
  while (i.hasNext()) {
    list.append(i.next()->value());
  }
  emit valueChanged(this->value(), list);
}

QVariant DataNode::fvalue() const { return m_fvalue; }

void DataNode::setFvalue(const QVariant& val) {
  if (m_fvalue != val) {
    m_fvalue = val;
    emit fvalueChanged(m_fvalue);
  }
}

QVariant DataNode::formatValue(const QVariant& val) {
  if (this->m_controlType == DataNode::ComboBox) {
    return getNode(val.toInt())->name();
  }
  return val;
}

void DataNode::setValue(const QVariant& value) {

  if (m_value != value) {
    m_value = value;

    // qDebug() << Q_FUNC_INFO << this->name() << value;
    setFvalue(formatValue(m_value));
    if (m_refNodes.count() == 0) {
      emit valueChanged(m_value, QList<QVariant>());
    } else {
      getFvalueSlots();
    }
  }
}

DataCalc *DataNode::calc() const
{
    return m_calc;
}

void DataNode::setCalc(DataCalc *calc)
{
    m_calc = calc;
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

CH::DataConverter DataNode::converter() const
{
    return m_converter;
}

void DataNode::setConverter(const CH::DataConverter &converter)
{
    m_converter = converter;
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

int DataNode::control() const { return m_controlType; }

void DataNode::setControl(const int& type) {
  if (m_controlType != type) {
    m_controlType = static_cast<DataNode::ControlType>(type);
    emit controlChanged(m_controlType);
  }
}
