#ifndef TASK_H
#define TASK_H
#include <QWidget>

class task
{
public:
    task();
    std::string title = "                    " , discription = "                                                            "
                                                             "                                                                                "
                                                              "          ";
    std::string stringID = "  ";
    int priority, id;
    int day, month, year;
};

#endif // TASK_H
