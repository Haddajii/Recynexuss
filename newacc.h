#ifndef NEWACC_H
#define NEWACC_H

#include <QDialog>
#include<QWidget>
namespace Ui {
class NewAcc;
}

class NewAcc : public QDialog
{
    Q_OBJECT

public:
    explicit NewAcc(QWidget *parent = nullptr);
    ~NewAcc();

private slots:
    void on_create_clicked();

private:
    Ui::NewAcc *ui;
};

#endif // NEWACC_H
