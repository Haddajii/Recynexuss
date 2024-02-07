#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include<QMessageBox>

#include "main_page.h"

#include "newacc.h"
#include "newacc.h"
#include "forgot.h"
#include "MYarduino.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_log_btn_clicked();

    void on_log_btn_2_clicked();


    void on_newAcc_clicked();

    void on_forgotPwd_clicked();

   void update_label() ;

private:
    Ui::MainWindow *ui;
    Arduino arduino ;
    QByteArray data ;

    bool checkPasswordInDatabase(char password);


    QString getUsernameFromDatabase(char password);
};
#endif // MAINWINDOW_H
