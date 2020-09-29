#include "eco_text.h"
#include "ui_eco_text.h"

Eco_Text::Eco_Text(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Eco_Text)
{
    ui->setupUi(this);
}

Eco_Text::~Eco_Text()
{
    delete ui;
}
