#include <QCoreApplication>

#include "res.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

//    Cache->Set("Name", QDateTime::currentDateTime(), "SLmini");
//    Cache->Set("Name", "Rain", "DGK");
//    Cache->Set("Name", "Hank", "DGK");
    Cache->Load("SLmini");
    qDebug() << Cache->Get("Name", "", "SLmini")->Value().toString();
    qDebug() << Cache->Get("Name", "", "DGK")->Value().toString();
    Cache->Print();
    int r = a.exec();
    return r;
}
