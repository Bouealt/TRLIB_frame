#include "TRLIB.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])

{
    QApplication a(argc, argv);
    TRLIB w;
    w.show();
    return a.exec();
}
