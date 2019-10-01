#include "convertservers.hpp"

ConvertServers::ConvertServers(QObject *parent) : QObject(parent)
{

}

ConvertServers::~ConvertServers() {
  qDebug() << "~ConvertServers";
  QHashIterator<CH::DataConverter, QObject*> i(m_Services);
  while (i.hasNext()) {
    i.next().value()->deleteLater();
  }
  m_Services.clear();
}

void ConvertServers::Register(CH::DataConverter type,
                              QObject *service) {
    if (!m_Services.contains(type)) {
        m_Services.insert(type, service);
    }
}

QObject *ConvertServers::GetService(CH::DataConverter type) {
    if (m_Services.contains(type)) {
        return m_Services[type];
    }
    return nullptr;
}

