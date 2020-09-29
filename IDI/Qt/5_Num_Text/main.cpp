#include "numtext.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    NumText w;
    w.show();

    return a.exec();
}
