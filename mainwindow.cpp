#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "plusopgaver.h"

#include <QSpinBox>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupOptions();

    connect(ui->btnExit, &QPushButton::clicked, this, &MainWindow::close);
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

void MainWindow::setupPlus()
{
    QGridLayout* grid = new QGridLayout;

    QLabel* labOpgaveAntal = new QLabel(tr("Antal opgaver:"));
    QSpinBox* sbAntal = new QSpinBox;
    sbAntal->setMinimum(10);
    sbAntal->setMaximum(100);
    sbAntal->setValue(20);
    sbAntal->setToolTip(tr("Interval: 10-100"));
    grid->addWidget(labOpgaveAntal,0, 0);
    grid->addWidget(sbAntal,0, 1);

    QLabel* labMaxSum = new QLabel(tr("Maksimum sum:"));
    QSpinBox* sbMaxSum = new QSpinBox;
    sbMaxSum->setMinimum(20);
    sbMaxSum->setMaximum(1000);
    sbMaxSum->setValue(50);
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
    PlusOpgaver* plusOpg = new PlusOpgaver();
    plusOpg->setCore(mPlusAntal, mPlusMaxSum);
    plusOpg->show();
}

void MainWindow::setupMinus()
{

}

void MainWindow::setupGange()
{

}

void MainWindow::setupDivision()
{

}

