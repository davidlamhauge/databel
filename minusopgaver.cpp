#include "minusopgaver.h"
#include "ui_minusopgaver.h"

MinusOpgaver::MinusOpgaver(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MinusOpgaver)
{
    ui->setupUi(this);
}

MinusOpgaver::~MinusOpgaver()
{
    delete ui;
}
