#ifndef NODEBASE_HPP
#define NODEBASE_HPP

#include <QObject>
#include <QQmlListProperty>
#include <QVariant>

class NodeBase : public QObject {
  Q_OBJECT
  Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
  Q_PROPERTY(QVariant value READ value WRITE setValue NOTIFY valueChanged)
  Q_PROPERTY(QVariant tag READ tag WRITE setTag NOTIFY tagChanged)
  Q_PROPERTY(
      QQmlListProperty<NodeBase> children READ children NOTIFY childrenChanged)
  Q_PROPERTY(
      bool selected READ selected WRITE setSelected NOTIFY selectedChanged)
  Q_PROPERTY(
      bool disabled READ disabled WRITE setDisabled NOTIFY disabledChanged)
  // Q_PROPERTY(bool enabled READ enabled WRITE setEnabled NOTIFY
  // enabledChanged)
public:
  explicit NodeBase(QObject* parent = nullptr);

  QQmlListProperty<NodeBase> children();
  void add(NodeBase* node);
  int count();
  NodeBase* at(int index) const;
  void clear();

  QList<NodeBase*> nodes() const;
  NodeBase* getNode(const int index);

  //   void Load(const QHash<QString, NodeBase*> datas);

public:
  QString name() const;
  void setName(const QString& name);

  QVariant value() const;
  virtual void setValue(const QVariant& value);

  QVariant tag() const;
  void setTag(const QVariant& tag);

  bool selected() const;
  void setSelected(bool val);

  bool disabled() const;
  void setDisabled(bool val);

signals:
  void nameChanged(const QString& name);
  void valueChanged(const QVariant& val);
  void childrenChanged(int flag, const QList<NodeBase*>& datas); //?
  void tagChanged(const QVariant& val);
  void selectedChanged(bool val);
  void disabledChanged(bool val);
  //  void enabledChanged(bool val);

public slots:
protected:
  QString m_name;
  QVariant m_value;
  QVariant m_tag;
  bool m_selected;
  bool m_disabled;
  //  bool m_enabled;
  QList<NodeBase*> m_datas;

private:
  static void add(QQmlListProperty<NodeBase>* list, NodeBase* node);
  static int count(QQmlListProperty<NodeBase>* list);
  static NodeBase* at(QQmlListProperty<NodeBase>* list, int index);
  static void clear(QQmlListProperty<NodeBase>* list);
};

#endif // NODEBASE_HPP
