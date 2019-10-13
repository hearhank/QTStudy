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

  Q_PROPERTY(QStringList refNames READ refNames WRITE setRefNames)
  Q_PROPERTY(CH::DataConverter converter READ converter WRITE setConverter)
  Q_PROPERTY(DataDesc* desc READ desc WRITE setDesc)
  Q_PROPERTY(DataCalc* calc READ calc WRITE setCalc)

  Q_PROPERTY(QString unit READ unit WRITE setUnit NOTIFY unitChanged)
  Q_PROPERTY(int control READ control WRITE setControl NOTIFY controlChanged)
  Q_PROPERTY(QVariant fvalue READ fvalue WRITE setFvalue NOTIFY fvalueChanged)
public:
  enum ControlType { Label, SWitchButton, ComboBox, TextBox, Button };
  Q_ENUM(ControlType)

  explicit DataNode(QObject* parent = nullptr);
  ~DataNode() override;

  void Load(const QHash<QString, DataNode*> datas);
  void Unload();
  void setValue(const QVariant& value) override;

  QStringList refNames() const;
  void setRefNames(const QStringList& refNames);

  bool isLoad() const;

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

signals:
  void unitChanged(const QString& unit);
  void controlChanged(const int& control);
  void fvalueChanged(const QVariant& val);

public slots:
  void getFvalueSlots();

private:
  QVariant formatValue(const QVariant& val);
  QList<DataNode*> m_refNodes;
  bool m_load = false;

  QStringList m_refNames;
  CH::DataConverter m_converter;
  DataDesc* m_desc;
  DataCalc* m_calc;
  QString m_unit;
  ControlType m_controlType;
  QVariant m_fvalue;
};

#endif // DATAITEM_HPP
