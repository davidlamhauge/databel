#ifndef SOLVETASKS_H
#define SOLVETASKS_H

#include <QWidget>
#include <QElapsedTimer>

namespace Ui {
class SolveTasks;
}

class SolveTasks : public QWidget
{
    Q_OBJECT

public:
    explicit SolveTasks(int type, int antal, int max, bool negatives = false, QWidget *parent = nullptr);
    ~SolveTasks();

    bool eventFilter(QObject* obj, QEvent* e);

private:
    Ui::SolveTasks *ui;

    void restartTasks();

    void setTasks();
    QString getTasks();
    void checkTasks();
    void solveTask();
    QList<int> getDivisors(int num);

    int m1 = 0;
    int m2 = 0;

    int mResult = 0;
    int mSolved = 0;
    int mCorrect = 0;

    int mTaskType;
    int mAntal;
    int mMax;
    bool mNegativeResult = false;

    QElapsedTimer timer;

};

#endif // SOLVETASKS_H
