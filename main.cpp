// Author: Pankaj Nathani

#include <QApplication>
#include <QtCore>
#include "mainwindow.h"

void main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    a.exec();
}
