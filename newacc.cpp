#include "newacc.h"
#include "ui_newacc.h"
#include "account.h"
#include <QMessageBox>
#include<QDebug>
NewAcc::NewAcc(QWidget *parent) : QDialog(parent), ui(new Ui::NewAcc)
{
    ui->setupUi(this);

   // Additional constructor implementation, if needed
    // You can initialize variables, set up connections, etc.
}

NewAcc::~NewAcc()
{
    delete ui;  // Don't forget to delete the UI object in the destructor
    // Additional destructor implementation, if needed
}




void NewAcc::on_create_clicked()
{
   int phone = ui->phone->text().toInt() ;
   QString username = ui->user->text() ;
   QString password = ui->password->text();
   QString email = ui->email->text();


     qDebug() << "Username:" << username;
     qDebug() << "Password:" << password;
     qDebug() << "Email:" << email;
     qDebug() << "Phone:" << phone;


   account a(username,password,email,phone);
   bool test = a.ajouterAcc();



   if(test){
      QMessageBox::information(nullptr,QObject::tr("ok"),
                               QObject::tr("Ajout effectue\n"
                                           "click cancel to exit"),QMessageBox::Cancel);

             ui->phone->clear();
             ui->user->clear();
             ui->password->clear();
             ui->email->clear();


   }

   else{
       QMessageBox::critical(nullptr,QObject::tr("NOT OK"),
                             QObject::tr("ajout non affectue"),QMessageBox::Cancel);
   }






}
