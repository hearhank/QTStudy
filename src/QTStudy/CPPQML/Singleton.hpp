#ifndef SINGLETON_HPP
#define SINGLETON_HPP
#include <QMutexLocker>
#include <QObject>
#include <QScopedPointer>

template <class T> class Singleton {
public:
    template <typename ... Args> static T& Instance(Args... args) {
        if (m_instance.isNull()) {
            QMutexLocker lock(&m_mutex);
            if (m_instance.isNull()) {
                m_instance.reset(new T(args ...));
            }
        }
        return *m_instance.data();
    }
    static T& getInstance(void) {
        if (m_instance == nullptr) {
            QMutexLocker lock(&m_mutex);
            if (m_instance.isNull()) {
                m_instance.reset(new T());
            }
        }
        return *m_instance.data();
    }
    //TODO
    static void DestroyInstall() {
      QObject* instance = static_cast<QObject*>(m_instance.data());
      if (instance != nullptr) {
        instance->deleteLater();
      } else {
        delete m_instance.data();
      }
      m_instance = nullptr;
    }

private:
    Singleton (void);
    virtual ~Singleton (void);
    Singleton (const Singleton  &);

    Singleton  &operator=(const Singleton  &);

    static QScopedPointer<T> m_instance;
    static QMutex m_mutex;
};

template <class T>
QScopedPointer<T> Singleton <T>::m_instance;
template <class T>
QMutex Singleton <T>::m_mutex;
#endif // SINGLETON_HPP
