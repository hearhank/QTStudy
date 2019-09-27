#ifndef DATAITEM_HPP
#define DATAITEM_HPP

#include <QObject>
#include <QVariant>
#include <QHash>

#include "EnumTypes.hpp"
#include "datadesc.hpp"

class DataItem : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(QVariant value READ value WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(QStringList refNames READ refNames WRITE setRefNames)
    Q_PROPERTY(ConverterType::DataConverter convertType READ convertType WRITE setConvertType)
    Q_PROPERTY(DataDesc * desc READ desc WRITE setDesc)
public:

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

    ConverterType::DataConverter convertType() const;
    void setConvertType(const ConverterType::DataConverter &convertType);

    QList<DataItem *> refItems() const;




    DataDesc *desc() const;
    void setDesc(DataDesc *desc);

signals:
    void valueChanged(const QVariant &newVal);
public slots:
private:
    QVariant m_value;
    QString m_name;
    QStringList m_refNames;
    QList<DataItem*> m_refItems;
    ConverterType::DataConverter m_convertType;
    bool m_load;
    DataDesc *m_desc;
};

#endif // DATAITEM_HPP
