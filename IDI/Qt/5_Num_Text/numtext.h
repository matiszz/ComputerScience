#ifndef NUMTEXT_H
#define NUMTEXT_H

#include <QWidget>

namespace Ui {
class NumText;
}

class NumText : public QWidget
{
    Q_OBJECT

public:
    explicit NumText(QWidget *parent = 0);
    ~NumText();

private:
    Ui::NumText *ui;
};

#endif // NUMTEXT_H
