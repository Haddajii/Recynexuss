#ifndef COLLECTE_H
#define COLLECTE_H
#include <QString>
#include <QSqlQueryModel>
#include <QPieSeries>

class QPieSeries;

class Collecte
{
    public:
        Collecte();
        Collecte(int, QString, QString, QString, QString);
        int getid();
        QString getdate();
        QString getmateriaux();
        QString getresp();
        QString getstatut();
        void setid(int);
        void setdate(QString);
        void setmateriaux(QString);
        void setresp(QString);
        void setstatut(QString);

        bool ajouter();
        QSqlQueryModel* afficher();
        bool supprimer(int id);
        bool rechercher(int id);
        QSqlQueryModel* tri(bool ascendance);
        QtCharts::QPieSeries* getDistribution_Materiaux();

    private:
        int id;
        QString date, materiaux, resp, statut;
};

#endif // COLLECTE_H

