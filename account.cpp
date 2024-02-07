#include "account.h"
#include <QDebug>
#include <QSqlError>



account::account(){

}


account::account(QString username , QString password , QString email , int phone)
{
    this->username = username ;
    this->password = password ;
    this->email = email ;
    this->phone = phone ;

}


bool account::ajouterAcc(){
    QSqlQuery  query ;
    QString res = QString::number(phone);

    query.prepare("insert into comptes(username,password,email,\"phone\")" "values (:username, :password, :email, :phone)" );

    query.bindValue(":username",username);
    query.bindValue(":password",password);
    query.bindValue(":email",email);
    query.bindValue(":phone",res);

    return query.exec();


}
