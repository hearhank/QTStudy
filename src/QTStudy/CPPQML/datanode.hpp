#ifndef DATAITEM_HPP
#define DATAITEM_HPP

#include <QObject>
#include <QVariant>
#include <QHash>
#include <QDebug>
#include <QList>

#include "EnumTypes.hpp"
#include "datadesc.hpp"
#include "datacalc.hpp"
#include <QQmlListProperty>

class DataNode : public QObject
{
    Q_OBJECT
    Q_ENUMS(PControlType)

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QVariant value READ value WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(QStringList refNames READ refNames WRITE setRefNames)
    Q_PROPERTY(CH::DataConverter convertType READ convertType WRITE setConvertType)
    Q_PROPERTY(DataDesc * desc READ desc WRITE setDesc)
    Q_PROPERTY(DataCalc * calc READ calc WRITE setCalc)
    Q_PROPERTY(QString unit READ unit WRITE setUnit NOTIFY unitChanged)
    Q_PROPERTY(int pControlType READ pControlType WRITE setPControlType NOTIFY pControlTypeChanged)
    Q_PROPERTY(bool enabled READ enabled WRITE setEnabled NOTIFY enabledChanged)
//    Q_PROPERTY(bool store READ getStore WRITE setStore)
    Q_PROPERTY(bool hidden READ getHidden WRITE setHidden)
    Q_PROPERTY(QQmlListProperty<DataNode> children READ children NOTIFY childrenChanged)
    Q_PROPERTY(bool selected READ getSelected WRITE setSelected NOTIFY selectedChanged)
public:
    enum PControlType {
        Label,
        SWitchButton,
        ComboBox,
        TextBox,
        Button
    };
    Q_ENUM(PControlType)

    explicit DataNode(QObject *parent = nullptr);
    ~DataNode();

    void Load(const QList<DataNode*> datas);
    QVariant value() const;
    void setValue(const QVariant &value);

    QString name() const;
    void setName(const QString &name);

    QStringList refNames() const;
    void setRefNames(const QStringList &refNames);

    bool isLoad() const;

    CH::DataConverter convertType() const;
    void setConvertType(const CH::DataConverter &convertType);

    QList<DataNode *> refNodes() const;

    DataDesc *desc() const;
    void setDesc(DataDesc *desc);
    DataCalc *calc() const;
    void setCalc(DataCalc *calc);
    QString unit() const;
    void setUnit(const QString &unit);

    int pControlType() const;
    void setPControlType(const int &pControlType);

    bool enabled() const;
    void setEnabled(bool enabled);

//    bool getStore() const;
//    void setStore(bool store);

    bool getHidden() const;
    void setHidden(bool hidden);



    QQmlListProperty<DataNode> children();
//    void setChildNodes(const QQmlListProperty<DataNode> &childNodes);

    void add(DataNode *node);
    int count();
    DataNode *at(int index) const;
    void clear();
    bool getSelected() const;
    void setSelected(bool selected);

signals:
    void nameChanged(const QString &name);
    void unitChanged(const QString &unit);
    void pControlTypeChanged(const int &pControlType);
    void enabledChanged(const bool &enabled);
    void valueChanged(const QVariant &val, const QList<QVariant> &vals);
    void childrenChanged(const int &count);
    void selectedChanged(const bool &val);

public slots:
    void getValueChanged();
private:
    static void add(QQmlListProperty<DataNode> *list, DataNode *node);
    static int count(QQmlListProperty<DataNode> *list);
    static DataNode *at(QQmlListProperty<DataNode> *list, int index);
    static void clear(QQmlListProperty<DataNode> *list);

    QVariant m_value;
    QString m_name;
    QStringList m_refNames;
    QList<DataNode *> m_refNodes;
    CH::DataConverter m_convertType;
    bool m_load;
    DataDesc *m_desc;
    DataCalc *m_calc;
    QString m_unit;
    PControlType m_pControlType;
    bool m_enabled = true;
//OLD 请在主页添加此类型的变量,去掉。
//    bool m_store = false;
    bool m_hidden = false;
    QList<DataNode*> m_children;
    bool m_selected = false;
};

#endif // DATAITEM_HPP
