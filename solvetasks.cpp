#include "solvetasks.h"
#include "ui_solvetasks.h"

#include <QKeyEvent>
#include <QRandomGenerator>
#include <QSettings>

SolveTasks::SolveTasks(int type, int antal, int max, bool negatives, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SolveTasks)
{
    ui->setupUi(this);

    // initialize settings
    QSettings settings("TeamLamhauge", "daTabel");
    move(settings.value("winPos", pos()).toPoint());
    mShowTimer = settings.value("timer", 0).toInt();

    mTaskType = type;
    mAntal = antal;
    mMax = max;
    mNegativeResult = negatives;

    switch (mTaskType) {
    case 1: ui->labSign->setText("+"); setWindowTitle(tr("Plus")); break;
    case 2: ui->labSign->setText("-"); setWindowTitle(tr("Minus")); break;
    case 3: ui->labSign->setText("x"); setWindowTitle(tr("Gange")); break;
    case 4: ui->labSign->setText(":"); setWindowTitle(tr("Division")); break;
    default: ui->labSign->setText("+"); setWindowTitle(tr("Plus")); break;
    }

    ui->leResult->installEventFilter(this);

    ui->labAntal->setText(QString::number(mAntal));

    connect(ui->btnExit, &QPushButton::clicked, this, &SolveTasks::close);
    connect(ui->btnOnceMore, &QPushButton::clicked, this, &SolveTasks::restartTasks);

    if (mShowTimer > 0)
        timer.start();
    if (mShowTimer > 1)
        single.singleShot(1000, this, &SolveTasks::updateTimerLabel);

    setTasks();
}

SolveTasks::~SolveTasks()
{
    delete ui;
}

bool SolveTasks::eventFilter(QObject *obj, QEvent *e)
{
    if (obj == ui->leResult)
    {
        if (e->type() == QEvent::KeyPress)
        {
            QKeyEvent *k = static_cast<QKeyEvent*>(e);
            if (k->key() == Qt::Key_Return)
            {
                checkTasks();
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

void SolveTasks::restartTasks()
{
    mResult = 0;
    mSolved = 0;
    mCorrect = 0;

    ui->leResult->setEnabled(true);
    ui->labElapsed->setText("");

    if (mShowTimer > 0)
        timer.start();
    if (mShowTimer > 1)
        single.singleShot(1000, this, &SolveTasks::updateTimerLabel);
    setTasks();
}

void SolveTasks::setTasks()
{
    ui->labRigtige->setText(QString::number(mCorrect));
    ui->labSolved->setText(QString::number(mSolved));
    ui->labMulige->setText(QString::number(mSolved));
    if (mSolved < mAntal)
        solveTask();
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

QString SolveTasks::getTasks()
{
    int a = 0, b = 0;

    switch (mTaskType)
    {
    case 1:
    {
        int tal = static_cast<int>(mMax * 0.6);
        do
        {
            a = QRandomGenerator::global()->bounded(2, tal);
            b = QRandomGenerator::global()->bounded(2, tal);
        } while (a + b > mMax);
        break;
    }
    case 2:
    {
        a = QRandomGenerator::global()->bounded(2, mMax);
        b = QRandomGenerator::global()->bounded(2, mMax);
        if (!mNegativeResult && a < b)
        {
            int tmp = a;
            a = b;
            b = tmp;
        }
        break;
    }
    case 3:
        a = QRandomGenerator::global()->bounded(2, mMax);
        b = QRandomGenerator::global()->bounded(2, mMax);
        break;
    case 4:
    {
        QList<int> divisorer;
        int tal;
        do
        {
            tal = QRandomGenerator::global()->bounded(10, mMax);
            divisorer = getDivisors(tal);
        } while (divisorer.size() < 3);
        int antal = divisorer.count();
        int pos = QRandomGenerator::global()->bounded(1, antal - 1);
        a = tal;
        b = divisorer.at(pos);
    }
        break;
    default:
    {
        int tal = static_cast<int>(mMax * 0.6);
        do
        {
            a = QRandomGenerator::global()->bounded(2, tal);
            b = QRandomGenerator::global()->bounded(2, tal);
        } while (a + b > mMax);
        break;
    }

    }

    return QString(QString::number(a) + "," + QString::number(b));
}

void SolveTasks::checkTasks()
{
    int guess = ui->leResult->text().toInt();
    if (guess == mResult)
    {
        mCorrect++;
    }
    mSolved++;
    setTasks();
}

void SolveTasks::solveTask()
{
    QString opg = getTasks();
    QStringList list = opg.split(",");
    m1 = list.first().toInt();
    m2 = list.last().toInt();

    switch (mTaskType) {
    case 1: mResult = m1 + m2; break;
    case 2: mResult = m1 - m2; break;
    case 3: mResult = m1 * m2; break;
    case 4: mResult = m1 / m2; break;
    default: mResult = m1 + m2; break;
    }

    ui->labFirst->setText(list.first());
    ui->labSecond->setText(list.last());
    ui->leResult->clear();
    ui->leResult->setFocus();
}

void SolveTasks::updateTimerLabel()
{
    if (timer.isValid())
    {
        int elapsed = timer.elapsed() / 1000;
        ui->labElapsed->setText(QString::number(elapsed) + tr(" sek."));
        single.singleShot(1000, this, &SolveTasks::updateTimerLabel);
    }
}

QList<int> SolveTasks::getDivisors(int num)
{
    QList<int> divisors;
    for (int i = 1; i <= num; i++)
        if (num % i == 0)
            divisors.append(i);
    return divisors;
}
