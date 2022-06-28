#include "plusopgaver.h"
#include "ui_plusopgaver.h"

#include <QDebug>
#include <QRandomGenerator>

PlusOpgaver::PlusOpgaver(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlusOpgaver)
{
    ui->setupUi(this);

    connect(ui->btnExit, &QPushButton::clicked, this, &PlusOpgaver::close);
    QString opg = getPlusOpgave();
    QStringList list = opg.split(",");
    int a = list.first().toInt();
    int b = list.last().toInt();
    ui->labTal1->setText(list.first());
    ui->labTal2->setText(list.last());
}

PlusOpgaver::~PlusOpgaver()
{
    delete ui;
}

void PlusOpgaver::setCore(int antal, int maxSum)
{
    mPlusOpgaver = antal;
    mPlusMaxSum = maxSum;

    ui->labIalt->setText(QString::number(mPlusOpgaver));
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
    return QString(QString::number(a)+"," + QString::number(b));
}
