#include "main_page.h"
#include "ui_main_page.h"
#include "employe.h"
#include <QMessageBox>
#include <QTextStream>
#include <QStandardPaths>
#include<QDebug>
#include <QIntValidator>
#include <QRegExpValidator>
#include <QPrinter>
#include <QPainter>
#include <QFileDialog>
#include <QtCharts>
#include <QChartView>
#include <QtCharts/QChartView>
#include <QPieSeries>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QPieSlice>
#include "produit.h"
#include "smtp.h"




using namespace QtCharts;

main_page::main_page(QWidget *parent) :
   QDialog(parent),
    ui(new Ui::main_page)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentWidget(ui->page) ;
    ui->tableView->setModel(e.afficher());
    ui->tableView_P->setModel(Ptmp.afficher());
    ui->tableView_C->setModel(Ctmp.afficher());

    ui->le_id_col->setValidator(new QIntValidator(0, 999, this));
    notificationModel = new QStandardItemModel(this);
    ui->table_notifications->setModel(notificationModel);
    ui->table_collecte->setModel(c.afficher());
    ui->table_pdf_col->setModel(c.afficher());
    calendarWidget = ui->calendarWidget;
    //calendar = new Calendar(this);  // Add this line
    //ui->verticalLayout_calendar->addWidget(calendar);
    connect(ui->cbox_tri_col, SIGNAL(currentIndexChanged(int)), this, SLOT(on_cbox_tri_currentIndexChanged(int)));
    connect(ui->pb_pdf_col, SIGNAL(clicked()), this, SLOT(on_pb_export_pdf_c_clicked()));
    connect(ui->pb_ajouter_col, &QPushButton::clicked, this, [=]() { updateNotificationTable("Collecte ajouté"); });
    connect(ui->pb_supprimer_col, &QPushButton::clicked, this, [=]() { updateNotificationTable("Collecte supprimé"); });
    connect(ui->pb_stat_materiaux_col, SIGNAL(clicked()), this, SLOT(on_pb_stat_materiaux_c_clicked()));
    connect(calendarWidget, &QCalendarWidget::selectionChanged, this, &main_page::updateCalendarEvents);
    updateCalendarEvents();





    connect(ui->m_connectButton, &QPushButton::clicked, this, &main_page::on_m_connectButton_clicked);

    connect(ui->m_sendButton, &QPushButton::clicked, this, &main_page::on_m_sendButton_clicked);

    connect(&m_tcpSocket, &QTcpSocket::readyRead, this, &main_page::onReadyRead);

    connect(&m_tcpSocket, &QTcpSocket::bytesWritten, this, &main_page::onBytesWritten);

    connect(ui->btnRFID, &QPushButton::clicked, this, &main_page::Fonction_RFID);
}

main_page::~main_page()
{
    delete ui;
}

void main_page::on_pushButton_clicked()
{
    this->hide();
    MainWindow *main = new MainWindow() ;
    main->show();

}

void main_page::on_ajouter_clicked()
{
    int cin = ui->cin->text().toInt() ;
    QString nom = ui->nom->text();
    QString prenom = ui->prenom->text();
    QString role = ui->poste->text();
    int salaire = ui->slaire->text().toInt();
    Employe e(cin , nom , prenom , role,salaire);


    bool test = e.ajouter();

    QShowEvent event ;

    if(test){
        ui->tableView->setModel(e.afficher());

        showEvent(&event);
       QMessageBox::information(nullptr,QObject::tr("ok"),
                                QObject::tr("Ajout effectue\n"
                                            "click cancel to exit"),QMessageBox::Cancel);

       ui->cin->clear();
       ui->nom->clear();
       ui->prenom->clear();
       ui->poste->clear();
       ui->slaire->clear();
    }

    else{
        QMessageBox::critical(nullptr,QObject::tr("NOT OK"),
                              QObject::tr("ajout non affectue"),QMessageBox::Cancel);
    }

}







void main_page::on_suppButton_clicked()
{
   int cin = ui->supprimer->text().toInt();
   bool test = e.supprimer(cin);
   QShowEvent event ;
   if(test){
       ui->tableView->setModel(e.afficher());
       showEvent(&event);
       QMessageBox::information(nullptr,QObject::tr("ok"),
                                QObject::tr("supprimer effectuer"),QMessageBox::Cancel);
       ui->supprimer->clear();
   }

   else{
       QMessageBox::critical(nullptr,QObject::tr("NOT OK"),
                                QObject::tr("supprimer non effectuer"),QMessageBox::Cancel);
   }


}

void main_page::on_modifier_clicked()
{
    int cin = ui->cin->text().toInt() ;
    QString nom = ui->nom->text();
    QString prenom = ui->prenom->text();
    QString role = ui->poste->text();
    int salaire = ui->slaire->text().toInt();
    Employe e(cin , nom , prenom , role,salaire);



    QSqlQuery query;
    query.prepare("UPDATE employe SET nom = :nom, salaire = :salaire ,prenom = :prenom, role = :role WHERE cin = :cin");
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":role", role);
    query.bindValue(":cin", cin);
    query.bindValue(":salaire",salaire);

    QShowEvent event ;

    if(query.exec()){
        ui->tableView->setModel(e.afficher());
        showEvent(&event);
       QMessageBox::information(nullptr,QObject::tr("ok"),
                                QObject::tr("modification effectue\n"
                                            "click cancel to exit"),QMessageBox::Cancel);

       ui->cin->clear();
       ui->nom->clear();
       ui->prenom->clear();
       ui->poste->clear();
       ui->slaire->clear();
    }

    else{
        QMessageBox::critical(nullptr,QObject::tr("NOT OK"),
                              QObject::tr("modification non affectue"),QMessageBox::Cancel);
    }
}



