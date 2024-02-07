#ifndef FORGOT_H
#define FORGOT_H

#include <QDialog>
#include <newpwd.h>

namespace Ui {
class forgot;
}

class forgot : public QDialog
{
    Q_OBJECT

public:
    explicit forgot(QWidget *parent = nullptr);
    ~forgot();
    QString u ;

private slots:
    void on_submit_clicked();

private:
    Ui::forgot *ui;
};

#endif // FORGOT_H
