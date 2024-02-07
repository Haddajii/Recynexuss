#ifndef CLIENTS_H
#define CLIENTS_H
#include <QString>
#include <QDate>
#include <QSqlQueryModel>
#include <QWidget>
#include <QCamera>
#include <QCameraViewfinder>
#include <QVBoxLayout>
#include <QWidget>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QtNetwork>
//#include <QPieSeries>
class Clients: public QWidget
{
private:
    int id,numero, age;
    QString nom, prenom, email,adresse;
    QString date_inscription;

public:
    Clients();
    Clients(int,QString,QString,QString,int,QString,int, QString);

    //getters
    int getId(){return id;}
    QString getNom(){return nom;}
    QString getPrenom(){return prenom;}
    QString getEmail(){return email;}
    int getNumero(){return numero;}
    QString getAdresse(){return adresse;}
    int getAge(){return age;}
    QString getDate_inscription(){return date_inscription;}

    //setters
    void setId(int identifiant){id=identifiant;}
    void setNom(QString nom){this->nom=nom;}
    void setPrenom(QString prenom){this->prenom=prenom;}
    void setEmail(QString email){this->email=email;}
    void setNumero(int tel){numero=tel;}
    void setAdresse(QString adresse){this->adresse=adresse;}
    void setAge(int age){this->age=age;}
    void setDate_incription(QString date){date_inscription=date;}


    //FONCTIONNALITES
    bool ajouter();
    QSqlQueryModel *afficher();
    bool supprimer(int);
    bool modifier();
    bool testNom_prenom_adresse(QString);
    bool testmail(QString);
    int nombreClients();
    //ARDUINO
    bool rechercher_RFID(QString id, QString& nom, QString& prenom);
    //Clients* getByRFID(QString rfid);
    //FONCTIONNALITES
        QSqlQueryModel *rechercher_id(int);
        QSqlQueryModel *rechercher_nom(QString);
        QSqlQueryModel *rechercher_prenom(QString);
        QSqlQueryModel *rechercher_ville(QString);
        QSqlQueryModel* Trier(QString);

        //QPieSeries* afficherStatistiquesAgesParPays();

};

#endif // CLIENTS_H
