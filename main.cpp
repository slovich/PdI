#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/img/resource/img/ico_mainwindow.ico"));
    MainWindow w;
    w.show();
    return QCoreApplication::exec();
}
