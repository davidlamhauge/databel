#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "plusopgaver.h"
#include "minusopgaver.h"

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
    setWindowTitle("databel");

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
        setupPlus();
    else if (ui->rbMinus->isChecked())
        setupMinus();
    else if (ui->rbGange->isChecked())
        setupGange();
    else if (ui->rbDivision->isChecked())
        setupDivision();
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
    mPlusAntal = 20;
    sbAntal->setToolTip(tr("Interval: 10-100"));
    grid->addWidget(labOpgaveAntal,0, 0);
    grid->addWidget(sbAntal,0, 1);

    QLabel* labMaxSum = new QLabel(tr("Maksimum sum:"));
    QSpinBox* sbMaxSum = new QSpinBox;
    sbMaxSum->setMinimum(20);
    sbMaxSum->setMaximum(1000);
    sbMaxSum->setValue(50);
    mPlusMaxSum = 50;
    sbMaxSum->setToolTip(tr("Interval: 20-1000"));
    grid->addWidget(labMaxSum,1, 0);
    grid->addWidget(sbMaxSum,1, 1);

    QPushButton* btnOK = new QPushButton(tr("Gå til Plus-opgaver"));
    grid->addWidget(btnOK, 2, 1);

    // connects
    connect(sbAntal, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::setPlusAntal);
    connect(sbMaxSum, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::setPlusMaxSum);
    connect(btnOK, &QPushButton::clicked, this, &MainWindow::plusChosen);

    ui->groupBox->setLayout(grid);
}

void MainWindow::plusChosen()
{
    PlusOpgaver* plusOpg = new PlusOpgaver(mPlusAntal, mPlusMaxSum);
    plusOpg->show();
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
    mMinusAntal = 20;
    sbAntal->setToolTip(tr("Interval: 10-100"));
    grid->addWidget(labOpgaveAntal,0, 0);
    grid->addWidget(sbAntal,0, 1);

    QLabel* labMaxTal = new QLabel(tr("Ikke tal større end:"));
    QSpinBox* sbMaxTal = new QSpinBox;
    sbMaxTal->setMinimum(20);
    sbMaxTal->setMaximum(500);
    sbMaxTal->setValue(50);
    mMinusMaxTal = 50;
    sbMaxTal->setToolTip(tr("Interval: 20-500"));
    grid->addWidget(labMaxTal,1, 0);
    grid->addWidget(sbMaxTal,1, 1);

    QCheckBox* cb = new QCheckBox(tr("Tillad negativ differens"));
    grid->addWidget(cb, 2, 1);

    QPushButton* btnOK = new QPushButton(tr("Gå til Minus-opgaver"));
    grid->addWidget(btnOK, 3, 1);

    // connects
    connect(sbAntal, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::setMinusAntal);
    connect(sbMaxTal, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::setMinusMaxTal);
    connect(cb, &QCheckBox::stateChanged, this, &MainWindow::setNegativeResult);
    connect(btnOK, &QPushButton::clicked, this, &MainWindow::minusChosen);

    ui->groupBox->setLayout(grid);
}

void MainWindow::setNegativeResult(int state)
{
    if (state == 2)
        mNegativeResult = true;
    else
        mNegativeResult = false;
}

void MainWindow::minusChosen()
{
    MinusOpgaver* minusOpg = new MinusOpgaver(mMinusAntal, mMinusMaxTal, mNegativeResult);
    minusOpg->show();
}

void MainWindow::setupGange()
{
    removeLayout();

}

void MainWindow::setupDivision()
{
    removeLayout();

}

