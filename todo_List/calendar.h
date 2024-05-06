#ifndef CALENDAR_H
#define CALENDAR_H

#include "qpushbutton.h"
#include <QWidget>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>

namespace Ui {
class Calendar;
}

class Calendar : public QWidget
{
    Q_OBJECT

public:
    explicit Calendar(QWidget *parent = nullptr);
    ~Calendar();

private slots:
    void on_Previous_clicked();

    void on_Next_clicked();

private:
    Ui::Calendar *ui;
    void setDay(QPushButton* button);
    std::string getMonth(int monthNumber);
    int numberOfDays (int monthNumber, int year);
    int dayOfMonth(int day, int month, int year);
    void updateCalender();
    std::string dAndMonth = "  ", yearSt = "    ", tempId = "  ";
    int table[100][4];
    int counter = 0;
    int listArr[100];
};

#endif // CALENDAR_H
