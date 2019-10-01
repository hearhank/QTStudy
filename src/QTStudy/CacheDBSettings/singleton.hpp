#ifndef SINGLETON_HPP
#define SINGLETON_HPP
#include <QMutexLocker>
#include <QObject>
#include <QtDebug>
#include <iostream>

using namespace std;

template <class T> class Singleton {
public:
    template <typename ... Args> static T *Instance(Args... args) {
        if (m_instance == nullptr) {
          QMutexLocker lock(&m_mutex);
          if (m_instance == nullptr) {
            m_instance = new T(std::forward<Args>(args)...);
          }
        }
        return m_instance;
    }
    static T *Installace() {
        if (m_instance == nullptr) {
          QMutexLocker lock(&m_mutex);
          if (m_instance == nullptr) {
            m_instance = new T();
          }
        }
        return m_instance;
    }
    //    class CSingleton {
    //    public:
    //      ~CSingleton() {
    //        qDebug() << "Destroy";
    //        QObject* obj = static_cast<QObject*>(m_instance);
    //        if (obj != nullptr) {
    //          obj->deleteLater();
    //        }
    //        m_instance = nullptr;
    //      }
    //    };
    //    static CSingleton CSing;

  private:
    Singleton(void);
    Singleton(const Singleton &);
    Singleton &operator=(const Singleton &);

    virtual ~Singleton(void);

    static T* m_instance;
    static QMutex m_mutex;
};

template <class T> T* Singleton<T>::m_instance = nullptr;
template <class T> QMutex Singleton<T>::m_mutex;
#endif // SINGLETON_HPP
