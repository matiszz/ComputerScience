#ifndef ECO_TEXT_H
#define ECO_TEXT_H

#include <QWidget>

namespace Ui {
class Eco_Text;
}

class Eco_Text : public QWidget
{
    Q_OBJECT

public:
    explicit Eco_Text(QWidget *parent = 0);
    ~Eco_Text();

private:
    Ui::Eco_Text *ui;
};

#endif // ECO_TEXT_H
