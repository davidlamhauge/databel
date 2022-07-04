#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "solvetasks.h"
#include "tabeltrainer.h"
#include "preferencemanager.h"

#include <QSpinBox>
#include <QCheckBox>
#include <QPushButton>
#include <QRadioButton>
#include <QSettings>
#include <QScreen>
#include <QTranslator>
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // initialize settings
    QSettings settings("TeamLamhauge", "daTabel");
    resize(settings.value("winSize", QSize(400, 300)).toSize());
    move(settings.value("winPos", this->pos()).toPoint());
    mTaskType = settings.value("taskType", 1).toInt();

    switch (mTaskType) {
    case 1 : ui->rbPlus->setChecked(true); break;
    case 2 : ui->rbMinus->setChecked(true); break;
    case 3 : ui->rbGange->setChecked(true); break;
    case 4 : ui->rbDivision->setChecked(true); break;
    default: ui->rbPlus->setChecked(true); break;
    }

    setupOptions();
    setWindowTitle("databel - v. " APP_VERSION);

    connect(ui->btnExit, &QPushButton::clicked, this, &MainWindow::close);
    connect(ui->btnSettings, &QPushButton::clicked, this, &MainWindow::setupSettings);
    connect(ui->rbPlus, &QRadioButton::toggled, this, &MainWindow::setupOptions);
    connect(ui->rbMinus, &QRadioButton::toggled, this, &MainWindow::setupOptions);
    connect(ui->rbGange, &QRadioButton::toggled, this, &MainWindow::setupOptions);
    connect(ui->rbDivision, &QRadioButton::toggled, this, &MainWindow::setupOptions);
    connect(ui->rbGangeTabel, &QRadioButton::toggled, this, &MainWindow::setupOptions);
    connect(ui->rbPlusTabel, &QRadioButton::toggled, this, &MainWindow::setupOptions);
}

MainWindow::~MainWindow()
{
    // save settings for next session
    QSettings settings("TeamLamhauge", "daTabel");
    settings.setValue("winPos", pos());
    settings.setValue("winSize", size());

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
    else if (ui->rbGangeTabel->isChecked())
    {
        mTaskType = 5;
        setupGangeTabel();
    }
    else if (ui->rbPlusTabel->isChecked())
    {
        mTaskType = 6;
        setupPlusTabel();
    }

    QSettings settings("TeamLamhauge", "daTabel");
    settings.setValue("taskType", mTaskType);
}

void MainWindow::setupSettings()
{
    // first save current language...
    QSettings settings("TeamLamhauge", "daTabel");
    QString tmp = settings.value("lang", ":lang/lang/databel_da").toString();

    // ...then start preferencemanager...
    prefs = new PreferenceManager();
    prefs->move(pos());
    prefs->exec();

    // ...then update settings, and make necessary changes
    updateSettings();

    // need to change UI language ?
    if (tmp != mLanguage)
    {
        QTranslator* translator = new QTranslator(this);
        translator->load(mLanguage);
        QCoreApplication::installTranslator(translator);
        ui->retranslateUi(this);
        setupOptions();
    }
}

void MainWindow::updateSettings()
{
    QSettings settings("TeamLamhauge", "daTabel");
    mLanguage = settings.value("lang", ":lang/lang/databel_da").toString();
    mLangIndex = settings.value("langIndex", 0).toInt();
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
    grid->addWidget(cb, 2, 0);

    QPushButton* btnOK = new QPushButton(tr("Gå til Minus-opgaver"));
    grid->addWidget(btnOK, 2, 1);

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

void MainWindow::setupGangeTabel()
{
    removeLayout();

    QGridLayout* grid = new QGridLayout;

    QLabel* labChoose = new QLabel(tr("Vælg tabel:"));
    QSpinBox* sbTabel = new QSpinBox;
    sbTabel->setMinimum(2);
    sbTabel->setMaximum(20);
    sbTabel->setValue(5);
    mTabel = 5;
    sbTabel->setToolTip(tr("Interval: 2-20"));
    grid->addWidget(labChoose, 0, 0);
    grid->addWidget(sbTabel, 0, 1);

    QLabel* lab1 = new QLabel(tr("Tabel ovenfor"));
    QPushButton* btnEn = new QPushButton(tr("Gangetabel"));
    grid->addWidget(lab1, 1, 0);
    grid->addWidget(btnEn, 1, 1);

    QLabel* lab100 = new QLabel(tr("1-10 x 1-10"));
    QPushButton* btnOK = new QPushButton(tr("Fuld gangetabel"));
    grid->addWidget(lab100, 2, 0);
    grid->addWidget(btnOK, 2, 1);

    // connects
    connect(btnOK, &QPushButton::clicked, this, &MainWindow::tabelChosen);
    connect(btnEn, &QPushButton::clicked, this, &MainWindow::tabelSingle);
    connect(sbTabel, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::setOptionTabel);

    ui->groupBox->setLayout(grid);

}

void MainWindow::setupPlusTabel()
{
    removeLayout();

    QGridLayout* grid = new QGridLayout;

    QLabel* labChoose = new QLabel(tr("Vælg tabel:"));
    QSpinBox* sbTabel = new QSpinBox;
    sbTabel->setMinimum(2);
    sbTabel->setMaximum(20);
    sbTabel->setValue(5);
    mTabel = 5;
    sbTabel->setToolTip(tr("Interval: 2-20"));
    grid->addWidget(labChoose, 0, 0);
    grid->addWidget(sbTabel, 0, 1);

    QLabel* lab1 = new QLabel(tr("Tabel ovenfor"));
    QPushButton* btnEn = new QPushButton(tr("Plustabel"));
    grid->addWidget(lab1, 1, 0);
    grid->addWidget(btnEn, 1, 1);

    QLabel* lab100 = new QLabel(tr("1-10 x 1-10"));
    QPushButton* btnOK = new QPushButton(tr("Fuld plustabel"));
    grid->addWidget(lab100, 2, 0);
    grid->addWidget(btnOK, 2, 1);

    // connects
    connect(btnOK, &QPushButton::clicked, this, &MainWindow::tabelChosen);
    connect(btnEn, &QPushButton::clicked, this, &MainWindow::tabelSingle);
    connect(sbTabel, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::setOptionTabel);

    ui->groupBox->setLayout(grid);
}

void MainWindow::setNegativeResult(int state)
{
    if (state == 2)
        mNegativeResult = true;
    else
        mNegativeResult = false;
}

void MainWindow::optionChosen()
{
    QSettings settings("TeamLamhauge", "daTabel");
    settings.setValue("winPos", pos());

    solve = new SolveTasks(mTaskType, mAntal, mMax, mNegativeResult);
    solve->show();
}

void MainWindow::tabelChosen()
{
    QSettings settings("TeamLamhauge", "daTabel");
    settings.setValue("winPos", pos());

    trainer = new TabelTrainer(mTaskType);
    trainer->show();
}

void MainWindow::tabelSingle()
{
    QSettings settings("TeamLamhauge", "daTabel");
    settings.setValue("winPos", pos());

    solve = new SolveTasks(mTaskType, mTabel);
    solve->show();
}