void main_page::on_chercher_clicked()
{
    int cin = ui->supprimer->text().toInt();

       QSqlQueryModel* model = new QSqlQueryModel();
       QSqlQuery query;

       query.prepare("SELECT * FROM employe WHERE cin = :cin");
       query.bindValue(":cin", cin);

       if (query.exec()) {
           model->setQuery(query);


           ui->tableView->setModel(model);
       } else {

           delete model;}
}

void main_page::on_actualiser_clicked()
{
    ui->tableView->setModel(e.afficher());
}

void main_page::on_trie_clicked()
{
   QSqlQueryModel *model = new QSqlQueryModel();
   QSqlQuery query ;
   query.prepare("SELECT * FROM employe ORDER BY salaire DESC");


   if (query.exec()) {
       model->setQuery(query);


       ui->tableView->setModel(model);
   } else {

       delete model;}

}

void main_page::on_PDF_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Export to PDF", "", "PDF Files (*.pdf)");

    if (!fileName.isEmpty()) {
        QPrinter printer(QPrinter::HighResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(fileName);

        printer.setPageSize(QPrinter::A4);
        printer.setOrientation(QPrinter::Portrait);

        QPainter painter(&printer);
        painter.setRenderHint(QPainter::Antialiasing);


        double scaleFactor = static_cast<double>(printer.width()) / ui->tableView->width();
        painter.scale(scaleFactor, scaleFactor);


        painter.translate(0, 0);

        ui->tableView->render(&painter);

        painter.end();
    }
}




void main_page::createPieChart() {

    QtCharts::QPieSeries* series = new QtCharts::QPieSeries();
    QSqlQuery query("SELECT role, COUNT(*) FROM employe GROUP BY role");
    int totalCount = 0;

    while (query.next()) {
        QString value = query.value(0).toString();
        int count = query.value(1).toInt();
        totalCount += count;
        series->append(value, count);
    }

    // Update labels with correct percentages
    for (auto slice : series->slices()) {
        qreal percentage = 100.0 *slice->percentage();
        slice->setLabel(QString("%1\n%2%").arg(slice->label()).arg(percentage, 0, 'f', 1));
    }

    QChart* chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("STATISTIQUE");
    chart->setAnimationOptions(QChart::AllAnimations);

    QChartView* chartView = new QChartView(chart);
    chartView->setUpdatesEnabled(true);
    QGridLayout* mainLayout = new QGridLayout();
    mainLayout->addWidget(chartView, 0, 0);

    ui->GB_Statistique->setLayout(new QVBoxLayout());
    ui->GB_Statistique->layout()->addWidget(chartView);
    ui->GB_Statistique->layout()->update();
}

void main_page::showEvent(QShowEvent *event) {
    qDebug() << "showEvent called";
   if (ui->GB_Statistique->layout()) {
        QLayoutItem* item;
        while ((item = ui->GB_Statistique->layout()->takeAt(0)) != nullptr) {
            delete item->widget();  // Delete the widget associated with the layout item
            delete item;            // Delete the layout item
        }
    }
    ui->GB_Statistique->setLayout(new QVBoxLayout());

    QWidget::showEvent(event);
    createPieChart();
}













// Gestion de Produits

void main_page::on_pageEbtn_clicked()
{
   ui->stackedWidget->setCurrentWidget(ui->page);
}

void main_page::on_pagePbtn_clicked()
{
   ui->stackedWidget->setCurrentWidget(ui->page_2);
   QShowEvent event_2 ;
   showEvent_PRODUIT(&event_2);
}

