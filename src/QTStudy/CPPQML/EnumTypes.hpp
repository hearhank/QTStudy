#ifndef ENUMTYPES_HPP
#define ENUMTYPES_HPP

#include <QObject>

class ConverterType : public QObject
{
    Q_OBJECT
    Q_ENUMS(DataConverter)
    Q_ENUMS(DeviceType)
public:
    ConverterType(QObject *parent = nullptr) : QObject(parent){
    }
    enum DataConverter { None,
                         NameC };
    Q_ENUM(DataConverter)
    enum DeviceType {
        SLmini,
        DGK,
        DGKMK3,
        Eccentricity,
        SLminiMK3
    };
    Q_ENUM(DeviceType)

};


#endif // ENUMTYPES_HPP

