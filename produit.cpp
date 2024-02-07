#include "produit.h"

Produit::Produit(int Id_Produit, QString type, float Poids, float Prix_Achat, QString Statut_De_Disponibilite ,QString Date_Ajout)
{
    this->Id_Produit=Id_Produit;
    this->type=type;
    this->Poids=Poids;
    this->Prix_Achat=Prix_Achat;
    this->Statut_De_Disponibilite=Statut_De_Disponibilite;
    this->Date_Ajout=Date_Ajout;

}
bool Produit::ajouterPODUIT()
{
    QSqlQuery query;
    QString res  = QString::number(Id_Produit);
    QString res1 = QString::number(Poids);
    QString res2 = QString::number(Prix_Achat);


    query.prepare("insert into produit (Id_Produit, type, Poids, Prix_Achat, Statut_De_Disponibilite, Date_Ajout)""values(:Id_Produit,:type,:Poids,:Prix_Achat,:Statut_De_Disponibilite,:Date_Ajout)");
    query.bindValue(":Id_Produit",res);
    query.bindValue(":type",type);
    query.bindValue(":Poids",res1);
    query.bindValue(":Prix_Achat",res2);
    query.bindValue(":Statut_De_Disponibilite",Statut_De_Disponibilite);
    query.bindValue(":Date_Ajout",Date_Ajout);

    return query.exec();
}
QSqlQueryModel * Produit::afficher ()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from produit");


    return model;
}
bool Produit::supprimer(int Id_Produit)
{
        QSqlQuery query;

        query.prepare("DELETE FROM produit WHERE Id_Produit = :Id_Produit");
        query.bindValue(":Id_Produit", Id_Produit);

        return query.exec();
}
bool Produit::modifier()
{
    QSqlQuery query;
    QString res1 = QString::number(Id_Produit);
    QString res2 = QString::number(Poids);
    QString res3 = QString::number(Prix_Achat);

    query.prepare("UPDATE produit SET type= :type, Poids= :Poids, Prix_Achat= :Prix_Achat, Statut_De_Disponibilite= :Statut_De_Disponibilite, Date_Ajout= :Date_Ajout WHERE Id_Produit= :Id_Produit ");
    query.bindValue(":Id_Produit", res1);
    query.bindValue(":type", type);
    query.bindValue(":Poids", res2);
    query.bindValue(":Prix_Achat", res3);
    query.bindValue(":Statut_De_Disponibilite", Statut_De_Disponibilite);
    query.bindValue(":Date_Ajout", Date_Ajout);

    return query.exec();
}
/*QSqlQueryModel* Produit::rechercherProduit(int Id_Produit)
{
    QSqlQueryModel* model = new QSqlQueryModel();
        QSqlQuery query;

        query.prepare("SELECT * FROM produit WHERE Id_Produit = :Id_Produit");
        query.bindValue(":Id_Produit", Id_Produit);

        if (query.exec()) {
            model->setQuery(query);
            return model;
        } else {
            qDebug() << "Erreur lors de la recherche : " << query.lastError().text();
            delete model;
            return nullptr;
        }
}*/
