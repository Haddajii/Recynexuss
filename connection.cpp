#include "connection.h"
#include<QMessageBox>




Connection::Connection()
{

}

bool Connection::createconnection()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("projet2A");
db.setUserName("mohamed");//inserer nom de l'utilisateur
db.setPassword("esprit23");//inserer mot de passe de cet utilisateur

if (db.open()){
    test = true ;
    QMessageBox::information(nullptr,"DONE","connection successful");
}
else{
  QMessageBox::warning(nullptr,"ERROR","Unable to etablish a database connection");
}








    return  test;
}
