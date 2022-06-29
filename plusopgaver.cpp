#include "plusopgaver.h"
#include "ui_plusopgaver.h"

#include <QDebug>
#include <QRandomGenerator>
#include <QKeyEvent>

PlusOpgaver::PlusOpgaver(int antal, int maxSum, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlusOpgaver)
{
    ui->setupUi(this);

    ui->leResult->installEventFilter(this);

    mOpgaver = antal;
    mMaxSum = maxSum;

    ui->labIalt->setText(QString::number(mOpgaver));

    connect(ui->btnExit, &QPushButton::clicked, this, &PlusOpgaver::close);
    connect(ui->btnOnceMore, &QPushButton::clicked, this, &PlusOpgaver::restartPlus);

    timer.start();
    setPlusOpgave();
}

PlusOpgaver::~PlusOpgaver()
{
    delete ui;
}

bool PlusOpgaver::eventFilter(QObject *obj, QEvent *e)
{
    if (obj == ui->leResult)
    {
        if (e->type() == QEvent::KeyPress)
        {
            QKeyEvent *k = static_cast<QKeyEvent*>(e);
            if (k->key() == Qt::Key_Return)
            {
                checkPlusOpgave();
                return true;
            }
            else
            {
                return QWidget::eventFilter(obj, e);
            }
        }
    }
    return QWidget::eventFilter(obj, e);
}

void PlusOpgaver::restartPlus()
{
    mResult = 0;
    mSolved = 0;
    mCorrect = 0;

    ui->leResult->setEnabled(true);
    ui->labElapsed->setText("");

    timer.restart();
    setPlusOpgave();
}

void PlusOpgaver::setPlusOpgave()
{
    ui->labRigtige->setText(QString::number(mCorrect));
    ui->labSolved->setText(QString::number(mSolved));
    ui->labMulige->setText(QString::number(mSolved));
    if (mSolved < mOpgaver)
        solvePlus();
    else
    {
        ui->leResult->setEnabled(false);
        float elapsed = timer.elapsed() / 1000.0;
        ui->labElapsed->setText(QString::number(elapsed) + " sek.");
    }
}

QString PlusOpgaver::getPlusOpgave()
{
    int tal = static_cast<int>(mMaxSum * 0.6);
    int a, b;
    do
    {
        a = QRandomGenerator::global()->bounded(2, tal);
        b = QRandomGenerator::global()->bounded(2, tal);
    } while (a + b > mMaxSum);
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
