#ifndef DIVIOPGAVER_H
#define DIVIOPGAVER_H

#include <QWidget>
#include <QElapsedTimer>

namespace Ui {
class DiviOpgaver;
}

class DiviOpgaver : public QWidget
{
    Q_OBJECT

public:
    explicit DiviOpgaver(int antal, int maxDividend, QWidget *parent = nullptr);
    ~DiviOpgaver();

    bool eventFilter(QObject* obj, QEvent* e);

private:
    Ui::DiviOpgaver *ui;

    void restartDivi();

    void setDiviOpgave();
    QString getDiviOpgave();
    QList<int> getDivisors(int num);
    void checkDiviOpgave();
    void solveDivi();

    int mOpgaver;
    int mMaxDividend;

    int m1 = 0;
    int m2 = 0;
    bool mCont = false;

    int mResult = 0;
    int mSolved = 0;
    int mCorrect = 0;

    QElapsedTimer timer;

};

#endif // DIVIOPGAVER_H
