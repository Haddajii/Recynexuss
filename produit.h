#ifndef PRODUIT_H
#define PRODUIT_H

#include <QTextCharFormat>
#include <QSqlQueryModel>
#include <QTextTableCell>
#include <QTextDocument>
#include <QTextTable>
#include <QFileDialog>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextCursor>
#include <QTextTable>
#include <QTableView>
#include <QSqlQuery>
#include <QPrinter>
#include <QString>
#include <QDebug>
#include <QtSql>




class Produit
{
private:
    int Id_Produit;
    float Prix_Achat, Poids ;
    QString type , Statut_De_Disponibilite, Date_Ajout;

public:
    //constructeurs
        Produit(){}
        Produit(int, QString, float, float, QString, QString);


    //getters
    int getIdPoduit(){return Id_Produit;}
    QString getNom(){return type;}
    float getPrixAchat(){return Prix_Achat;}
    float getPoids(){return Poids;}
    QString getStatutDeDisponibilite(){return Statut_De_Disponibilite;}
    QString getDateAjout(){return Date_Ajout;}

    //setters
    void getIdPoduit(int i){ Id_Produit=i;}
    void getNom(QString t){ type=t;}
    void getPrixAchat(float pa){ Prix_Achat=pa;}
    void getPoids(float p){ Poids=p;}
    void getStatutDeDisponibilite(QString s){ Statut_De_Disponibilite=s;}
    void getDateAjout(QString d){ Date_Ajout=d;}

    //methods
    bool ajouterPODUIT();
    QSqlQueryModel * afficher ();
    bool supprimer(int);
    bool modifier();
    static QSqlQueryModel* rechercherProduit(int);


};

#endif // PRODUIT_H

