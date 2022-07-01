#include "solvetasks.h"
#include "ui_solvetasks.h"

#include <QKeyEvent>
SolveTasks::SolveTasks(int type, int antal, int max, bool negatives, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SolveTasks)
{
    ui->setupUi(this);

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

    timer.start();
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
    switch (mTaskType) {
    case 1:
        mResult = 0;
        mSolved = 0;
        mCorrect = 0;

        ui->leResult->setEnabled(true);
        ui->labElapsed->setText("");

        timer.restart();
        setTasks();
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        break;
    default:
        break;
    }
}

void SolveTasks::setTasks()
{
    switch (mTaskType) {
    case 1:
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        break;
    default:
        break;
    }
}

QString SolveTasks::getTasks()
{
    switch (mTaskType) {
    case 1:
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        break;
    default:
        break;
    }

    return QString();
}

void SolveTasks::checkTasks()
{
    switch (mTaskType) {
    case 1:
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        break;
    default:
        break;
    }
}

void SolveTasks::solveTask()
{
    switch (mTaskType) {
    case 1:
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        break;
    default:
        break;
    }
}
