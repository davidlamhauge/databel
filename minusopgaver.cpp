#include "minusopgaver.h"
#include "ui_minusopgaver.h"

#include <QDebug>
#include <QRandomGenerator>
#include <QKeyEvent>

MinusOpgaver::MinusOpgaver(int antal, int maxTal, bool negativeResult, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MinusOpgaver)
{
    ui->setupUi(this);

    ui->leResult->installEventFilter(this);

    mOpgaver = antal;
    mMaxTal = maxTal;
    mNegativDiff = negativeResult;

    ui->labAntal->setText(QString::number(mOpgaver));
    ui->labElapsed->setText("");

    connect(ui->btnExit, &QPushButton::clicked, this, &MinusOpgaver::close);
    connect(ui->btnOnceMore, &QPushButton::clicked, this, &MinusOpgaver::restartMinus);

    timer.start();
    setMinusOpgave();
}

MinusOpgaver::~MinusOpgaver()
{
    delete ui;
}

bool MinusOpgaver::eventFilter(QObject *obj, QEvent *e)
{
    if (obj == ui->leResult)
    {
        if (e->type() == QEvent::KeyPress)
        {
            QKeyEvent *k = static_cast<QKeyEvent*>(e);
            if (k->key() == Qt::Key_Return)
            {
                checkMinusOpgave();
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

void MinusOpgaver::restartMinus()
{
    mResult = 0;
    mSolved = 0;
    mCorrect = 0;

    ui->leResult->setEnabled(true);
    ui->labElapsed->setText("");

    timer.restart();
    setMinusOpgave();
}

void MinusOpgaver::setMinusOpgave()
{
    ui->labRigtige->setText(QString::number(mCorrect));
    ui->labSolved->setText(QString::number(mSolved));
    ui->labMulige->setText(QString::number(mSolved));
    if (mSolved < mOpgaver)
        solveMinus();
    else
    {
        ui->leResult->setEnabled(false);
        float elapsed = timer.elapsed() / 1000.0;
        ui->labElapsed->setText(QString::number(elapsed) + " sek.");
    }
}

QString MinusOpgaver::getMinusOpgave()
{
    int a, b;
    a = QRandomGenerator::global()->bounded(2, mMaxTal);
    b = QRandomGenerator::global()->bounded(2, mMaxTal);
    if (!mNegativDiff && a < b)
    {
        int tmp = a;
        a = b;
        b = tmp;
    }
    return QString(QString::number(a) + "," + QString::number(b));
}

void MinusOpgaver::checkMinusOpgave()
{
    int guess = ui->leResult->text().toInt();
    if (guess == mResult)
    {
        mCorrect++;
    }
    mSolved++;
    setMinusOpgave();
}

void MinusOpgaver::solveMinus()
{
    QString opg = getMinusOpgave();
    QStringList list = opg.split(",");
    m1 = list.first().toInt();
    m2 = list.last().toInt();
    mResult = m1 - m2;
    ui->labFirst->setText(list.first());
    ui->labSecond->setText(list.last());
    ui->leResult->clear();
    ui->leResult->setFocus();
}
