#ifndef EMPLOYE_H
#define EMPLOYE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Employe
{
    QString nom , prenom , role ;
    int CIN,salaire ;
public:
    Employe();
    Employe(int,QString,QString,QString,int);

    QString getNom(){return nom ;}
    QString getPrenom(){return prenom ;}
    QString getRole(){return role ;}
    int getCin(){return CIN ;}
    int getSalaire(){return salaire;}

    void setNom(QString n){nom = n ;}
    void setPrenom(QString p){prenom = p ;}
    void setRole(QString r){role = r ;}
    void setCin(int c){CIN = c ;}
    void setSalaire(int s){salaire = s ;}

    bool ajouter();
    QSqlQueryModel * afficher() ;
    bool supprimer(int) ;
};

#endif // EMPLOYE_H
