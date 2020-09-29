#ifndef CONVERSIO_H
#define CONVERSIO_H

#include <QWidget>

namespace Ui {
class Conversio;
}

class Conversio : public QWidget
{
    Q_OBJECT

public:
    explicit Conversio(QWidget *parent = 0);
    ~Conversio();

private:
    Ui::Conversio *ui;
};

#endif // CONVERSIO_H
