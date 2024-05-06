#ifndef MYTODO_H
#define MYTODO_H
#include "qlistwidget.h"
#include "task.h"
#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MyTodo; }
QT_END_NAMESPACE

class MyTodo : public QMainWindow
{
    Q_OBJECT

public:
    MyTodo(QWidget *parent = nullptr);
    ~MyTodo();
    Ui::MyTodo *ui;


private slots:
    void on_AddNew_clicked();

    void on_DoneButton_clicked();

    void on_Calendar_clicked();

    void on_BackButton_clicked();

    void on_TasksList_currentRowChanged(int currentRow);

    void on_trashButton_clicked();

    void on_TasksList_itemDoubleClicked(QListWidgetItem *item);

private:
    std::string dAndMonth = "  ", yearSt = "    ", tempId = "  ";
    void updateTasks();
    int crRow = -1;
    int counter = 0;
    task TaskList[100];
    int listArr[99] = {0};
};
#endif // MYTODO_H
