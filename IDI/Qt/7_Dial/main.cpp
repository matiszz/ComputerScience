#include "dial_magic.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dial_Magic w;
    w.show();

    return a.exec();
}
