#include "plusopgaver.h"
#include "ui_plusopgaver.h"

#include <QDebug>
#include <QRandomGenerator>

PlusOpgaver::PlusOpgaver(int antal, int maxSum, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlusOpgaver)
{
    ui->setupUi(this);
    mPlusOpgaver = antal;
    mPlusMaxSum = maxSum;

    ui->labIalt->setText(QString::number(mPlusOpgaver));

    connect(ui->btnExit, &QPushButton::clicked, this, &PlusOpgaver::close);
    connect(ui->btnSolved, &QPushButton::clicked, this, &PlusOpgaver::checkPlusOpgave);

    timer.start();
    setPlusOpgave();
}

PlusOpgaver::~PlusOpgaver()
{
    delete ui;
}

void PlusOpgaver::setPlusOpgave()
{
    ui->labRigtige->setText(QString::number(mCorrect));
    ui->labSolved->setText(QString::number(mSolved));
    ui->labMulige->setText(QString::number(mSolved));
    if (mSolved < mPlusOpgaver)
        solvePlus();
    else
    {
        ui->leResult->setEnabled(false);
        ui->btnSolved->setEnabled(false);
        int elapsed = timer.elapsed() / 1000;
        ui->labElapsed->setText(QString::number(elapsed) + " sek.");
    }
}

QString PlusOpgaver::getPlusOpgave()
{
    int tal = static_cast<int>(mPlusMaxSum * 0.6);
    int a, b;
    do
    {
        a = QRandomGenerator::global()->bounded(tal);
        b = QRandomGenerator::global()->bounded(tal);
    } while (a + b > mPlusMaxSum);
    return QString(QString::number(a) + "," + QString::number(b));
}

void PlusOpgaver::checkPlusOpgave()
{
    int guess = ui->leResult->text().toInt();
    if (guess == mResult)
    {
        mCorrect++;
    }
    mSolved++;
    setPlusOpgave();
}

void PlusOpgaver::solvePlus()
{
    QString opg = getPlusOpgave();
    QStringList list = opg.split(",");
    m1 = list.first().toInt();
    m2 = list.last().toInt();
    mResult = m1 + m2;
    ui->labTal1->setText(list.first());
    ui->labTal2->setText(list.last());
    ui->leResult->clear();
    ui->leResult->setFocus();
}
