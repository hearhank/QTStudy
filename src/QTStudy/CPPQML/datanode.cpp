#include "datanode.hpp"

DataNode::DataNode(QObject* parent)
    : NodeBase(parent), m_load(false), m_sources(),
      m_converter(CH::DataConverter::None), m_desc(nullptr), m_calc(nullptr),
      m_unit(""), m_controlType(ControlType::TextBox) {}

DataNode::~DataNode() {
    if (m_desc != nullptr)
        m_desc->deleteLater();
}

void DataNode::Load(const QHash<QString, DataNode*> datas) {
  if (m_load)
    return;

  if (m_sources.size() > 0) {
    foreach (auto name, m_sources) {
      if (datas.contains(name)) {
        connect(datas[name], &DataNode::valueChanged, this,
                &DataNode::someSourceChanged);
        m_sourceNodes.append(datas[name]);
      }
    }
    qDebug() << name() << " Load";
    someSourceChanged();
  }
  if (m_targets.size() > 0) {
    foreach (auto name, m_targets) {
      if (datas.contains(name)) {
        m_targetNodes.append(datas[name]);
        emit datas[name]->targetUpdated(this);
      }
    }
  }
  m_load = true;
}

void DataNode::someSourceChanged() {
  QList<QVariant> datas;
  QListIterator<DataNode*> i(this->m_sourceNodes);
  while (i.hasNext()) {
    datas.append(i.next()->value());
  }
  emit sourceUpdated(datas);
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

QStringList DataNode::targets() const { return m_targets; }

void DataNode::setTargets(const QStringList &targetNames)
{
    m_targets = targetNames;
}

void DataNode::setValue(const QVariant& value) {
    if (m_value != value) {
        m_value = value;
        setFvalue(formatValue(m_value));
        if (m_sourceNodes.count() == 0) {
          emit valueChanged(m_value);
        } else {
          someSourceChanged();
        }
        // for targets
        foreach (auto target, m_targetNodes) {
          emit target->targetUpdated(this);
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

QStringList DataNode::sources() const { return m_sources; }

void DataNode::setSources(const QStringList& val) { m_sources = val; }

CH::DataConverter DataNode::converter() const { return m_converter; }

void DataNode::setConverter(const CH::DataConverter &converter)
{
    m_converter = converter;
}

QList<DataNode*> DataNode::refNodes() const { return m_sourceNodes; }

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
