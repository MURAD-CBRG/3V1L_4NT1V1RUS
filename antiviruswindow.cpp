#include "antiviruswindow.h"
#include "./ui_antiviruswindow.h"

AntivirusWindow::AntivirusWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AntivirusWindow)
{
    ui->setupUi(this);
}

AntivirusWindow::~AntivirusWindow()
{
    delete ui;
}

