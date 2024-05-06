#include "mytodo.h"
#include "ui_addtask.h"
#include "ui_mytodo.h"
#include "addtask.h"
#include "calendar.h"
#include "ui_calendar.h"
#include "task.h"




MyTodo::MyTodo(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MyTodo)
{
    ui->setupUi(this);
    ui->DoneButton->hide();
    ui->BackButton->hide();
    ui->label_2->hide();
    ui->Calendar->setIcon(QIcon(":/images/calenderICON.png"));
    ui->trashButton->setIcon(QIcon(":/images/trashICON.png"));
    ui->trashButton->setIconSize(QSize(89,89));
    ui->Calendar->setIconSize(QSize(125,125));

    updateTasks();

}

MyTodo::~MyTodo()
{
    delete ui;
}




void MyTodo::on_AddNew_clicked()
{

    AddTask *TaskTab = new AddTask;


    ui->tabWidget->insertTab(ui->tabWidget->count()
                             ,TaskTab,QIcon(QString("")),"Add Task");
    ui->tabWidget->setCurrentIndex(ui->tabWidget->count()-1);
    ui->tabWidget->setTabEnabled(0, false);
    ui->DoneButton->show();
    resize(440,430);
    TaskTab->on_lineEdit_returnPressed();


}



void MyTodo::on_DoneButton_clicked()
{
    ui->DoneButton->hide();
    ui->tabWidget->removeTab(ui->tabWidget->currentIndex());
    ui->tabWidget->setCurrentIndex(0);
    ui->tabWidget->setTabEnabled(0, true);
    resize(340,440);
    updateTasks();
}




void MyTodo::on_Calendar_clicked()
{
    ui->tabWidget->insertTab(ui->tabWidget->count()
                             ,new Calendar(),QIcon(QString("")),"Calendar");
    ui->tabWidget->setCurrentIndex(ui->tabWidget->count()-1);
    ui->tabWidget->setTabEnabled(0, false);
    ui->BackButton->show();
    resize(440,430);
}




void MyTodo::on_BackButton_clicked()
{
    ui->BackButton->hide();
    ui->tabWidget->removeTab(ui->tabWidget->currentIndex());
    ui->tabWidget->setCurrentIndex(0);
    ui->tabWidget->setTabEnabled(0, true);
    resize(340,440);
    updateTasks();
}


void MyTodo::updateTasks()
{
    ui->TasksList->clear();
    counter = 0;
    int nForT = 3, nForP = 175, nForID = 0, nForDis = 23, i = 0;
    int nForD = 177, nForM = 180, nForY = 183;
    QFile file("dataBase.txt");
    QFile blackList("blackList.txt");

    if(!blackList.open(QIODevice::ReadOnly | QFile::Text))
      {
        QMessageBox::warning(this, "Warning",
                             "Failed to open file :" + blackList.errorString());
        return;
      }

    QTextStream in2(&blackList);
        while (!in2.atEnd())
        {
           QString line = in2.readLine();
           listArr[i] = line.toInt();
           i++;
        }
        blackList.close();
//        if(listArr[8] != 0)
//        {
//            for(int i = 0; i < 10; i++)
//                listArr[i] = 0;
//            file.open(QIODevice::WriteOnly| QFile::Text);
//            file.close();
//            blackList.open(QIODevice::WriteOnly| QFile::Text);
//            blackList.close();
//        }


    if(!file.open(QIODevice::ReadOnly | QFile::Text))
     {
      QMessageBox::warning(this, "Warning",
                           "Failed to open file :" + file.errorString());
      return;
     }


      QTextStream in(&file);
      QString text = in.readAll();
      file.close();


      std::string a = text.toStdString();

      int j = 0;


      for(int k = 0; text.length() > nForP; k++)
      {
          tempId[0] = a[nForID];
          tempId[1] = a[nForID+1];
          TaskList[k].id = QString::fromStdString(tempId).toInt();


          for(i = nForT; i < nForT + 20; i++ )
          {

              TaskList[k].title[j] = a[i];
              j++;
          }
          j = 0;
          for(i = nForDis; i < nForDis + 150; i++ )
          {

              TaskList[k].discription[j] = a[i];
              j++;
          }


          dAndMonth[0] = a[nForD];
          dAndMonth[1] = a[nForD + 1];
          TaskList[k].day = QString::fromStdString(dAndMonth).toInt();

          dAndMonth[0] = a[nForM];
          dAndMonth[1] = a[nForM + 1];
          TaskList[k].month = QString::fromStdString(dAndMonth).toInt();

          j = 0;
          for(int i = nForY ; i < nForY + 4; i++)
          {
              yearSt[j] = a[i];
              j++;
          }
          TaskList[k].year = QString::fromStdString(yearSt).toInt();

          nForD += 189;
          nForM += 189;
          nForY += 189;

          TaskList[k].priority = a[nForP] - '0';
          nForT += 189;
          nForP += 189;
          nForDis += 189;
          nForID += 189;
          counter++;

      }


       for (i = 0; i < counter - 1; i++)
         {
          for (int j = 0; j < counter - i - 1; j++)
              if (TaskList[j].priority > TaskList[j + 1].priority)
                  std::swap(TaskList[j], TaskList[j + 1]);
         }


       for(i = 0; i < counter; i++)
         {
           int* found = std::find (listArr, std::end (listArr), TaskList[i].id);
           if(found == std::end (listArr))
           {

          QString newTitle = QString::fromStdString(TaskList[i].title);

            QFont _font;
            _font.setPointSize(8);
            QListWidgetItem *item = new QListWidgetItem(QString::number(TaskList[i].priority) +"          "+ newTitle );
            item->setFlags(item->flags() | Qt::ItemIsUserCheckable | Qt::ItemIsSelectable);
            item->setFont(_font);
            ui->TasksList->addItem(item);
            item->setCheckState(Qt::CheckState(0));
          }
       }

}


