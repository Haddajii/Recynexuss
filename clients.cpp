#include "clients.h"
#include <QSqlQuery>
#include <QtSql>
#include <QMessageBox>
#include <QSqlQuery>
#include <QtDebug>
#include <QPrinter>
#include <QPrintDialog>
#include <QTextStream>
#include <QPainter>
Clients::Clients()
{
    //setupUi(this);

    id=0;
    nom=" ";
    prenom=" ";
    email=" ";
    numero=0;
    adresse=" ";
    age=0;
    date_inscription=" ";
}

Clients::Clients(int id,QString nom,QString prenom,QString email,int numero,QString adresse,int age, QString date_inscription)
{
    this->id=id;
    this->nom=nom;
    this->prenom=prenom;
    this->email=email;
    this->numero=numero;
    this->adresse=adresse;
    this->age=age;
    this->date_inscription=date_inscription;
}

bool Clients::ajouter()
{
    QSqlQuery query;


    QString res=QString::number(id);
    query.prepare("insert into clients(id_client, nom, prenom, email, numero, adresse, age, date_inscription) values(:id, :nom, :prenom, :email, :numero, :adresse, :age, :date_inscription)");

    query.bindValue(":id",res);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":email",email);
    query.bindValue(":numero",numero);
    query.bindValue(":adresse",adresse);
    query.bindValue(":age",age);
    query.bindValue(":date_inscription",date_inscription);

    return query.exec();
}

QSqlQueryModel *Clients::afficher()
{
    QSqlQueryModel *model =new QSqlQueryModel();
    model->setQuery("select * from clients");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRENOM"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("EMAIL"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("NUMERO"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("ADRESSE"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("AGE"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("DATE"));
    return model;
}


bool Clients::supprimer(int id)
{
    QSqlQuery query;
    //fait une conversion de id en chaîne de caractères id_string
    QString id_string = QString::number(id);
    query.prepare("DELETE FROM clients WHERE id_client = :id");
    query.bindValue(":id", id_string);
    // Exécution de la requête SQL
    return query.exec();
}

bool Clients::modifier()
{
    QSqlQuery query;
    QString id_string = QString::number(id);
    QString numero_string = QString::number(numero);
    QString age_string = QString::number(age);

        query.prepare("UPDATE clients SET id_client = :id, nom = :nom, prenom = :prenom, email = :email, numero = :numero, adresse = :adresse, age = :age, date_inscription = :date_inscription WHERE id_client = :id");

        query.bindValue(":id", id_string);
        query.bindValue(":nom", nom);
        query.bindValue(":prenom", prenom);
        query.bindValue(":email", email);
        query.bindValue(":numero", numero_string);
        query.bindValue(":adresse", adresse);
        query.bindValue(":age", age_string);
        query.bindValue(":date_inscription", date_inscription);

        return query.exec();
}

/*
{
    QSqlQuery query;
    query.prepare("SELECT pays, COUNT(*) FROM clients GROUP BY adresse");
    if (!query.exec()) {
        // Gestion de l'erreur de la requête
        return nullptr;
    }

    QPieSeries* series = new QPieSeries();

    while (query.next()) {
        QString pays = query.value(0).toString();
        int count = query.value(1).toInt();

        series->append(pays, count);
    }

    return series;
}

QPieSeries* Clients::afficherStatistiquesAgesParDateInscription()
{
    QSqlQuery query;
    query.prepare("SELECT date_inscription, COUNT(*) FROM clients GROUP BY date_inscription");
    if (!query.exec()) {
        // Gestion de l'erreur de la requête
        return nullptr;
    }

    QPieSeries* series = new QPieSeries();

    while (query.next()) {
        QString dateInscription = query.value(0).toString();
        int count = query.value(1).toInt();

        series->append(dateInscription, count);
    }

    return series;
}*/


int Clients::nombreClients()
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM clients");
    if (query.exec() && query.next()) {
        return query.value(0).toInt();
    }
    return 0;
}

//QSqlQueryModel permet la Récupération des données, Tri et filtrage des données, Manipulation des données et Interaction avec les vues
QSqlQueryModel *Clients::rechercher_id(int id)
{
    //stocker les résultats de la requête SQL dans QSqlQueryModel()
    QSqlQueryModel *model=new QSqlQueryModel();
    QSqlQuery query;

    QString id_string=QString::number(id);

    query.prepare("select * from clients where id_client= :id");
    query.bindValue(":id", id_string);
    query.exec();
    //définit les résultats de la requête SQL dans QSqlQueryModel avec setQuery() et permet de stocke les données récupérées dans model
    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));

    return model;
}

QSqlQueryModel *Clients::rechercher_nom(QString nom)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    QSqlQuery query;

    query.prepare("select * from clients where nom= :nom");
    query.bindValue(":nom", nom);
    query.exec();
    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));

    return model;
}

QSqlQueryModel *Clients::rechercher_prenom(QString prenom)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    QSqlQuery query;

    query.prepare("select * from clients where prenom= :prenom");
    query.bindValue(":prenom", prenom);
    query.exec();
    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));

    return model;
}

QSqlQueryModel *Clients::rechercher_ville(QString ville)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    QSqlQuery query;

    query.prepare("select * from clients where nom= :nom");
    query.bindValue(":ville", ville);
    query.exec();
    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));

    return model;
}

QSqlQueryModel *Clients::Trier(QString critere)
{
    QSqlQueryModel* model=new QSqlQueryModel();
    QSqlQuery *query=new QSqlQuery;
    // prépare la requête de tri
    query->prepare(critere);
    query->exec();
    //définit les résultats de la requête de tri dans QSqlQueryModel avec setQuery() et permet de stocker les données triées dans model.
    model->setQuery(*query);

    return model;
}
//ARDUINO
bool Clients::rechercher_RFID(QString id, QString& nom, QString& prenom)
{
    QSqlQuery query;

    query.prepare("SELECT nom, prenom FROM clients WHERE id = :id");
    query.bindValue(":id", id);
    query.exec();

    bool found = query.next();  // Vérifie si la requête a trouvé une correspondance

    if (found) {
        nom = query.value(0).toString();    // Récupère la valeur de la colonne "nom"
        prenom = query.value(1).toString(); // Récupère la valeur de la colonne "prenom"
    }

    return found;
}


bool Clients::testmail(QString mail)
{
    int test=0;
    int position=0;

    if(mail[0]=='@') //le premier caractère est un @
    {
        return false;
    }
    for(int i = 1; i < mail.size(); i++)
    {
        if(mail[i]=='@')
        {
            test++;
            position=i; //recupérer la position du @

        }
    }
    if(test!=1) //il y'a plusieurs @ ou il n'ya pas de @
    {
        return false;
    }

    if(mail[position+1]=='.') //on a le piont juste après le @
    {
        return false;
    }
    for(int i = position+1; i < mail.size(); i++)
    {

        if(mail[i]=='.')
        {
            if(mail.size()>i+1) //S'il y'a des caractère après le point
                return true;
        }
    }
    return false;
}
bool Clients::testNom_prenom_adresse(QString a)
{
    for(int i=0;i<a.size();i++)
    {
        if(a.at(i)=='&'||a.at(i)=='~'||a.at(i)=='#'||a.at(i)=='{'||a.at(i)=='['||a.at(i)=='|'||a.at(i)=='@'
                ||a.at(i)==']'||a.at(i)=='}'||a.at(i)=='!'||a.at(i)=='?'||a.at(i)=='*'||a.at(i)=='%'||a.at(i)=='$'
               )
        {
            return false;
        }

    }

    return true;
}
