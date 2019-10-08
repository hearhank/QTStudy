#ifndef DATACALC_HPP
#define DATACALC_HPP

#include <QObject>

class DataCalc : public QObject
{
    Q_OBJECT
    Q_ENUMS(CalcType)

    Q_PROPERTY(qreal value READ value WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(CalcType type READ type WRITE setType)
public:
    explicit DataCalc(QObject *parent = nullptr);

    enum CalcType { Zoom, Add };
    Q_ENUM(CalcType)
    qreal value() const;
    void setValue(qreal value);

    CalcType type() const;
    void setType(const CalcType &type);

signals:
    void valueChanged(double val);
public slots:
private:
    qreal m_value;
    CalcType m_type;
};

#endif // DATACALC_HPP
