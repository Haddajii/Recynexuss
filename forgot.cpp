#include "forgot.h"
#include "ui_forgot.h"
#include <QSqlQuery>
#include <QMessageBox>

forgot::forgot(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::forgot)
{
    ui->setupUi(this);
}

forgot::~forgot()
{
    delete ui;
}

void forgot::on_submit_clicked()
{
    QString UserName = ui->lineEdit->text();
     int phone = ui->phone->text().toInt() ;


      QSqlQuery query;
      query.prepare("SELECT \"phone\" FROM comptes WHERE username = :username");
      query.bindValue(":username", UserName);

      if (query.exec() && query.next()) {
          u = UserName ;

          int storedPhone = query.value("phone").toInt();


          if (storedPhone == phone) {

              this->hide();
              NewPwd *mainpage = new NewPwd();
              mainpage->show();
          } else {

              QMessageBox::warning(this, "", "That is not your phone number");
          }
      } else {

          QMessageBox::warning(this, "", "Username not found");
      }

}

