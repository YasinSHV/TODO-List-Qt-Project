#include "addtask.h"
#include "ui_addtask.h"
#include<cstdio>
#include<string>

//public vars
char ch;
int count = 0;

AddTask::AddTask(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddTask)
{
    QDate date = QDate::currentDate();
    ui->setupUi(this);
    for(int i = 1; i <= 9; i++)
    {
      QString a = QString::number(i);
      ui->comboBox->addItem(a);
    }
    ui->save->setIcon(QIcon(":/images/saveICON.png"));
      ui->save->setIconSize(QSize(35,35));

    ui->dateEdit->setDate(date);
}

AddTask::~AddTask()
{
    delete ui;
}

void AddTask::on_lineEdit_returnPressed()
{
    ui->textEdit->append(ui->lineEdit->text());
    ui->lineEdit->clear();
}


void AddTask::insertTask()
{
    count = 0;

       QFile file("dataBase.txt");
       if(!file.open(QFile::Append | QFile::Text))
       {
           QMessageBox::warning(this, "Warning",
                                   "Failed to save file :" + file.errorString());
           return;
       }

       //Ezafi Begin
       FILE *file2 = fopen("dataBase.txt", "r");
            while ((ch=getc(file2))!=EOF)
            {
             if (ch=='^')
                    count++;}
       //Ezafi End

       QTextStream out(&file);
       while(ui->lineEdit->text().length() < 20)
       {
           ui->lineEdit->insert(QString(" "));
       }while(ui->textEdit->toPlainText().length() < 150)
       {
           ui->textEdit->insertPlainText(" ");
       }
       QString _day = QString::number(ui->dateEdit->date().day());
       QString _month = QString::number(ui->dateEdit->date().month());
       if(_day.length() < 2)
           _day.append(QString(" "));
       if(_month.length() < 2)
           _month.append(QString(" "));


       QString id  = QString::number(count+1);

       if(id.length() == 1)
           id.append(" ");

       QString text = id +'\n'+ QString(ui->lineEdit->text()) + '\n'
               + QString(ui->textEdit->toPlainText()) +'\n'+ QString(ui->comboBox->currentText()) +'\n'
               + _day + '\n' + _month
               + '\n' + QString::number(ui->dateEdit->date().year()) +'^';
       out << text + '\n';
       file.close();


       QString textTemp = QString(ui->textEdit->toPlainText().trimmed());
       QString textTemp2 = QString(ui->lineEdit->text().trimmed());
       ui->textEdit->setPlainText(textTemp);
       ui->lineEdit->setText(textTemp2);

}


void AddTask::on_save_clicked()
{
    if(ui->tagLabel->text().toInt() != 0)
    {
        QFile blackList("blackList.txt");

        if( !blackList.open(QIODevice::Append | QFile::Text))
         {
          QMessageBox::warning(this, "Warning",
                               "Failed to open file :" + blackList.errorString());
          return;
         }
        QTextStream out(&blackList);
        out << QString::number(tempId)+ "\n";
        tempId++;
    }
    insertTask();
    ui->save->setEnabled(false);



}


void AddTask::on_lineEdit_textChanged(const QString &arg1)
{
    ui->counter1->setText(QString::number(ui->lineEdit->text().length()));
    if(ui->textEdit->toPlainText().length() > 150 || ui->lineEdit->text().length() > 20
            || ui->textEdit->toPlainText().length() == 0 || ui->lineEdit->text().length() == 0)
    {
        ui->save->setEnabled(false);
        if(ui->lineEdit->text().length() > 20){
        ui->counter1->setStyleSheet("color: red");}
    }else
    {
        ui->counter1->setStyleSheet("color: black");
        ui->save->setEnabled(true);
    }
}


void AddTask::on_textEdit_textChanged()
{
    ui->counter2->setText(QString::number(ui->textEdit->toPlainText().length()));
    if(ui->textEdit->toPlainText().length() > 150 || ui->lineEdit->text().length() > 20
            || ui->lineEdit->text().length() == 0 || ui->textEdit->toPlainText().length() == 0)
    {
        ui->save->setEnabled(false);
        if(ui->textEdit->toPlainText().length() > 150){
        ui->counter2->setStyleSheet("color: red");}
    }else
     {
       ui->counter2->setStyleSheet("color: black");
       ui->save->setEnabled(true);
     }
}

