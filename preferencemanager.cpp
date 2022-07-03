#include "preferencemanager.h"
#include "ui_preferencemanager.h"

#include <QSettings>

PreferenceManager::PreferenceManager(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PreferenceManager)
{
    ui->setupUi(this);

    QSettings settings("TeamLamhauge", "daTabel");
    int index = settings.value("langIndex", 0).toInt();
    ui->cbLanguage->setCurrentIndex(index);
    int timerindex = settings.value("timer", 0).toInt();
    ui->cbTimer->setCurrentIndex(timerindex);

    connect(ui->btnOk, &QPushButton::clicked, this, &PreferenceManager::close);
    connect(ui->cbLanguage, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &PreferenceManager::setLanguage);
    connect(ui->cbTimer, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &PreferenceManager::setTimerVisibility);
}

PreferenceManager::~PreferenceManager()
{
    delete ui;
}

void PreferenceManager::setLanguage(int i)
{
    QSettings settings("TeamLamhauge", "daTabel");

    switch (i)
    {
    case 0:
        settings.setValue("lang", ":lang/lang/databel_da");
        break;
    case 1:
        settings.setValue("lang", ":lang/lang/databel_en");
        break;
    default:
        settings.setValue("lang", ":lang/lang/databel_da");
        break;
    }
    settings.setValue("langIndex", i);
}

void PreferenceManager::setTimerVisibility(int i)
{
    QSettings settings("TeamLamhauge", "daTabel");
    settings.setValue("timer", i);
}
