#include "newpwd.h"
#include "ui_newpwd.h"
#include "forgot.h"
#include <QSqlQuery>
#include <QMessageBox>
NewPwd::NewPwd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewPwd)
{
    ui->setupUi(this);
}

NewPwd::~NewPwd()
{
    delete ui;
}

void NewPwd::on_pushButton_clicked()
{
    QString username = ui->lineEdit->text();
     QString newpwd = ui->newpwd->text() ;


      QSqlQuery query;
      query.prepare("UPDATE comptes SET password = :newpwd WHERE username = :username");
      query.bindValue(":username", username);
      query.bindValue(":newpwd", newpwd);


      if (query.exec()) {

          QMessageBox::information(this, "", "password updated");
          this->hide() ;
      }

}
