#include "antiviruswindow.h"

#include <QApplication>
#include "analizerseparated.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    AntivirusWindow w;

    return app.exec();
}
