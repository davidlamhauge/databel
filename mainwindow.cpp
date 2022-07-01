#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "solvetasks.h"

#include <QSpinBox>
#include <QCheckBox>
#include <QPushButton>
#include <QRadioButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupOptions();
    setWindowTitle("databel - v. " APP_VERSION);

    connect(ui->btnExit, &QPushButton::clicked, this, &MainWindow::close);
    connect(ui->rbPlus, &QRadioButton::toggled, this, &MainWindow::setupOptions);
    connect(ui->rbMinus, &QRadioButton::toggled, this, &MainWindow::setupOptions);
    connect(ui->rbGange, &QRadioButton::toggled, this, &MainWindow::setupOptions);
    connect(ui->rbDivision, &QRadioButton::toggled, this, &MainWindow::setupOptions);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupOptions()
{
    if (ui->rbPlus->isChecked())
    {
        mTaskType = 1;
        setupPlus();
    }
    else if (ui->rbMinus->isChecked())
    {
        mTaskType = 2;
        setupMinus();
    }
    else if (ui->rbGange->isChecked())
    {
        mTaskType = 3;
        setupGange();
    }
    else if (ui->rbDivision->isChecked())
    {
        mTaskType = 4;
        setupDivision();
    }
}

void MainWindow::removeLayout()
{
    if (ui->groupBox->layout() != nullptr)
    {
        QLayoutItem* item;
        while ((item = ui->groupBox->layout()->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
        delete ui->groupBox->layout();
    }
}

void MainWindow::setupPlus()
{
    removeLayout();

    QGridLayout* grid = new QGridLayout;

    QLabel* labOpgaveAntal = new QLabel(tr("Antal opgaver:"));
    QSpinBox* sbAntal = new QSpinBox;
    sbAntal->setMinimum(10);
    sbAntal->setMaximum(100);
    sbAntal->setValue(20);
    mAntal = 20;
    sbAntal->setToolTip(tr("Interval: 10-100"));
    grid->addWidget(labOpgaveAntal,0, 0);
    grid->addWidget(sbAntal,0, 1);

    QLabel* labMaxSum = new QLabel(tr("Maksimum sum:"));
    QSpinBox* sbMaxSum = new QSpinBox;
    sbMaxSum->setMinimum(20);
    sbMaxSum->setMaximum(1000);
    sbMaxSum->setValue(50);
    mMax = 50;
    sbMaxSum->setToolTip(tr("Interval: 20-1000"));
    grid->addWidget(labMaxSum,1, 0);
    grid->addWidget(sbMaxSum,1, 1);

    QPushButton* btnOK = new QPushButton(tr("Gå til Plus-opgaver"));
    grid->addWidget(btnOK, 2, 1);

    // connects
    connect(sbAntal, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::setOptionAntal);
    connect(sbMaxSum, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::setOptionMax);
    connect(btnOK, &QPushButton::clicked, this, &MainWindow::optionChosen);

    ui->groupBox->setLayout(grid);
}

void MainWindow::setupMinus()
{
    removeLayout();

    QGridLayout* grid = new QGridLayout;

    QLabel* labOpgaveAntal = new QLabel(tr("Antal opgaver:"));
    QSpinBox* sbAntal = new QSpinBox;
    sbAntal->setMinimum(10);
    sbAntal->setMaximum(100);
    sbAntal->setValue(20);
    mAntal = 20;
    sbAntal->setToolTip(tr("Interval: 10-100"));
    grid->addWidget(labOpgaveAntal,0, 0);
    grid->addWidget(sbAntal,0, 1);

    QLabel* labMaxTal = new QLabel(tr("Ikke tal større end:"));
    QSpinBox* sbMaxTal = new QSpinBox;
    sbMaxTal->setMinimum(20);
    sbMaxTal->setMaximum(500);
    sbMaxTal->setValue(50);
    mMax = 50;
    sbMaxTal->setToolTip(tr("Interval: 20-500"));
    grid->addWidget(labMaxTal,1, 0);
    grid->addWidget(sbMaxTal,1, 1);

    QCheckBox* cb = new QCheckBox(tr("Tillad negativ differens"));
    grid->addWidget(cb, 2, 1);

    QPushButton* btnOK = new QPushButton(tr("Gå til Minus-opgaver"));
    grid->addWidget(btnOK, 3, 1);

    // connects
    connect(sbAntal, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::setOptionAntal);
    connect(sbMaxTal, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::setOptionMax);
    connect(cb, &QCheckBox::stateChanged, this, &MainWindow::setNegativeResult);
    connect(btnOK, &QPushButton::clicked, this, &MainWindow::optionChosen);

    ui->groupBox->setLayout(grid);
}

void MainWindow::setupGange()
{
    removeLayout();

    QGridLayout* grid = new QGridLayout;

    QLabel* labOpgaveAntal = new QLabel(tr("Antal opgaver:"));
    QSpinBox* sbAntal = new QSpinBox;
    sbAntal->setMinimum(10);
    sbAntal->setMaximum(100);
    sbAntal->setValue(20);
    mAntal = 20;
    sbAntal->setToolTip(tr("Interval: 10-100"));
    grid->addWidget(labOpgaveAntal,0, 0);
    grid->addWidget(sbAntal,0, 1);

    QLabel* labMaxTal = new QLabel(tr("Ikke faktorer større end:"));
    QSpinBox* sbMaxTal = new QSpinBox;
    sbMaxTal->setMinimum(5);
    sbMaxTal->setMaximum(20);
    sbMaxTal->setValue(10);
    mMax = 10;
    sbMaxTal->setToolTip(tr("Interval: 5-20"));
    grid->addWidget(labMaxTal,1, 0);
    grid->addWidget(sbMaxTal,1, 1);

    QPushButton* btnOK = new QPushButton(tr("Gå til Gange-opgaver"));
    grid->addWidget(btnOK, 2, 1);

    // connects
    connect(sbAntal, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::setOptionAntal);
    connect(sbMaxTal, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::setOptionMax);
    connect(btnOK, &QPushButton::clicked, this, &MainWindow::optionChosen);

    ui->groupBox->setLayout(grid);
}

void MainWindow::setupDivision()
{
    removeLayout();

    QGridLayout* grid = new QGridLayout;

    QLabel* labOpgaveAntal = new QLabel(tr("Antal opgaver:"));
    QSpinBox* sbAntal = new QSpinBox;
    sbAntal->setMinimum(10);
    sbAntal->setMaximum(100);
    sbAntal->setValue(20);
    mAntal = 20;
    sbAntal->setToolTip(tr("Interval: 10-100"));
    grid->addWidget(labOpgaveAntal,0, 0);
    grid->addWidget(sbAntal,0, 1);

    QLabel* labMaxTal = new QLabel(tr("Ikke dividend større end:"));
    QSpinBox* sbMaxTal = new QSpinBox;
    sbMaxTal->setMinimum(20);
    sbMaxTal->setMaximum(1000);
    sbMaxTal->setValue(50);
    mMax = 50;
    sbMaxTal->setToolTip(tr("Interval: 20-1000"));
    grid->addWidget(labMaxTal,1, 0);
    grid->addWidget(sbMaxTal,1, 1);

    QPushButton* btnOK = new QPushButton(tr("Gå til Divisions-opgaver"));
    grid->addWidget(btnOK, 2, 1);

    // connects
    connect(sbAntal, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::setOptionAntal);
    connect(sbMaxTal, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::setOptionMax);
    connect(btnOK, &QPushButton::clicked, this, &MainWindow::optionChosen);

    ui->groupBox->setLayout(grid);

}

void MainWindow::setNegativeResult(int state)
{
    if (state == 2)
        mNegativeResult = true;
    else
        mNegativeResult = false;
}

void MainWindow::setupOption(int taskType)
{
    switch (taskType) {
    case 1: setupPlus(); break;
    case 2: setupMinus(); break;
    case 3: setupGange(); break;
    case 4: setupDivision(); break;
    default: setupPlus(); break;
    }
}

void MainWindow::optionChosen()
{
    SolveTasks* solve = new SolveTasks(mTaskType, mAntal, mMax, mNegativeResult);
    solve->show();
}

