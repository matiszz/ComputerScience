#include <QWidget>
#include "ui_maincolors.h"

class MainColors : public QWidget {
    Q_OBJECT

public:
    MainColors(QWidget *parent = 0);

private:
    Ui::MainColors ui;
};
