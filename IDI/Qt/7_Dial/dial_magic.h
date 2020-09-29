#ifndef DIAL_MAGIC_H
#define DIAL_MAGIC_H

#include <QWidget>

namespace Ui {
class Dial_Magic;
}

class Dial_Magic : public QWidget
{
    Q_OBJECT

public:
    explicit Dial_Magic(QWidget *parent = 0);
    ~Dial_Magic();

private:
    Ui::Dial_Magic *ui;
};

#endif // DIAL_MAGIC_H
