#ifndef MAIN_PAGE_H
#define MAIN_PAGE_H
#include "QrCode.hpp"
#include <QDialog>
#include "mainwindow.h"
#include "employe.h"
#include "MYarduino.h"
#include "produit.h"
#include "clients.h"
#include "cameramanager.h"
#include <QCameraImageCapture>
#include "collecte.h"
#include "calendar.h"
#include <QStandardItemModel>
namespace Ui {
class main_page;
}

class main_page : public QDialog
{
    Q_OBJECT

public:
    explicit main_page(QWidget *parent = nullptr);
    ~main_page();
    void addCameraWidget() ;
     void Fonction_RFID();
private slots:
    void on_pushButton_clicked();

    void on_ajouter_clicked();

    void on_suppButton_clicked();

    void on_modifier_clicked();



    void on_chercher_clicked();

    void on_actualiser_clicked();

    void on_trie_clicked();

    void on_PDF_clicked();

    void createPieChart();
    void showEvent(QShowEvent *event);




    void on_pageEbtn_clicked();

    void on_pagePbtn_clicked();

    void on_pbAjouter_clicked();

    void on_pbSupprimer_clicked();

    void on_pbModifier_clicked();

    void on_effacer_clicked();

    void on_pbchercher_clicked();

    void on_pbview_clicked();

    void updateTableViewSorting(const QString& selectedAttribute);
    void on_comboBox_colonne_currentIndexChanged(int index);

    void createPieChart_PRODUIT();
    void showEvent_PRODUIT(QShowEvent *event_2);

    void exportToPdf(QTableView *);


    void sendMail(QString,QString);

    void on_pbEnvoiMail_clicked();

    void on_pbPDF_clicked();

    void on_tableView_P_doubleClicked(const QModelIndex &index);

    void on_boutton_ajouter_clicked();

    void on_pageCbtn_clicked();

    void on_Bouton_supprimer_clicked();

    void on_tableView_C_doubleClicked(const QModelIndex &index);

    void exportToPdf_Client(const QString& filePath, QTableView* tableView);

    void on_Bouton_pdf_clicked();

    void on_Bouton_Rechercher_clicked();

    void on_comboBox_tri_activated(int index);

    void capturePhoto();


     void on_Bouton_photo_clicked(int id, const QImage &image);

     void on_pushButton_7_clicked();

     void on_Bouton_Modifier_clicked();

     void on_m_connectButton_clicked();

     void on_m_sendButton_clicked();
     void onReadyRead();

      void onBytesWritten(qint64 bytes);
      void on_pageCLbtn_clicked();

      void updateCalendarEvents();


       void updateNotificationTable(const QString &message);

       void on_pb_ajouter_col_clicked();

       void on_pb_supprimer_col_clicked();

       void on_pb_rechercher_col_clicked();

       void on_pb_nettoyer_col_clicked();
       void on_cbox_tri_col_currentIndexChanged(int index);
       void on_pb_nettoyer_tri_col_clicked();

       void on_pb_pdf_col_clicked();

       void on_pb_stat_materiaux_col_clicked();

private:
    Ui::main_page *ui;
    Employe e ;
    Produit Ptmp;
    Clients Ctmp ;

       QWidget *cameraWidget;
        QVBoxLayout *cameraLayout;
        QCameraViewfinder *viewfinder;
        CameraManager cameraManager;
        QCameraImageCapture *imageCapture;
        QCamera *m_camera;
        QCamera *camera;
        int photoCounter = 1;
        QTcpSocket m_tcpSocket;

        Collecte c;

        QByteArray data;
        QStandardItemModel *notificationModel;
        QCalendarWidget *calendarWidget;
        Calendar *calendar;

        void appendMessage(const QString& message);
protected:
        void resizeEvent(QResizeEvent* event) ;
};

#endif // MAIN_PAGE_H
