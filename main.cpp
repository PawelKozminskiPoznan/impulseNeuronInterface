#include <QApplication>
#include "Mainwindow.h"

#include <QThread>
#include <ctime>

int main(int argc, char *argv[])
{
    QApplication u(argc, argv);
    MainWindow w;
//    QThread thread;
//    thread.setObjectName("Network");
//    QObject::connect(&thread, SIGNAL(startOfLearning()),
//                     &w, SLOT(unenable_window()));
//    QObject::connect(&thread, SIGNAL(endOfLearning()),
//                     &w, SLOT(enable_window()));
    w.show();
    return u.exec();;
}
