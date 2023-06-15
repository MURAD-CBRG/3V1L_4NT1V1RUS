#include "antiviruswindow.h"
#include "test.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AntivirusWindow w;
    w.show();

    abc();

    return a.exec();
}
