#ifndef PLUSOPGAVER_H
#define PLUSOPGAVER_H

#include <QWidget>

namespace Ui {
class PlusOpgaver;
}

class PlusOpgaver : public QWidget
{
    Q_OBJECT

public:
    explicit PlusOpgaver(QWidget *parent = nullptr);
    ~PlusOpgaver();

    void setCore(int antal, int maxSum);

private:
    Ui::PlusOpgaver *ui;

    QString getPlusOpgave();

    int mPlusOpgaver = 20;
    int mPlusMaxSum = 50;

    int mSolved = 0;
    int mCorrect = 0;
};

#endif // PLUSOPGAVER_H
