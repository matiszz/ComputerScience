#include "conversio.h"
#include "ui_conversio.h"

Conversio::Conversio(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Conversio)
{
    ui->setupUi(this);
}

Conversio::~Conversio()
{
    delete ui;
}
