#include "antiviruswindow.h"

#include <QApplication>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QDebug>

#include <iostream>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    AntivirusWindow w;
    w.show();

    return app.exec();
}