void MyTodo::on_TasksList_currentRowChanged(int currentRow)
{
    crRow = currentRow;
}


void MyTodo::on_trashButton_clicked()
{

    int j = 0;
    char a[20];
    if(crRow != -1)
    {
        QListWidgetItem *it = ui->TasksList->takeItem(crRow);
        std::string temp = it->text().toStdString(), newItem;

        //11 + 20
        for(int i = 11; i < 32; i++)
        {
            a[j] = temp[i];
            j++;
        }
        newItem = a;
        for(int i = 0; i < counter; i++)
        {
            if( newItem == TaskList[i].title)
            {
                QFile blackList("blackList.txt");

                if( !blackList.open(QIODevice::Append | QFile::Text))
                 {
                  QMessageBox::warning(this, "Warning",
                                       "Failed to open file :" + blackList.errorString());
                  return;
                 }
                QTextStream out(&blackList);
                out << QString::number(TaskList[i].id)+ "\n";

            }
        }
        delete it;
    }
    ui->TasksList->setCurrentRow(-1);
    updateTasks();

}

void MyTodo::on_TasksList_itemDoubleClicked(QListWidgetItem *item)
{
    int j = 0;
    char a[20];
    if(crRow != -1)
    {
        QListWidgetItem *it = ui->TasksList->takeItem(crRow);
        std::string temp = it->text().toStdString(), newItem;
        AddTask *TaskTab = new AddTask;


        ui->tabWidget->insertTab(ui->tabWidget->count()
                                 ,TaskTab,QIcon(QString("")),"Add Task");
        ui->tabWidget->setCurrentIndex(ui->tabWidget->count()-1);
        ui->tabWidget->setTabEnabled(0, false);
        ui->DoneButton->show();
        TaskTab->ui->save->setText("Save Edit");
        TaskTab->ui->save->setIcon(QIcon(":/images/penICON.png"));
         TaskTab->ui->save->setIconSize(QSize(35,35));
        resize(440,430);
        TaskTab->on_lineEdit_returnPressed();

        //11 + 20
        for(int i = 11; i < 32; i++)
        {
            a[j] = temp[i];
            j++;
        }
        newItem = a;
        for(int i = 0; i < counter; i++)
        {
            if( newItem == TaskList[i].title)
            {
                TaskTab->tempId = TaskList[i].id;
                TaskTab->ui->tagLabel->setText(QString::number(TaskList[i].id));
                TaskTab->ui->comboBox->setCurrentIndex(TaskList[i].priority -1);
                TaskTab->ui->lineEdit->setText(QString::fromStdString(TaskList[i].title).trimmed());
                TaskTab->ui->dateEdit->setDate(QDate(TaskList[i].year,TaskList[i].month,TaskList[i].day));
                TaskTab->ui->textEdit->setPlainText(QString::fromStdString(TaskList[i].discription).trimmed());
                TaskList[i].id = TaskTab->tempId;
            }
        }
        delete it;
    }


}

