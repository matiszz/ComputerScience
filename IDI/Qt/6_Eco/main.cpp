#include "eco_text.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Eco_Text w;
    w.show();

    return a.exec();
}
