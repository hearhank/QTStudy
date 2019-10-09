#ifndef DATAITEMS_HPP
#define DATAITEMS_HPP

#include "Singleton.hpp"
#include "convertservers.hpp"
#include "datanode.hpp"
#include "modbusconvert.hpp"
#include <QDebug>
#include <QList>
#include <QObject>
#include <QQmlListProperty>
#include <QString>

class DataNodes : public QObject {
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<DataNode> nodes READ nodes NOTIFY nodesChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
public:
    explicit DataNodes(QObject *parent = nullptr);
    ~DataNodes();

    QQmlListProperty<DataNode> nodes();
    void add(DataNode *);
    int count();
    DataNode *at(int) const;
    void clear();
    QList<DataNode *> nodeList();

    void Load(QHash<QString, DataNode*> nodes);

    //    Q_INVOKABLE DataNode *getStore(const QString &name);
    QString name() const;
    void setName(const QString &name);

signals:
    void nodesChanged(int count);
    void nameChanged(const QString &name);
public slots:
    //    void upgradeValue(int index, const QVariant &val);
    //    void update();

private:
  void load(QList<DataNode*> nodes);
  static void add(QQmlListProperty<DataNode>* list, DataNode* at);
  static int count(QQmlListProperty<DataNode>* list);
  static DataNode* at(QQmlListProperty<DataNode>* list, int index);
  static void clear(QQmlListProperty<DataNode>* list);
  QList<DataNode*> m_nodes;
  QString m_name;
};

#endif // DATAITEMS_HPP
