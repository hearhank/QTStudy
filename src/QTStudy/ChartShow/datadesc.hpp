#ifndef DATADESC_HPP
#define DATADESC_HPP

#include <QObject>
#include <QDebug>

class DataDesc : public QObject
{
    Q_OBJECT
    Q_ENUMS(DataType)
    Q_ENUMS(DataArea)

    Q_PROPERTY(int offset READ offset WRITE setOffset)
    Q_PROPERTY(int length READ length WRITE setLength)
    Q_PROPERTY(int bitOffset READ bitOffset WRITE setBitOffset)
    Q_PROPERTY(int bitLength READ bitLength WRITE setBitLength)
    Q_PROPERTY(DataType dataType READ dataType WRITE setDataType)
    Q_PROPERTY(DataArea dataArea READ dataArea WRITE setDataArea)
public:
    DataDesc(QObject *parent = nullptr);
    ~DataDesc();

    enum DataType {
        Boolean,
        Byte,
        Short,
        UShort,
        Int,
        UInt,
        Float,
        Long,
        ULong,
        Double,
        String
    };
    Q_ENUM(DataType)
    enum DataArea { Input, Hold };
    Q_ENUM(DataArea)

    int offset() const;
    void setOffset(int offset);

    int length() const;
    void setLength(int length);

    int bitOffset() const;
    void setBitOffset(int bitOffset);

    int bitLength() const;
    void setBitLength(int bitLength);

    DataType dataType() const;
    void setDataType(const DataType &dataType);

    DataArea dataArea() const;
    void setDataArea(const DataArea &dataArea);

signals:


public slots:
private:
    int m_offset;
    int m_length;
    int m_bitOffset;
    int m_bitLength;
    DataType m_dataType;
    DataArea m_dataArea;

};

#endif // DATADESC_HPP
