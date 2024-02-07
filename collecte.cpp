#include "collecte.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QPieSeries>
#include <QtCharts/QPieSeries>

Collecte::Collecte()
{
    id = 0;
    date = ' ';
    materiaux = ' ';
    resp = ' ';
    statut = ' ';
}

Collecte::Collecte(int id, QString date, QString materiaux, QString resp, QString statut)
{
    this->id = id;
    this->date = date;
    this->materiaux = materiaux;
    this->resp = resp;
    this->statut = statut;
}

int Collecte::getid()
{
    return id;
}

QString Collecte::getdate()
{
    return date;
}

QString Collecte::getmateriaux()
{
    return materiaux;
}

QString Collecte::getresp()
{
    return resp;
}

QString Collecte::getstatut()
{
    return statut;
}

void Collecte::setid(int id)
{
    this->id = id;
}

void Collecte::setdate(QString date)
{
    this->date = date;
}

void Collecte::setmateriaux(QString materiaux)
{
    this->materiaux = materiaux;
}

void Collecte::setresp(QString resp)
{
    this->resp = resp;
}

void Collecte::setstatut(QString statut)
{
    this->statut = statut;
}

bool Collecte::ajouter()
{
    QSqlQuery query;
    QString id_string = QString::number(id);

    query.prepare("INSERT INTO COLLECTE (ID, DATECOLLECTE, MATERIAUX, RESPONSABLE, STATUT) "
                  "VALUES (:id, :date, :materiaux, :resp, :statut)");
    query.bindValue(":id", id_string);
    query.bindValue(":date", date);
    query.bindValue(":materiaux", materiaux);
    query.bindValue(":resp", resp);
    query.bindValue(":statut", statut);
    return query.exec();
}

QSqlQueryModel* Collecte::afficher()
{
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT * FROM COLLECTE");

    return model;
}

bool Collecte::supprimer(int id)
{
    QSqlQuery query;
    query.prepare("Delete from COLLECTE where ID = :id");
    query.bindValue(":id", id);
    return query.exec();
}

bool Collecte::rechercher(int id)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM COLLECTE WHERE ID = :id");
    query.bindValue(":id", id);

    if (query.exec() && query.next())
    {
        id = query.value(0).toInt();
        date = query.value(1).toString();
        materiaux = query.value(2).toString();
        resp = query.value(3).toString();
        statut = query.value(4).toString();

        return true;
    }

    return false;
}

QSqlQueryModel* Collecte::tri(bool ascendance)
{
    QSqlQueryModel *model = new QSqlQueryModel;

    QString sortOrder = ascendance ? "ASC" : "DESC";
    QString queryString = QString("SELECT * FROM COLLECTE ORDER BY ID %1").arg(sortOrder);

    model->setQuery(queryString);

    return model;
}

QtCharts::QPieSeries* Collecte::getDistribution_Materiaux()  // Use the fully qualified name
{
    QSqlQuery query;
    query.prepare("SELECT MATERIAUX, COUNT(*) FROM COLLECTE GROUP BY MATERIAUX");

    if (query.exec()) {
        QtCharts::QPieSeries* series = new QtCharts::QPieSeries;  // Use the fully qualified name

        while (query.next()) {
            QString materiaux = query.value(0).toString();
            int count = query.value(1).toInt();

            series->append(materiaux, count);
        }
        return series;
    }
    return nullptr;
}
