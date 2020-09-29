// MyForm.h – Ui::MyForm com a membre

#include "ui_Form.h"
#include <QWidget>

class MyForm : public QWidget {
    Q_OBJECT

public:
    MyForm(QWidget *parent = 0);

private:
    Ui::MyForm ui;
};
