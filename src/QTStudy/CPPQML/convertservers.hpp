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


    void Register(CH::DataConverter type, QObject *service);
    QObject *GetService(CH::DataConverter type);

signals:

public slots:
private:
    QHash<CH::DataConverter, QObject*> m_Services;
};

#endif // CONVERTSERVERS_HPP
