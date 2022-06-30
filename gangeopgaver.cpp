#include "gangeopgaver.h"
#include "ui_gangeopgaver.h"

#include <QDebug>
#include <QRandomGenerator>
#include <QKeyEvent>

GangeOpgaver::GangeOpgaver(int antal, int maxTal, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GangeOpgaver)
{
    ui->setupUi(this);

    ui->leResult->installEventFilter(this);
    ui->labElapsed->setText("");

    mOpgaver = antal;
    mMaxTal = maxTal;

    ui->labAntal->setText(QString::number(mOpgaver));

    connect(ui->btnExit, &QPushButton::clicked, this, &GangeOpgaver::close);
    connect(ui->btnOnceMore, &QPushButton::clicked, this, &GangeOpgaver::restartGange);

    timer.start();
    setGangeOpgave();
}

GangeOpgaver::~GangeOpgaver()
{
    delete ui;
}

bool GangeOpgaver::eventFilter(QObject *obj, QEvent *e)
{
    if (obj == ui->leResult)
    {
        if (e->type() == QEvent::KeyPress)
        {
            QKeyEvent *k = static_cast<QKeyEvent*>(e);
            if (k->key() == Qt::Key_Return)
            {
                checkGangeOpgave();
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

void GangeOpgaver::restartGange()
{
    mResult = 0;
    mSolved = 0;
    mCorrect = 0;

    ui->leResult->setEnabled(true);
    ui->labElapsed->setText("");

    timer.restart();
    setGangeOpgave();
}

void GangeOpgaver::setGangeOpgave()
{
    ui->labRigtige->setText(QString::number(mCorrect));
    ui->labSolved->setText(QString::number(mSolved));
    ui->labMulige->setText(QString::number(mSolved));
    if (mSolved < mOpgaver)
        solveGange();
    else
    {
        ui->leResult->setEnabled(false);
        float elapsed = timer.elapsed() / 1000.0;
        ui->labElapsed->setText(QString::number(elapsed) + " sek.");
    }
}

QString GangeOpgaver::getGangeOpgave()
{
    int tal1 = QRandomGenerator::global()->bounded(2, mMaxTal);
    int tal2 = QRandomGenerator::global()->bounded(2, mMaxTal);
    qDebug() << tal1 << " * " << tal2 << " maxtal: "  << mMaxTal;
    return QString(QString::number(tal1) + "," + QString::number(tal2));
}

void GangeOpgaver::checkGangeOpgave()
{
    int guess = ui->leResult->text().toInt();
    if (guess == mResult)
    {
        mCorrect++;
    }
    mSolved++;
    setGangeOpgave();
}

void GangeOpgaver::solveGange()
{
    QString opg = getGangeOpgave();
    QStringList list = opg.split(",");
    m1 = list.first().toInt();
    m2 = list.last().toInt();
    mResult = m1 * m2;
    ui->labFirst->setText(list.first());
    ui->labSecond->setText(list.last());
    ui->leResult->clear();
    ui->leResult->setFocus();
}
