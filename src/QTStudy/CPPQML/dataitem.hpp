#ifndef DATAITEM_HPP
#define DATAITEM_HPP

#include <QObject>
#include <QVariant>
#include <QHash>
#include <QDebug>

#include "EnumTypes.hpp"
#include "datadesc.hpp"

class DataItem : public QObject
{
    Q_OBJECT
    Q_ENUMS(EleType)

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QVariant value READ value WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(QStringList refNames READ refNames WRITE setRefNames)
    Q_PROPERTY(CH::DataConverter convertType READ convertType WRITE setConvertType)
    Q_PROPERTY(DataDesc * desc READ desc WRITE setDesc)
    Q_PROPERTY(QString unit READ unit WRITE setUnit NOTIFY unitChanged)
    Q_PROPERTY(EleType eletype READ eletype WRITE setEletype NOTIFY eletypeChanged)
    Q_PROPERTY(bool enabled READ enabled WRITE setEnabled NOTIFY enabledChanged)
public:
    enum EleType {
        Label,
        SWitchButton,
        ComboBox,
        TextBox,
        Button
    };
    Q_ENUM(EleType)

    explicit DataItem(QObject *parent = nullptr);
    ~DataItem();

    void Load(const QList<DataItem*> datas);
    QVariant value() const;
    void setValue(const QVariant &value);

    QString name() const;
    void setName(const QString &name);

    QStringList refNames() const;
    void setRefNames(const QStringList &refNames);

    bool isLoad() const;

    CH::DataConverter convertType() const;
    void setConvertType(const CH::DataConverter &convertType);

    QList<DataItem *> refItems() const;

    DataDesc *desc() const;
    void setDesc(DataDesc *desc);

    QString unit() const;
    void setUnit(const QString &unit);

    EleType eletype() const;
    Q_INVOKABLE int getEletype();
    void setEletype(const EleType &eletype);

    bool enabled() const;
    void setEnabled(bool enabled);

signals:
    void nameChanged(const QString &name);
    void unitChanged(const QString &unit);
    void eletypeChanged(const EleType &eletype);
    void enabledChanged(const bool &enabled);
    void valueChanged(const QVariant &newVal);
public slots:
private:
    QVariant m_value;
    QString m_name;
    QStringList m_refNames;
    QList<DataItem*> m_refItems;
    CH::DataConverter m_convertType;
    bool m_load;
    DataDesc *m_desc;
    QString m_unit;
    EleType m_eletype;
    bool m_enabled;
};

#endif // DATAITEM_HPP
