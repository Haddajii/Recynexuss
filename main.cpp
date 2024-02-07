#include "mainwindow.h"
#include <QCamera>
#include <QCameraViewfinder>
#include <QVBoxLayout>
#include <QApplication>
#include <QMessageBox>
#include "connection.h"
#include "MYarduino.h"
#include "main_page.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Connection c ;
    bool test = c.createconnection() ;












    MainWindow w;
    main_page z ;
    if(test){
        z.addCameraWidget();
        w.show();
        QMessageBox::information(nullptr,QObject::tr("database is open"),
        QObject::tr("connection successful .\n"
                    "click cancel to exit"),QMessageBox::Cancel);

    }
    else{
        QMessageBox::critical(nullptr,QObject::tr("databse is not open"),
                              QObject::tr("connection failed .\n"
                                          "click cancel to exit"),QMessageBox::Cancel);
    }



    return a.exec();
}
