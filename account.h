#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <QSqlQuery>
#include <QSqlQueryModel>

class account
{
    QString username , email , password ;
    int phone ;

public:
    account();
    account(QString,QString,QString,int);

    QString getUsername(){return username;}
     QString getPassword(){return password;}
      QString getEmail(){return email;}
      int getPhone(){return phone;}


      void setUsername(QString n){username = n ;}
      void setPassword(QString p){password = p ;}
      void setEmail(QString e){email = e ;}
      void setPhone(int m){phone = m ;}


      bool ajouterAcc();



};

#endif // ACCOUNT_H
