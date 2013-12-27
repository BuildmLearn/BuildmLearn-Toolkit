// Author: Pankaj Nathani

#include <QApplication>
#include <QtCore>
#include "mainwindow.h"
#include <QDebug>

void main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;

    try{
    w.show();
    }
    catch(std::exception& e){
        QMessageBox::information(&w,QString("Oops") , QString("Something went wrong. The toolkit will now close. Please relaunch the toolkit to create your apps. \nError:") + e.what());
    }

    a.exec();
}
