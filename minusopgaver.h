#ifndef MINUSOPGAVER_H
#define MINUSOPGAVER_H

#include <QWidget>
#include <QElapsedTimer>

namespace Ui {
class MinusOpgaver;
}

class MinusOpgaver : public QWidget
{
    Q_OBJECT

public:
    explicit MinusOpgaver(int antal, int maxTal, bool negativeResult, QWidget *parent = nullptr);
    ~MinusOpgaver();

    bool eventFilter(QObject* obj, QEvent* e);

private:
    Ui::MinusOpgaver *ui;

    void restartMinus();

    void setMinusOpgave();
    QString getMinusOpgave();
    void checkMinusOpgave();
    void solveMinus();

    int mOpgaver;
    int mMaxTal;
    bool mNegativDiff = false;

    int m1 = 0;
    int m2 = 0;
    bool mCont = false;

    int mResult = 0;
    int mSolved = 0;
    int mCorrect = 0;

    QElapsedTimer timer;
};

#endif // MINUSOPGAVER_H