void main_page::on_pbAjouter_clicked()
{
    int Id_Produit = ui->le_IdProduit->text().toInt();
    QString type = ui->le_Type->text();
    float Poids = ui->le_Poids->text().toFloat();
    float Prix_Achat = ui->le_PrixAchat->text().toFloat();
    QString Statut_De_Disponibilite = ui->le_StatutDeDisponibilite->text();
    QString Date_Ajout = ui->le_DateAjout->text();

    Produit p(Id_Produit,type,Poids,Prix_Achat,Statut_De_Disponibilite,Date_Ajout);

    QShowEvent event_2;
    bool test=p.ajouterPODUIT();
    if (test)
    {
        ui->tableView_P->setModel(Ptmp.afficher());
        showEvent(&event_2);
        QMessageBox::information (nullptr, QObject::tr("Ajout effectué"),
                    QObject::tr("Ajout effectué.\n       OK\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Ajout non effectué"),
                    QObject::tr("Ajout non effectué.\n      NOT OK\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}



void main_page::on_pbSupprimer_clicked()
{
    int Id_Produit=ui->le_IdProduit->text().toInt();
    bool test=Ptmp.supprimer(Id_Produit);
    QShowEvent event_2;
    if (test)
    {
        ui->tableView_P->setModel(Ptmp.afficher());
        showEvent_PRODUIT(&event_2);
        QMessageBox::information (nullptr, QObject::tr("Supression effectué"),
                    QObject::tr("Supression effectué.\n        OK\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Supression non effectué"),
                    QObject::tr("Supression non effectué.\n        NOT OK\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}

void main_page::on_pbModifier_clicked()
{
    int Id_Produit = ui->le_IdProduit->text().toInt();
    QString type = ui->le_Type->text();
    float Poids = ui->le_Poids->text().toFloat();
    float Prix_Achat = ui->le_PrixAchat->text().toFloat();
    QString Statut_De_Disponibilite = ui->le_StatutDeDisponibilite->text();
    QString Date_Ajout = ui->le_DateAjout->text();

    Produit p(Id_Produit,type,Poids,Prix_Achat,Statut_De_Disponibilite,Date_Ajout);

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

    QShowEvent event;
    if(query.exec())
    {
        ui->tableView_P->setModel(Ptmp.afficher());
        showEvent(&event);
        QMessageBox::information (nullptr, QObject::tr("Modification effectué"),
                    QObject::tr("Modification effectué.\n        OK\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Modification non effectué"),
                    QObject::tr("Modification non effectué.\n        NOT OK\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}





void main_page::on_effacer_clicked()
{
    ui->le_IdProduit->clear();
    ui->le_PrixAchat->clear();
    ui->le_Poids->clear();
    ui->le_Type->clear();
    ui->le_StatutDeDisponibilite->clear();
    ui->le_DateAjout->clear();
}




void main_page::on_pbchercher_clicked()
{
    int Id_Produit = ui->le_IdProduit_chercher->text().toInt();

       QSqlQueryModel* model = new QSqlQueryModel();
       QSqlQuery query;

       query.prepare("SELECT * FROM produit WHERE Id_Produit = :Id_Produit");
       query.bindValue(":Id_Produit", Id_Produit);

       if (query.exec()) {
           model->setQuery(query);


           ui->tableView_P->setModel(model);
       } else {
           qDebug() << "Erreur lors de la recherche : " << query.lastError().text();
           delete model;
       }
}

void main_page::on_pbview_clicked()
{
   ui->tableView_P->setModel(Ptmp.afficher());
}

void main_page::on_comboBox_colonne_currentIndexChanged(int index)
{
    QString selectedAttribute;
        switch (index) {
            case 0:
               selectedAttribute = "Id_Produit";
                break;
            case 1:
                selectedAttribute = "type";
                break;
            case 2:
                selectedAttribute = "Poids";
                break;
            case 3:
                selectedAttribute = "Prix_Achat";
                break;
            case 4:
                selectedAttribute = "Statut_De_Disponibilite";
                break;
            case 5:
                selectedAttribute = "Date_Ajout";
                break;}
        updateTableViewSorting(selectedAttribute);
}
void main_page::updateTableViewSorting(const QString& selectedAttribute) {

    ui->tableView_P->setSortingEnabled(false);
    QString queryStr = QString("SELECT * FROM produit ORDER BY %1 ASC").arg(selectedAttribute);

    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery(queryStr);

    ui->tableView_P->setModel(model);

    ui->tableView_P->setSortingEnabled(true);
}

void main_page::createPieChart_PRODUIT() {

    QtCharts::QPieSeries* series = new QtCharts::QPieSeries();
    QSqlQuery query("SELECT type, COUNT(*) FROM produit GROUP BY type");
    int totalCount = 0;

    while (query.next()) {
        QString value = query.value(0).toString();
        int count = query.value(1).toInt();
        totalCount += count;
        series->append(value, count);
    }

    // Update labels with correct percentages
    for (auto slice : series->slices()) {
        qreal percentage = 100.0 *slice->percentage();
        slice->setLabel(QString("%1\n%2%").arg(slice->label()).arg(percentage, 0, 'f', 1));
    }

    QChart* chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("STATISTIQUE");
    chart->setAnimationOptions(QChart::AllAnimations);

    QChartView* chartView = new QChartView(chart);
    chartView->setUpdatesEnabled(true);
    QGridLayout* mainLayout = new QGridLayout();
    mainLayout->addWidget(chartView, 0, 0);

    ui->GB_Statistique_2->setLayout(new QVBoxLayout());
    ui->GB_Statistique_2->layout()->addWidget(chartView);
    ui->GB_Statistique_2->layout()->update();
}

void main_page::showEvent_PRODUIT(QShowEvent *event_2) {
    qDebug() << "showEvent_PRODUIT called";
   if (ui->GB_Statistique_2->layout()) {
        QLayoutItem* item;
        while ((item = ui->GB_Statistique_2->layout()->takeAt(0)) != nullptr) {
            delete item->widget();  // Delete the widget associated with the layout item
            delete item;            // Delete the layout item
        }
    }
    ui->GB_Statistique_2->setLayout(new QVBoxLayout());



    createPieChart_PRODUIT();
}


void main_page::sendMail(QString email,QString message)
{
 Smtp* smtp = new Smtp("zeineb.fadhel@esprit.tn", "221JFT4129", "smtp.gmail.com", 465);
    smtp->sendMail("zeineb.fadhel.zeineb@gmail.com", email ,"Smart_recycling_center",message);
}


void main_page::on_pbEnvoiMail_clicked()
{
    Produit p;
    Smtp* mail = new Smtp("zeineb.fadhel@esprit.tn", "221JFT4129", "smtp.gmail.com", 465);
    connect(mail,SIGNAL(status(QString)),this,SLOT(mailSent(QString)));
    QString email = ui->mailAdresseEmail->text();
    QString sujet = ui->mailSujet->text();
    QString message = ui->mailBody->text();
    if(email!="" && sujet!=""&& message!="" )
    {
        mail->sendMail("ouchikh9one@gmail.com",email,sujet,message);
    }

      QMessageBox::information(this, "Smart_recycling_center", "Mail envoyé", QMessageBox::Ok);
}



void main_page::exportToPdf(QTableView *tableView) {
    QTextDocument document;

    // Configuration du format de la première ligne
    QTextBlockFormat firstLineFormat;
    firstLineFormat.setAlignment(Qt::AlignCenter);
    document.rootFrame()->firstCursorPosition().setBlockFormat(firstLineFormat);

    // Ajout du titre
    QTextCursor cursor(&document);
    QTextCharFormat titleFormat;
    titleFormat.setFontWeight(QFont::Bold);
    titleFormat.setFontPointSize(16);
    cursor.setCharFormat(titleFormat);
    cursor.insertText("Liste des Produits\n\n");

    // Création d'un tableau pour afficher les données
    QTextTableFormat tableFormat;
    tableFormat.setBorder(1);
    tableFormat.setBorderStyle(QTextFrameFormat::BorderStyle_Solid);
    tableFormat.setWidth(QTextLength(QTextLength::PercentageLength, 100));
    QTextTable *table = cursor.insertTable(1, 6, tableFormat);

    // Configuration de la première ligne du tableau (en-têtes en gras)
    QTextCharFormat headerFormat;
    headerFormat.setFontWeight(QFont::Bold);
    for (int column = 0; column < 6; ++column) {
        QTextTableCell cell = table->cellAt(0, column);
        cell.setFormat(headerFormat);
        cell.firstCursorPosition().insertText(tableView->model()->headerData(column, Qt::Horizontal).toString());
    }

    // Ajout des données de la table au tableau
    int rowCount = tableView->model()->rowCount();
    int columnCount = tableView->model()->columnCount();
    table->insertRows(1, rowCount);

    for (int row = 0; row < rowCount; ++row) {
        for (int column = 0; column < columnCount; ++column) {
            QTextTableCell cell = table->cellAt(row + 1, column);
            cell.firstCursorPosition().insertText(tableView->model()->data(tableView->model()->index(row, column)).toString());
        }
    }

    // Enregistrement du fichier PDF
    QString fileName = QFileDialog::getSaveFileName(this, "Enregistrer PDF", QString(), "*.pdf");
    if (!fileName.isNull()) {
        QPrinter printer(QPrinter::PrinterResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setPaperSize(QPrinter::A4);
        printer.setOutputFileName(fileName);

        document.print(&printer);
        qDebug() << "Exportation en PDF réussie.";
    }
}



void main_page::on_pbPDF_clicked()
{
   exportToPdf(ui->tableView_P);
}

void main_page::on_tableView_P_doubleClicked(const QModelIndex &index)
{
    QString text ="Id_Produit:"+ ui->tableView_P->model()->data(ui->tableView_P->model()->index(ui->tableView_P->currentIndex().row(),0)).toString()
                     +"type:"+ui->tableView_P->model()->data(ui->tableView_P->model()->index(ui->tableView_P->currentIndex().row(),1)).toString()
                     +"Poids:"+ui->tableView_P->model()->data(ui->tableView_P->model()->index(ui->tableView_P->currentIndex().row(),2)).toString()
                    +"Prix_Achat:"+ui->tableView_P->model()->data(ui->tableView_P->model()->index(ui->tableView_P->currentIndex().row(),3)).toString()
                     +"Statut_De_Disponibilite:"+ui->tableView_P->model()->data(ui->tableView_P->model()->index(ui->tableView_P->currentIndex().row(),4)).toString()
                     +"Date_Ajout:"+ui->tableView_P->model()->data(ui->tableView_P->model()->index(ui->tableView_P->currentIndex().row(),5)).toString();
    using namespace qrcodegen;
    // Create the QR Code object
    QrCode qr = QrCode::encodeText( text.toUtf8().data(), QrCode::Ecc::MEDIUM );
    //image
    qint32 sz = qr.getSize();
    QImage im(sz,sz, QImage::Format_RGB32);
    QRgb black = qRgb(  0,  0,  0);
    QRgb white = qRgb(255,255,255);
    for (int y = 0; y < sz; y++)
    for (int x = 0; x < sz; x++)
       im.setPixel(x,y,qr.getModule(x, y) ? black : white );
     ui->QRcode->setPixmap( QPixmap::fromImage(im.scaled(200,200,Qt::KeepAspectRatio,Qt::FastTransformation),Qt::MonoOnly) );
}


//Gestion des Clients
//*********************************************************************************
//**********************************************************************************





void main_page::on_boutton_ajouter_clicked()
{
    int id=ui->lineEdit_id->text().toInt();
    QString nom=ui->lineEdit_nom->text();
    QString prenom=ui->lineEdit_prenom->text();
    QString email=ui->lineEdit_email->text();
    int numero=ui->lineEdit_numero->text().toInt();
    QString adresse=ui->lineEdit_adresse->text();
    int age=ui->lineEdit_age->text().toInt();
    QString  date_inscription=ui->lineEdit_date->text();
    //QString dateString = date_inscription.toString("yyyy-MM-dd");
    if(Ctmp.testNom_prenom_adresse(adresse))
        {
            //verifiier la validité du mail;
            /*ui->lineEdit_mail->setStyleSheet("color: black");
            ui->lineEdit_id->setStyleSheet("color: black");
            ui->lineEdit_prenom->setStyleSheet("color : black");
            ui->lineEdit_nom->setStyleSheet("color: black");
            ui->lineEdit_adresse->setStyleSheet("color: black");
            ui->lineEdit_telephone->setStyleSheet("color: black");*/
Clients c(id, nom, prenom, email, numero, adresse, age, date_inscription);

bool test=c.ajouter();

if(test)
{//Actualiser la méthode Afficher
    ui->tableView_C->setModel(Ctmp.afficher());
    QString id_string=QString::number(id);
    ui->tableView->setModel(Ctmp.afficher());
    QMessageBox::information(nullptr, QObject::tr("Ok"),
                QObject::tr("Ajouter avec succes.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);

}
else
{
    QMessageBox::critical(nullptr, QObject::tr("not Ok"),
                QObject::tr("Echec ajout\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
}
    }
else
    {
           QMessageBox::critical(nullptr,QObject::tr("ERROR"),
           QObject::tr("VERIFIER LES INFORMATIONS...\n"
           "Click Cancel to quit"),QMessageBox::Cancel);

    }
    if(!Ctmp.testmail(email)) //essayer de réper l'erreur pour pemettre à l'utilisateur de corriger rapidement
    {
        ui->lineEdit_email->setStyleSheet("color: red");

    }
    if(!Ctmp.testNom_prenom_adresse(prenom))
    {
        ui->lineEdit_prenom->setStyleSheet("color: red");
    }
    if(!Ctmp.testNom_prenom_adresse(nom))
    {
        ui->lineEdit_nom->setStyleSheet("color: red");
    }
    if(!Ctmp.testNom_prenom_adresse(adresse))
    {
        ui->lineEdit_adresse->setStyleSheet("color : red");
    }
}


void main_page::on_pageCbtn_clicked()
{
   ui->stackedWidget->setCurrentWidget(ui->page_3);
}

void main_page::on_Bouton_supprimer_clicked()
{
    int id=ui->lineEdit_id->text().toInt();
    QMessageBox::StandardButton reply = QMessageBox::question(this,"SUPPRESSION","ATTENTION!\nETES-VOUS VRAIMENT SÛR DE SUPPRIMER CE CLIENT?", QMessageBox::Yes | QMessageBox::No);

    // Obtenir l'ID du client dans la colonne 0(c'est-à-dire dans la première colonne) de l'index
    //int id = ui->tableView->model()->data(index.sibling(index.row(), 0)).toInt();
    if(reply==QMessageBox::Yes)
        {// Appel de la méthode supprimer de la classe client
           bool test = Ctmp.supprimer(id);


    if (test) {
        // Actualiser la méthode Afficher
        ui->tableView_C->setModel(Ctmp.afficher());
        //mettre les lignes à null
        ui->lineEdit_id->setText("");
        ui->lineEdit_nom->setText("");
        ui->lineEdit_prenom->setText("");
        ui->lineEdit_email->setText("");
        ui->lineEdit_numero->setText("");
        ui->lineEdit_adresse->setText("");
        ui->lineEdit_age->setText("");
        ui->lineEdit_date->setText("");
        QMessageBox::information(nullptr, QObject::tr("Ok"),
                                 QObject::tr("Suppression effectuée.\n"
                                             "Cliquez sur Annuler pour quitter."), QMessageBox::Cancel);
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Not Ok"),
                              QObject::tr("Échec de la suppression.\n"
                                          "Cliquez sur Annuler pour quitter."), QMessageBox::Cancel);
    }
    }
    else
    {
        //afficher un message de débogage
        qDebug()<<"Suppresion annulée";
    }
}

void main_page::on_tableView_C_doubleClicked(const QModelIndex &index)
{
    // Récupérer les données de la ligne sélectionnée
    int row = index.row();
    int id = ui->tableView_C->model()->index(row, 0).data().toInt();
    QString nom = ui->tableView_C->model()->index(row, 1).data().toString();
    QString prenom = ui->tableView_C->model()->index(row, 2).data().toString();
    QString email = ui->tableView_C->model()->index(row, 3).data().toString();
    int numero = ui->tableView_C->model()->index(row, 4).data().toInt();
    QString adresse = ui->tableView_C->model()->index(row, 5).data().toString();
    int age = ui->tableView_C->model()->index(row, 6).data().toInt();
    QString date_inscription = ui->tableView_C->model()->index(row, 7).data().toString();
    // ...

    // Mettre à jour les QLineEdit avec les données récupérées
    ui->lineEdit_id->setText(QString::number(id));
    ui->lineEdit_nom->setText(nom);
    ui->lineEdit_prenom->setText(prenom);
    ui->lineEdit_email->setText(email);
    ui->lineEdit_numero->setText(QString::number(numero));
    ui->lineEdit_adresse->setText(adresse);
    ui->lineEdit_age->setText(QString::number(age));
    ui->lineEdit_date->setText(date_inscription);
    // ...

    QMessageBox::StandardButton reply = QMessageBox::question(this,"Reçu de paiement","VOULEZ-VOUS UN RECU DE PAIEMENT POUR CE CLIENT?", QMessageBox::Yes | QMessageBox::No);


    if(reply==QMessageBox::Yes)
        {
            ui->label_id->setText(ui->lineEdit_id->text());
            ui->label_nom->setText(ui->lineEdit_nom->text());
            ui->label_prenom->setText(ui->lineEdit_prenom->text());
    }
        else
        {
           qDebug()<<"ANNULEE";
        }

}


void main_page::exportToPdf_Client(const QString& filePath, QTableView* tableView)
{
    QPrinter printer;
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(filePath);

    QPainter painter;
    if (!painter.begin(&printer)) {
        // Gérer l'erreur de démarrage du QPainter
        return;
    }

    // Dessiner le TableView sur le QPainter
    tableView->render(&painter);
    qDebug() << "Reached exportToPdf() function.";

    painter.end();
}

void main_page::on_Bouton_pdf_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Exporter en PDF", "", "Fichiers PDF (*.pdf)");

        if (!filePath.isEmpty()) {
            exportToPdf_Client(filePath, ui->tableView_C);
        }
}

void main_page::on_Bouton_Rechercher_clicked()
{
    int id=ui->lineEdit_search->text().toInt();
    if(ui->comboBox_rechercher->currentText()=="ID")
    {//définit le modèle dans tableView avec le modèle de données retourné par cette méthode et permet d'afficher les résultats de la recherche par ID dans tableview.
         ui->tableView_C->setModel(Ctmp.rechercher_id(id));
    }
    if(ui->comboBox_rechercher->currentText()=="NOM")
        {
            QString nom=ui->lineEdit_search->text();
            ui->tableView_C->setModel(Ctmp.rechercher_nom(nom));
        }

        if(ui->comboBox_rechercher->currentText()=="PRENOM")
        {
            QString nom=ui->lineEdit_search->text();
            ui->tableView->setModel(Ctmp.rechercher_prenom(nom));
        }

        if(ui->comboBox_rechercher->currentText()=="VILLE")
        {
            QString nom=ui->lineEdit_search->text();
            ui->tableView_C->setModel(Ctmp.rechercher_ville(nom));
        }
}

void main_page::on_comboBox_tri_activated(int index)
{
    QString critere;
    if(index==2)
    {
        critere="select * from clients ORDER BY AGE";
        /*appelle Trier(critere) de l'objet Ctmp en utilisant la requête de tri critere et définit le modèle dans tableView
         avec le modèle de données retourné par cette méthode et Cela permet d'afficher les données triées dans la vue*/
        ui->tableView_C->setModel(Ctmp.Trier(critere));
    }
    if(index==1)
    {
        critere="select * from clients ORDER BY NUMERO";
        ui->tableView_C->setModel(Ctmp.Trier(critere));
    }
    if(index==0)
    {
        critere="select * from clients ORDER BY NOM";
        ui->tableView_C->setModel(Ctmp.Trier(critere));
    }
}

void main_page::capturePhoto()
{
    // Génère un nom de fichier unique pour chaque photo en utilisant le compteur de photos
    QString fileName = QString("C:/Users/Mega-PC/Desktop/captured_image_%1.jpg").arg(photoCounter);
    imageCapture->capture(fileName); // Capture l'image
    photoCounter++; // Incrémente le compteur de photos
    // Charge l'image capturée
    QImage capturedImage(fileName);

       if (!capturedImage.isNull()) {
           QImage resizedImage = capturedImage.scaled(ui->imageLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);

           ui->imageLabel->setPixmap(QPixmap::fromImage(resizedImage));
           ui->imageLabel->setScaledContents(true);

           // Réajuste la position de l'image dans le QLabel
           ui->imageLabel->setAlignment(Qt::AlignCenter);
       }
}



void main_page::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);

        if (!ui->imageLabel->pixmap())
            return;

        QSize newLabelSize = ui->imageLabel->size();
        QPixmap currentPixmap = ui->imageLabel->pixmap()->scaled(newLabelSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);

        ui->imageLabel->setPixmap(currentPixmap);
        ui->imageLabel->setScaledContents(true);
        ui->imageLabel->setAlignment(Qt::AlignCenter);
}

void main_page::on_Bouton_photo_clicked(int id, const QImage &image)
{
    // Affiche un message d'avertissement et demande le choix de l'utilisateur
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation", "Voulez-vous vraiment prendre une photo ?", QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        // L'utilisateur a choisi "Oui", enregistre l'image
        QString fileName = "C:/Users/Mega-PC/Desktop/captured_image.jpg";
        if (image.save(fileName)) {
            qDebug() << "Image enregistrée avec success! " << fileName;
        } else {
            qDebug() << "Echec de la capture " << fileName;
        }
    } else {
        // L'utilisateur a choisi "Non", n'effectue aucune action
        qDebug() << "Capture photo annulée";
    }
}



/*void main_page::addCameraWidget()
{
    cameraWidget = ui->cameraWidget; // Récupère le widget de la caméra à partir de l'interface utilisateur

    cameraLayout = new QVBoxLayout(cameraWidget); // Crée un nouveau layout vertical pour le widget de la caméra
    cameraWidget->setLayout(cameraLayout); // Applique le layout au widget de la caméra

    viewfinder = new QCameraViewfinder; // Crée une nouvelle instance de QCameraViewfinder, qui est une vue pour afficher le flux vidéo de la caméra
    cameraLayout->addWidget(viewfinder); // Ajoute le viewfinder au layout vertical du widget de la caméra

    cameraManager.setupCamera(viewfinder); // Configure le gestionnaire de caméra en lui spécifiant le viewfinder pour afficher le flux vidéo
    cameraManager.startCamera(); // Démarre la caméra, ce qui active le flux vidéo sur le viewfinder

    imageCapture = new QCameraImageCapture(cameraManager.getCamera()); // Crée une instance de QCameraImageCapture, qui est utilisée pour capturer des images à partir de la caméra

    // Connecte le signal imageCaptured() émis par l'objet imageCapture à la méthode on_Bouton_photo_clicked() de la classe MainWindow
    connect(imageCapture, SIGNAL(imageCaptured(int, const QImage&)),
            this, SLOT(on_Bouton_photo_clicked(int, const QImage&)));

    // Connecte le signal clicked() émis par le bouton Bouton_photo à la méthode capturePhoto() de la classe MainWindow
    connect(ui->Bouton_photo, &QPushButton::clicked, this, &main_page::capturePhoto);
}*/


void main_page::addCameraWidget()
{
    // Create a new widget to hold the camera-related components
    cameraWidget = new QWidget(this);

    // Create a layout for the camera widget
    cameraLayout = new QVBoxLayout(cameraWidget);
    cameraWidget->setLayout(cameraLayout);

    // Create an instance of QCameraViewfinder and set a fixed size
    viewfinder = new QCameraViewfinder(cameraWidget);
    viewfinder->setFixedSize(640, 480);  // Adjust the size accordingly

    // Add the viewfinder to the layout of the camera widget
    cameraLayout->addWidget(viewfinder);

    // Create an instance of QCamera
    m_camera = new QCamera(this);

    // Configure the camera to use the viewfinder
    m_camera->setViewfinder(viewfinder);

    // Create an instance of QCameraImageCapture
    imageCapture = new QCameraImageCapture(m_camera);

    // Connect the signal imageCaptured() to the method on_Bouton_photo_clicked()
    connect(imageCapture, SIGNAL(imageCaptured(int, const QImage&)), this, SLOT(on_Bouton_photo_clicked(int, const QImage&)));

    // Connect the signal clicked() of the Bouton_photo button to the method capturePhoto()
    connect(ui->Bouton_photo, &QPushButton::clicked, this, &main_page::capturePhoto);

    // Start the camera
    m_camera->start();

    // Make sure the camera widget is visible
    cameraWidget->setVisible(true);

    // Assuming you have a main layout, add the camera widget to it
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(cameraWidget);
    setLayout(mainLayout);
}




void main_page::on_pushButton_7_clicked()
{
   addCameraWidget();
}

void main_page::on_Bouton_Modifier_clicked()
{
    int id=ui->lineEdit_id->text().toInt();
    QString nom=ui->lineEdit_nom->text();
    QString prenom=ui->lineEdit_prenom->text();
    QString email=ui->lineEdit_email->text();
    int numero=ui->lineEdit_numero->text().toInt();
    QString adresse=ui->lineEdit_adresse->text();
    int age=ui->lineEdit_age->text().toInt();
    QString  date_inscription=ui->lineEdit_date->text();


Clients c(id, nom, prenom, email, numero, adresse, age, date_inscription);
QMessageBox::StandardButton reply = QMessageBox::question(this,"MODIFICATION","ATTENTION!\nETES-VOUS VRAIMENT SÛR DE MODIFIER CE CLIENT?", QMessageBox::Yes | QMessageBox::No);


if(reply==QMessageBox::Yes)
    {
        bool test = c.modifier();
        if (test)
        {
            // Actualiser la méthode Afficher
            ui->tableView_C->setModel(Ctmp.afficher());
            QMessageBox::information(nullptr, QObject::tr("OK"),
                                     QObject::tr("Modification effectuée\n"
                                                 "Click Cancel to exit."), QMessageBox::Cancel);
        }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                        QObject::tr("Modification échouée\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }
}
    else
    {
       qDebug()<<"MODIFICATION ANNULEE";
    }
}




void main_page::Fonction_RFID()
{
    Clients c;
    QString rfid1 = "b3c317fc"; // Remplacez "valeur_rfid" par la valeur RFID que vous souhaitez rechercher
    QString rfid2 = "53f48adc";

    QString nom;
    QString prenom;

    bool found1 = c.rechercher_RFID(rfid1, nom, prenom);
    bool found2 = c.rechercher_RFID(rfid2, nom, prenom);
    if (found1) {
        qDebug() << "rfid1: " << rfid1;
        QString message = "Nom: " + nom + "\nPrénom: " + prenom;
                QMessageBox::information(this, "Arduino", message, QMessageBox::Ok);

    }
    if (found2) {
        qDebug() << "rfid2: " << rfid2;
        QString message = "Nom: " + nom + "\nPrénom: " + prenom;
                QMessageBox::information(this, "Arduino", message, QMessageBox::Ok);

    }
    else {
        QMessageBox::information(this, "Arduino", "IDENTIFIANT RFID NON TROUVE", QMessageBox::Ok);
    }

}








void main_page::on_m_connectButton_clicked()
{
    m_tcpSocket.connectToHost("127.0.0.1", 50885); // Remplacez l'adresse IP et le port par ceux de votre serveur de chat

        if (m_tcpSocket.waitForConnected()) {
            qDebug() << "Connexion établie avec le serveur.";
        } else {
            qDebug() << "Erreur lors de la connexion au serveur:" << m_tcpSocket.errorString();
        }
}

void main_page::on_m_sendButton_clicked()
{
    QString message = ui->m_messageInput->text();
    m_tcpSocket.write(message.toUtf8());
    ui->m_messageInput->clear();
}


void main_page::onReadyRead()
{
    if (m_tcpSocket.waitForReadyRead()) {
        QByteArray data = m_tcpSocket.readAll();
        QString message = QString::fromUtf8(data);
        qDebug() << "Message received from server: " << message;
        appendMessage(message);
    } else {
        qDebug() << "Erreur lors de la réception des données du serveur:" << m_tcpSocket.errorString();
    }
}

void main_page::appendMessage(const QString& message)
{
    ui->m_messageView->append(message);
}

void main_page::onBytesWritten(qint64 bytes)
{
    qDebug() << "Message sent. Bytes written: " << bytes;
}

//Gestion des collectes
//*************************************************************************************************************************************************
//*************************************************************************************************************************************************

void main_page::on_pageCLbtn_clicked()
{
  ui->stackedWidget->setCurrentWidget(ui->page_6) ;
}

void main_page::updateNotificationTable(const QString &message)
{
    qDebug() << "Updating table with message:" << message;

    QStandardItem *notificationItem = new QStandardItem(message);
    notificationModel->appendRow(notificationItem);
}

void main_page::on_pb_ajouter_col_clicked()
{
    QMessageBox M;
    int id = ui->le_id_col->text().toInt();
    QString date = ui->le_date_col->text();
    QString materiaux = ui->le_materiaux_col->text();
    QString resp = ui->le_resp_col->text();
    QString statut = ui->le_statut_col->text();

    Collecte C(id, date, materiaux, resp, statut);

    if (C.ajouter())
    {
        M.setText("Ajout avec succes");
        ui->table_collecte->setModel(c.afficher());
    }
    else
    {
        M.setText("Ajout non effectue");
    }
    M.exec();
}

void main_page::on_pb_supprimer_col_clicked()
{
    QMessageBox M;
    Collecte C1;
    C1.setid(ui->le_id_supp_col->text().toInt());
    bool test = C1.supprimer(C1.getid());
    if (test)
    {
        M.setText("Suppression avec succes");
        ui->table_collecte->setModel(c.afficher());
    }
    else
        M.setText("Erreur de suppression");
    M.exec();
}

void main_page::on_pb_rechercher_col_clicked()
{
    QMessageBox M;
    int id_recherche = ui->le_id_recherche_col->text().toInt();
    ui->table_recherche_col->setModel(new QSqlQueryModel);
    Collecte resultat;
    bool existe = resultat.rechercher(id_recherche);
    if (existe)
    {
        QSqlQueryModel *Model = new QSqlQueryModel;
        Model->setQuery(QString("SELECT * FROM COLLECTE WHERE ID_C = %1").arg(id_recherche));
        ui->table_recherche_col->setModel(Model);
    }
    else
    {
        M.setText("Cet element n'existe pas");
        M.exec();
    }
}

void main_page::on_pb_nettoyer_col_clicked()
{
    ui->table_recherche_col->setModel(new QSqlQueryModel);
    ui->le_id_recherche_col->clear();
}

void main_page::on_cbox_tri_col_currentIndexChanged(int index)
{
    bool ascendant = (index == 0); // 0 pour ascendant; 1 pour descendant
    ui->table_tri_col->setModel(c.tri(ascendant));
}

void main_page::on_pb_nettoyer_tri_col_clicked()
{
   ui->table_tri_col->setModel(new QSqlQueryModel);
}

void main_page::on_pb_pdf_col_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Export PDF", "", "PDF Files (*.pdf)");

    if (!filePath.isEmpty())
    {
        QPrinter printer(QPrinter::PrinterResolution);

        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(filePath);

        QPainter painter(&printer);

        ui->table_pdf_col->render(&painter);
    }
}

void main_page::on_pb_stat_materiaux_col_clicked()
{
    QtCharts::QPieSeries* series = c.getDistribution_Materiaux();  // Use the fully qualified name

    QtCharts::QChart* chart = new QtCharts::QChart();  // Use the fully qualified name
    chart->addSeries(series);
    chart->setTitle("Distribution des matériaux");

    series->setLabelsVisible();

    QtCharts::QChartView* chartView = new QtCharts::QChartView(chart);  // Use the fully qualified name
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->chart()->setAnimationOptions(QtCharts::QChart::AllAnimations);  // Use the fully qualified name
    chartView->chart()->legend()->hide();
    chartView->resize(1000, 500);

    chartView->show();
}


void main_page::updateCalendarEvents()
{
    // Clear existing date formatting
    calendarWidget->setDateTextFormat(QDate(), QTextCharFormat());

    // Retrieve events from the COLLECTE table
    QSqlQueryModel *model = new QSqlQueryModel(this);
    model->setQuery("SELECT DATECOLLECTE FROM COLLECTE");

    // Iterate through the query results
    for (int i = 0; i < model->rowCount(); ++i) {
        QSqlRecord record = model->record(i);
        QDate eventDate = QDate::fromString(record.value("DATECOLLECTE").toString(), "dd/MM/yyyy");

        // Mark the date on the calendar
        QTextCharFormat format;
        format.setBackground(Qt::yellow);  // You can customize the background color
        calendarWidget->setDateTextFormat(eventDate, format);
    }

    // Delete the model to release memory
    delete model;
}




