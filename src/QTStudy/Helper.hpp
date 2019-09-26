#ifndef HELPER_HPP
#define HELPER_HPP

#include "singleton.hpp"
#include "datacache.hpp"
#include <QDebug>

//typedef Singleton<DataCache> Cache;

class Helper {
public:
    static void Load(){

    }
    static void UnLoad() {
        qDebug() << "Help Unload!";
        Singleton<DataCache>::Installace()->deleteLater();
        Singleton<DataCache>::DestroyInstall();
    }
};

#endif // HELPER_HPP

#define Cache Singleton<DataCache>::Installace()

