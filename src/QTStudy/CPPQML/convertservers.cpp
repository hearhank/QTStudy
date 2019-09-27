#include "convertservers.hpp"

ConvertServers::ConvertServers(QObject *parent) : QObject(parent)
{

}

ConvertServers::~ConvertServers() {
    QHashIterator<ConverterType::DataConverter, NameConvert *> i(m_Services);
    while (i.hasNext()) {
        i.next().value()->deleteLater();
    }
    m_Services.clear();
}

void ConvertServers::Register(ConverterType::DataConverter type,
                              NameConvert *service) {
    if (!m_Services.contains(type)) {
        m_Services.insert(type, service);
    }
}

NameConvert *ConvertServers::GetService(ConverterType::DataConverter type) {
    if (m_Services.contains(type)) {
        return m_Services[type];
    }
    return nullptr;
}

