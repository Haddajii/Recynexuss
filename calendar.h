#ifndef CALENDAR_H
#define CALENDAR_H

#include <QWidget>
#include <QDate>
#include <QTextBrowser>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include <QDateTimeEdit>
#include <QSpinBox>
#include <QLabel>
#include <QTextTable>
#include <QTextCursor>
#include <QTextCharFormat>
#include <QSqlQuery>
#include <QVector>
#include <QSqlQueryModel>
#include <QTableWidget>
#include <QPushButton>

class Calendar : public QWidget
{
    Q_OBJECT

public:
    Calendar(QWidget *parent = nullptr);

private slots:
    void setFontSize(int size);
    void setMonth(int month);
    void setYear(QDate date);

private:
    void insertCalendar();

    int fontSize;
    QDate selectedDate;
    QTextBrowser *editor;
};

#endif // CALENDAR_H
