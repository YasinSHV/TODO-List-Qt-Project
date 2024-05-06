#include "calendar.h"
#include "qdatetime.h"
#include "ui_calendar.h"

//public vars
QDate date = QDate::currentDate();
int year = date.year();
int month = date.month();

Calendar::Calendar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Calendar)
{
    ui->setupUi(this);
    updateCalender();

}

void Calendar::setDay(QPushButton* button)
{
    button->setText("g");
}

Calendar::~Calendar()
{
    delete ui;
}



std::string Calendar::getMonth(int monthNumber)
{
    const std::string months[] = {"January", "February", "March",
                       "April", "May", "June",
                       "July", "August", "September",
                       "October", "November", "December"
                      };

    return (months[monthNumber]);
}

int Calendar::numberOfDays (int monthNumber, int year)
{
    if (monthNumber == 0 || (monthNumber % 2 == 0 && monthNumber <= 6))
        return (31);
    if((monthNumber != 1 && monthNumber % 2 == 1) && monthNumber <= 6)
        return (30);
    if (monthNumber == 0 || (monthNumber % 2 == 0 && monthNumber > 6))
        return (30);
    if((monthNumber != 1 && monthNumber % 2 == 1) && monthNumber > 6)
        return (31);

    if (monthNumber == 1)
    {
        // If is leap then
        // 29 days
        if (year % 400 == 0 ||
                (year % 4 == 0 && year % 100 != 0))
            return (29);
        else
            return (28);
    }
}

int Calendar::dayOfMonth(int day, int month, int year)
{

    static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1,
                       4, 6, 2, 4 };
    year -= month < 3;
    return ( year + year/4 - year/100 +
             year/400 + t[month-1] + day) % 7;
}

void Calendar::updateCalender()
{
    counter = 0;
    int nForD = 177, nForM = 180, nForY = 183, nForID = 0, i = 0;
    QFile file("dataBase.txt");
    QFile blackList("blackList.txt");

    if(!file.open(QIODevice::ReadOnly | QFile::Text) || !blackList.open(QIODevice::ReadOnly | QFile::Text))
     {
      QMessageBox::warning(this, "Warning",
                           "Failed to open file :" + file.errorString());
      return;
     }
      QTextStream in(&file);
      QString text = in.readAll();
      file.close();

      QTextStream in2(&blackList);
      while (!in2.atEnd())
      {
         QString line = in2.readLine();
         listArr[i] = line.toInt();
         i++;
      }
      blackList.close();

      std::string a = text.toStdString();

      int j = 0;
      for(int k = 0; text.length() > nForD; k++)
      {
          QString tempLine;
          tempId[0] = a[nForID];
          tempId[1] = a[nForID+1];
          table[k][0] = QString::fromStdString(tempId).toInt();

          dAndMonth[0] = a[nForD];
          dAndMonth[1] = a[nForD + 1];
          table[k][1] = QString::fromStdString(dAndMonth).toInt();

          dAndMonth[0] = a[nForM];
          dAndMonth[1] = a[nForM + 1];
          table[k][2] = QString::fromStdString(dAndMonth).toInt();
          int j = 0;
          for(int i = nForY ; i < nForY + 4; i++)
          {
              yearSt[j] = a[i];
              j++;
          }
          table[k][3] = QString::fromStdString(yearSt).toInt();

          nForD += 189;
          nForM += 189;
          nForY += 189;
          nForID += 189;
          counter++;

      }






    QString monthToString = QString::fromStdString(getMonth(month));

    ui->MonthLabel->setText(monthToString);
    ui->YearLabel->setText(QString::number(year));

    QPushButton *dayButtons[38];
    for(int i= 1; i <= 38; i++)
    {
        QString butName = "Button" + QString::number(i);
        dayButtons[i-1] = Calendar::findChild<QPushButton *>(butName);
        dayButtons[i-1]->setStyleSheet("font : bold");
        dayButtons[i-1]->show();
    }

    for(int i =0 ; i < dayOfMonth(1,month,year) ; i++)
    {
        dayButtons[i]->setText(" ");
    }

    for(int i = 1 ; i <= numberOfDays(month, year); i++)
    {
        dayButtons[(i+ dayOfMonth(1,month,year)) -1]->setText(QString::number(i));


        if(i + 1 > numberOfDays(month, year))
        {
            for(int j = (i+ dayOfMonth(1,month,year)); j < 38; j++)
            {
                dayButtons[j]->hide();
            }
        }
    }

    for(int i =0; i < counter; i++)
    {
        int* found = std::find (listArr, std::end (listArr), table[i][0]);
        if((table[i][2] == month && table[i][3] == year )&&( found == std::end (listArr)))
        dayButtons[table[i][1] + (dayOfMonth(1,table[i][2],table[i][3])) - 1]->setStyleSheet("background-color: yellow; font : bold");
    }
}


void Calendar::on_Previous_clicked()
{
    month--;
    if(month < 0){
        month = 11;
    year--;}

    updateCalender();
}


void Calendar::on_Next_clicked()
{
    month++;
    if(month > 11){
        month = 1;year++;}
    updateCalender();
}

