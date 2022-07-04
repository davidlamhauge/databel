#include "tabeltrainer.h"
#include "ui_tabeltrainer.h"

#include <QSettings>
#include <QKeyEvent>
#include <QRandomGenerator>
#include <QDebug>

TabelTrainer::TabelTrainer(int type, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TabelTrainer)
{
    ui->setupUi(this);

    // initialize settings
    QSettings settings("TeamLamhauge", "daTabel");
    move(settings.value("winPos", pos()).toPoint());
    mShowTimer = settings.value("timer", 0).toInt();

    mTaskType = type;

    switch (mTaskType) {
    case 5: ui->labSign->setText("x"); setWindowTitle(tr("Gangetabel")); break;
    case 6: ui->labSign->setText("+"); setWindowTitle(tr("Plustabel")); break;
    default: ui->labSign->setText("x"); setWindowTitle(tr("Gangetabel")); break;
    }

    ui->leResult->installEventFilter(this);

    connect(ui->btnExit, &QPushButton::clicked, this, &TabelTrainer::close);
    connect(ui->btnOnceMore, &QPushButton::clicked, this, &TabelTrainer::restartTrainer);

    numbers.clear();
    for (int i = 0; i < 100; i++)
    {
        numbers.append(i);
    }

    for (int i = 0 ;i < 200; i++)
    {
        int tmp = QRandomGenerator::global()->bounded(1, 100);
        numbers.move(0, tmp);
    }

    if (mShowTimer > 0)
        timer.start();
    if (mShowTimer > 1)
        single.singleShot(1000, this, &TabelTrainer::updateTimerLabel);

    setTrainer();
}

TabelTrainer::~TabelTrainer()
{
    delete ui;
}

bool TabelTrainer::eventFilter(QObject *obj, QEvent *e)
{
    if (obj == ui->leResult)
    {
        if (e->type() == QEvent::KeyPress)
        {
            QKeyEvent *k = static_cast<QKeyEvent*>(e);
            if (k->key() == Qt::Key_Return)
            {
                checkTrainer();
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

void TabelTrainer::restartTrainer()
{
    mResult = 0;
    mSolved = 0;
    mCorrect = 0;

    ui->leResult->setEnabled(true);
    ui->labElapsed->setText("");

    if (mShowTimer > 0)
        timer.start();
    if (mShowTimer > 1)
        single.singleShot(1000, this, &TabelTrainer::updateTimerLabel);
    setTrainer();
}

void TabelTrainer::setTrainer()
{
    ui->labSolved->setText(QString::number(mSolved));
    ui->labAntal->setText(QString::number(100));
    if (mSolved < mAntal)
        solveTrainer();
    else
    {
        ui->leResult->setEnabled(false);
        if (mShowTimer > 0)
        {
            float elapsed = timer.elapsed() / 1000.0;
            ui->labElapsed->setText(QString::number(elapsed) + " sek.");
            timer.invalidate();
        }
    }
}

QString TabelTrainer::getTrainer()
{
    int tmp = numbers.takeFirst();
    mRow = tmp / 10;
    mCol = tmp % 10;

    return QString(QString::number(mRow + 1) + "," + QString::number(mCol + 1));
}

void TabelTrainer::checkTrainer()
{
    int guess = ui->leResult->text().toInt();
    QTableWidgetItem* item = new QTableWidgetItem(QString::number(guess));
    ui->tableWidget->setItem(mRow, mCol, item);
    if (guess == mResult)
    {
        mCorrect++;
        ui->tableWidget->item(mRow, mCol)->setBackground(mGreen);
    }
    else
    {
        ui->tableWidget->item(mRow, mCol)->setBackground(mRosa);
    }
    mSolved++;
    setTrainer();
}

void TabelTrainer::solveTrainer()
{
    QString opg = getTrainer();
    QStringList list = opg.split(",");
    m1 = list.first().toInt();
    m2 = list.last().toInt();

    switch (mTaskType) {
    case 5: mResult = m1 * m2; break;
    case 6: mResult = m1 + m2; break;
    default: mResult = m1 * m2; break;
    }

    ui->labFirst->setText(list.first());
    ui->labSecond->setText(list.last());
    ui->leResult->clear();
    ui->leResult->setFocus();
}

void TabelTrainer::updateTimerLabel()
{
    if (timer.isValid())
    {
        int elapsed = timer.elapsed() / 1000;
        ui->labElapsed->setText(QString::number(elapsed) + tr(" sek."));
        single.singleShot(1000, this, &TabelTrainer::updateTimerLabel);
    }
}

