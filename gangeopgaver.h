#ifndef GANGEOPGAVER_H
#define GANGEOPGAVER_H

#include <QWidget>
#include <QElapsedTimer>

namespace Ui {
class GangeOpgaver;
}

class GangeOpgaver : public QWidget
{
    Q_OBJECT

public:
    explicit GangeOpgaver(int antal, int maxTal, QWidget *parent = nullptr);
    ~GangeOpgaver();

    bool eventFilter(QObject* obj, QEvent* e);

private:
    Ui::GangeOpgaver *ui;

    void restartGange();

    void setGangeOpgave();
    QString getGangeOpgave();
    void checkGangeOpgave();
    void solveGange();

    int mOpgaver;
    int mMaxTal;

    int m1 = 0;
    int m2 = 0;

    int mResult = 0;
    int mSolved = 0;
    int mCorrect = 0;

    QElapsedTimer timer;

};

#endif // GANGEOPGAVER_H
