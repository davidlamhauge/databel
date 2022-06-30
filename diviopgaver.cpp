#include "diviopgaver.h"
#include "ui_diviopgaver.h"

#include <QDebug>
#include <QRandomGenerator>
#include <QKeyEvent>

DiviOpgaver::DiviOpgaver(int antal, int maxDividend, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DiviOpgaver)
{
    ui->setupUi(this);

    ui->leResult->installEventFilter(this);
    ui->labElapsed->setText("");

    mOpgaver = antal;
    mMaxDividend = maxDividend;

    ui->labAntal->setText(QString::number(mOpgaver));

    connect(ui->btnExit, &QPushButton::clicked, this, &DiviOpgaver::close);
    connect(ui->btnOnceMore, &QPushButton::clicked, this, &DiviOpgaver::restartDivi);

    timer.start();
    setDiviOpgave();

}

DiviOpgaver::~DiviOpgaver()
{
    delete ui;
}

bool DiviOpgaver::eventFilter(QObject *obj, QEvent *e)
{
    if (obj == ui->leResult)
    {
        if (e->type() == QEvent::KeyPress)
        {
            QKeyEvent *k = static_cast<QKeyEvent*>(e);
            if (k->key() == Qt::Key_Return)
            {
                checkDiviOpgave();
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

void DiviOpgaver::restartDivi()
{
    mResult = 0;
    mSolved = 0;
    mCorrect = 0;

    ui->leResult->setEnabled(true);
    ui->labElapsed->setText("");

    timer.restart();
    setDiviOpgave();
}

void DiviOpgaver::setDiviOpgave()
{
    ui->labRigtige->setText(QString::number(mCorrect));
    ui->labSolved->setText(QString::number(mSolved));
    ui->labMulige->setText(QString::number(mSolved));
    if (mSolved < mOpgaver)
        solveDivi();
    else
    {
        ui->leResult->setEnabled(false);
        float elapsed = timer.elapsed() / 1000.0;
        ui->labElapsed->setText(QString::number(elapsed) + " sek.");
    }
}

QString DiviOpgaver::getDiviOpgave()
{
    QList<int> divisorer;
    int tal;
    do
    {
        tal = QRandomGenerator::global()->bounded(10, mMaxDividend);
        divisorer = getDivisors(tal);
    } while (divisorer.size() < 3);
    int antal = divisorer.count();
    int pos = QRandomGenerator::global()->bounded(1, antal - 1);
    return QString(QString::number(tal) + "," + QString::number(divisorer.at(pos)));
}

QList<int> DiviOpgaver::getDivisors(int num)
{
    QList<int> divisors;
    for (int i = 1; i <= num; i++)
        if (num % i == 0)
            divisors.append(i);
    return divisors;
}

void DiviOpgaver::checkDiviOpgave()
{
    int guess = ui->leResult->text().toInt();
    if (guess == mResult)
    {
        mCorrect++;
    }
    mSolved++;
    setDiviOpgave();
}

void DiviOpgaver::solveDivi()
{
    QString opg = getDiviOpgave();
    QStringList list = opg.split(",");
    m1 = list.first().toInt();
    m2 = list.last().toInt();
    mResult = m1 / m2;
    ui->labFirst->setText(list.first());
    ui->labSecond->setText(list.last());
    ui->leResult->clear();
    ui->leResult->setFocus();
}
