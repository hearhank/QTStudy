#ifndef CONVERTSERVERS_HPP
#define CONVERTSERVERS_HPP

#include <QObject>
#include "nameconvert.hpp"
#include "EnumTypes.hpp"

class ConvertServers : public QObject
{
    Q_OBJECT
public:
    explicit ConvertServers(QObject *parent = nullptr);
    ~ConvertServers();


    void Register(ConverterType::DataConverter type, NameConvert *service);
    NameConvert *GetService(ConverterType::DataConverter type);

signals:

public slots:
private:
    QHash<ConverterType::DataConverter, NameConvert*> m_Services;
};

#endif // CONVERTSERVERS_HPP
