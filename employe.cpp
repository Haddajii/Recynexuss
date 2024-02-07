#include "employe.h"

Employe::Employe() {

}




Employe::Employe(int CIN , QString nom , QString prenom ,QString role,int salaire)
{
  this->CIN = CIN ;
  this->nom = nom ;
  this->prenom = prenom ;
  this->role = role ;
  this->salaire = salaire ;

}


bool Employe::ajouter(){
    QSqlQuery query ;
    QString res = QString::number(CIN) ;
    QString res1 = QString::number(salaire);
    query.prepare("insert into employe (cin,nom,prenom,role,salaire)""values(:cin,:nom,:prenom,:role,:salaire)");

    query.bindValue(":cin",res);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
     query.bindValue(":role",role);
     query.bindValue(":salaire",res1);

     return query.exec();
}


QSqlQueryModel * Employe::afficher(){
    QSqlQueryModel *model = new QSqlQueryModel();

    model->setQuery("select * from employe");


    return model ;
}

bool Employe::supprimer(int cin){
    QSqlQuery query ;
    QString res = QString::number(cin);
    query.prepare("Delete from employe where cin = :cin");
    query.bindValue(":cin",res);
    return query.exec();
}





