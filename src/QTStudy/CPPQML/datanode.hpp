#ifndef DATAITEM_HPP
#define DATAITEM_HPP

#include <QObject>
#include <QVariant>
#include <QHash>
#include <QDebug>
#include <QList>

#include "EnumTypes.hpp"
#include "datacalc.hpp"
#include "datadesc.hpp"
#include "nodebase.hpp"
#include <QQmlListProperty>

class DataNode : public NodeBase {
  Q_OBJECT
  Q_ENUMS(ControlType)

  Q_PROPERTY(QStringList sources READ sources WRITE setSources)
  Q_PROPERTY(CH::DataConverter converter READ converter WRITE setConverter)
  Q_PROPERTY(DataDesc* desc READ desc WRITE setDesc)
  Q_PROPERTY(DataCalc* calc READ calc WRITE setCalc)

  Q_PROPERTY(QString unit READ unit WRITE setUnit NOTIFY unitChanged)
  Q_PROPERTY(int control READ control WRITE setControl NOTIFY controlChanged)
  Q_PROPERTY(QVariant fvalue READ fvalue WRITE setFvalue NOTIFY fvalueChanged)
  Q_PROPERTY(
      QStringList targets READ targets WRITE setTargets NOTIFY targetsChanged)
public:
  enum ControlType { Label, SWitchButton, ComboBox, TextBox, Button };
  Q_ENUM(ControlType)

  explicit DataNode(QObject* parent = nullptr);
  ~DataNode() override;

  void Load(const QHash<QString, DataNode*> datas);

  void setValue(const QVariant& value) override;

  CH::DataConverter converter() const;
  void setConverter(const CH::DataConverter& converter);

  QList<DataNode*> refNodes() const;

  DataDesc* desc() const;
  void setDesc(DataDesc* desc);
  DataCalc* calc() const;
  void setCalc(DataCalc* calc);
  QString unit() const;
  void setUnit(const QString& unit);

  int control() const;
  void setControl(const int& control);

  QVariant fvalue() const;
  void setFvalue(const QVariant& val);

  QStringList sources() const;
  void setSources(const QStringList& val);

  QStringList targets() const;
  void setTargets(const QStringList& val);

signals:
  void unitChanged(const QString& unit);
  void controlChanged(const int& control);
  void fvalueChanged(const QVariant& val);
  void targetsChanged(const QStringList& val);
  void targetUpdated(DataNode* target);
  void sourceUpdated(const QList<QVariant>& datas);

public slots:
  void someSourceChanged();

private:
  QVariant formatValue(const QVariant& val);
  QList<DataNode*> m_sourceNodes;
  QList<DataNode*> m_targetNodes;
  bool m_load = false;

  QStringList m_sources;
  QStringList m_targets;
  CH::DataConverter m_converter;
  DataDesc* m_desc;
  DataCalc* m_calc;
  QString m_unit;
  ControlType m_controlType;
  QVariant m_fvalue;
};

#endif // DATAITEM_HPP
