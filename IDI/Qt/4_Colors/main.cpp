#include "maincolors.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainColors w;
    w.show();

    return a.exec();
}
