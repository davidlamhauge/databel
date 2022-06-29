#ifndef PLUSOPGAVER_H
#define PLUSOPGAVER_H

#include <QWidget>
#include <QElapsedTimer>

namespace Ui {
class PlusOpgaver;
}

class PlusOpgaver : public QWidget
{
    Q_OBJECT

public:
    explicit PlusOpgaver(int antal, int maxSum, QWidget *parent = nullptr);
    ~PlusOpgaver();

    bool eventFilter(QObject* obj, QEvent* e);

private:
    Ui::PlusOpgaver *ui;

    void restartPLus();

    void setPlusOpgave();
    QString getPlusOpgave();
    void checkPlusOpgave();
    void solvePlus();

    int mPlusOpgaver;
    int mPlusMaxSum;

    int m1 = 0;
    int m2 = 0;
    bool mCont = false;

    int mResult = 0;
    int mSolved = 0;
    int mCorrect = 0;

    QElapsedTimer timer;
};

#endif // PLUSOPGAVER_H
