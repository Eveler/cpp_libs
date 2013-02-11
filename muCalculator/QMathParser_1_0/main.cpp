#include <QApplication>
#include "qmathparser.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMathParser w;
    w.show();

    return a.exec();
}
