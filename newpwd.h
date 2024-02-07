#ifndef NEWPWD_H
#define NEWPWD_H

#include <QDialog>
#include <forgot.h>
namespace Ui {
class NewPwd;
}

class NewPwd : public QDialog
{
    Q_OBJECT

public:
    explicit NewPwd(QWidget *parent = nullptr);
    ~NewPwd();

private slots:
    void on_pushButton_clicked();

private:
    Ui::NewPwd *ui;
};

#endif // NEWPWD_H
