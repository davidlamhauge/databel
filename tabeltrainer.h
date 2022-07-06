#ifndef TABELTRAINER_H
#define TABELTRAINER_H

#include <QDialog>
#include <QElapsedTimer>
#include <QTimer>

namespace Ui {
class TabelTrainer;
}

class TabelTrainer : public QDialog
{
    Q_OBJECT

public:
    explicit TabelTrainer(int type, QWidget *parent = nullptr);
    ~TabelTrainer();

    bool eventFilter(QObject* obj, QEvent* e);

private:
    Ui::TabelTrainer *ui;

    void restartTrainer();

    void setTrainer();
    QString getTrainer();
    void checkTrainer();
    void solveTrainer();
    void updateTimerLabel();
    void updateGrid(int state);

    int m1 = 0;
    int m2 = 0;
    int mRow = 0;
    int mCol = 0;

    int mAntal = 100;
    int mResult = 0;
    int mSolved = 0;
    int mCorrect = 0;

    int mTaskType;
    int mShowTimer = 0;

    void setShowColors(bool b) { mShowColors = b; }
    bool mShowColors = false;

    QList<int> numbers;
    QList<QColor> mColors;

    QElapsedTimer timer;
    QTimer single;

    const QColor mPurple = QColor(255, 123, 240);
    const QColor mGreen = QColor(123, 255, 123);
    const QColor mBg = QColor(240, 240, 240);
};

#endif // TABELTRAINER_H
