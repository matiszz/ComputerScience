#include "numtext.h"
#include "ui_numtext.h"

NumText::NumText(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NumText)
{
    ui->setupUi(this);
}

NumText::~NumText()
{
    delete ui;
}
