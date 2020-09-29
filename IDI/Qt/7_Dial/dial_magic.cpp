#include "dial_magic.h"
#include "ui_dial_magic.h"

Dial_Magic::Dial_Magic(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Dial_Magic)
{
    ui->setupUi(this);
}

Dial_Magic::~Dial_Magic()
{
    delete ui;
}
