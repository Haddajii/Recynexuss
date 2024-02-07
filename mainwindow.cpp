#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QDebug>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QSerialPort>
#include <QSerialPortInfo>
#include "MYarduino.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    int ret=arduino.connect_arduino(); // lancer la connexion à arduino
    switch(ret){
    case(0):qDebug()<< "arduino is available and connected to : "<< arduino.getarduino_port_name();
        break;
    case(1):qDebug() << "arduino is available but not connected to :" <<arduino.getarduino_port_name();
       break;
    case(-1):qDebug() << "arduino is not available";
    }
    QObject::connect(arduino.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));









    QPixmap pix("C:/Users/Mega-PC/Downloads/icon.png");
    ui->icon->setPixmap(pix.scaled(50,50,Qt::KeepAspectRatio)) ;
    ui->icon->setAlignment(Qt::AlignCenter);

    QPixmap p("C:/Users/Mega-PC/Downloads/user.png");
    ui->username->setPixmap(p.scaled(30,30,Qt::KeepAspectRatio));
    ui->username->setAlignment(Qt::AlignCenter);

    QPixmap pi("C:/Users/Mega-PC/Downloads/pwd.png");
    ui->password->setPixmap(pi.scaled(30,30,Qt::KeepAspectRatio));
    ui->password->setAlignment(Qt::AlignCenter);


}

MainWindow::~MainWindow()
{
    delete ui;
    arduino.close_arduino();
}


void MainWindow::update_label()
{
    // Read data from Arduino
    QByteArray data = arduino.read_from_arduino();

    // Process the data as needed
    QStringList idList = QString(data).trimmed().split("\n");

    // Iterate over the received IDs
    for (const QString &id : idList) {
        if (id.isEmpty()) {
            qDebug() << "Received empty ID from Arduino. Ignoring.";
            continue;
        }

        qDebug() << "Received ID from Arduino: " << id;

        // Verify the ID in the database and display the result on the Arduino LCD
        bool idExists = arduino.verifyIdInDatabase(id);

        // Handle the result and update the physical LCD connected to the Arduino
        if (idExists) {
            qDebug() << "ID Exists. Displaying Disponibilite on the physical LCD.";

        } else {
            qDebug() << "ID Not Found. Displaying message on the physical LCD.";

        }
    }
}












void MainWindow::on_log_btn_clicked()
{
    QString UserName = ui->User->text();
      QString Password = ui->pwd->text();


      QSqlQuery query;
      query.prepare("SELECT password FROM comptes WHERE username = :username");
      query.bindValue(":username", UserName);

      if (query.exec() && query.next()) {

          QString storedPassword = query.value("password").toString();


          if (storedPassword == Password) {

              this->hide();
              main_page *mainpage = new main_page();
              mainpage->show();
          } else {

              QMessageBox::warning(this, "", "Incorrect password");
          }
      } else {

          QMessageBox::warning(this, "", "Username not found");
      }

}



void MainWindow::on_log_btn_2_clicked(){
    QMessageBox:: StandardButton reply;
    reply = QMessageBox::question(this,"hammouda","Are you sure to close the application ?",QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes){
        QApplication::quit();
    }
}











void MainWindow::on_newAcc_clicked()
{
   NewAcc *acc = new NewAcc();
   acc->show();
}

void MainWindow::on_forgotPwd_clicked()
{
    forgot *f = new forgot();
    f->show();
}
