#ifndef SINGLETON_HPP
#define SINGLETON_HPP
#include <iostream>
#include <QObject>
#include <QMutexLocker>

using namespace std;

template <class T> class Singleton {
public:
    template <typename ... Args> static T *Instance(Args... args) {
        if (m_instance == nullptr) {
            if (m_instance == nullptr) {
                QMutexLocker lock(&m_mutex);
                m_instance = new T(std::forward<Args>(args)...);
            }
        }
        return m_instance;
    }
    static T *Installace() {
        if (m_instance == nullptr) {
            if (m_instance == nullptr) {
                QMutexLocker lock(&m_mutex);
                m_instance = new T();
            }
        }
        return m_instance;
    }
    static void DestroyInstall() {
        //delete m_instance;
        m_instance = nullptr;
    }

private:
    Singleton(void);
    virtual ~Singleton(void);
    Singleton(const Singleton &);

    Singleton &operator=(const Singleton &);

    static T* m_instance;
    static QMutex m_mutex;
};

template <class T> T *  Singleton<T>::m_instance = nullptr;
template <class T> QMutex Singleton<T>::m_mutex;
#endif // SINGLETON_HPP
