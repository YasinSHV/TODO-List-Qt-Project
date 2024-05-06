#ifndef ADDTASK_H
#define ADDTASK_H
#include "mytodo.h"
#include "ui_mytodo.h"
#include <QWidget>

namespace Ui {
class AddTask;
}

class AddTask : public QWidget
{
    Q_OBJECT

public:
    explicit AddTask(QWidget *parent = nullptr);
    ~AddTask();
    void insertTask();
    Ui::AddTask *ui;
    int tempId = 0;
public slots:
    void on_lineEdit_returnPressed();

private slots:

    void on_save_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_textEdit_textChanged();

private:

};

#endif // ADDTASK_H
