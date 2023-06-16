#include "antiviruswindow.h"
#include "./ui_antiviruswindow.h"
#include <QMessageBox>
#include <QSystemTrayIcon>
#include "antivirus.h"

AntivirusWindow::AntivirusWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AntivirusWindow)
{
    ui->setupUi(this);
    mySysTrayIcon = new QSystemTrayIcon(this);
    mySysTrayIcon->setIcon(QIcon(":/sprites/anti.png"));
    mySysTrayIcon->setVisible(true);
}

AntivirusWindow::~AntivirusWindow()
{
    delete ui;
}


void AntivirusWindow::on_checkDirButton_clicked()
{
    mySysTrayIcon->showMessage(tr("Clicked!!!!"), tr("yeah, good"));
}


void AntivirusWindow::on_actionExit_triggered()
{
    QCoreApplication::quit();
}


void AntivirusWindow::on_checkFileButton_clicked()
{
    QLineEdit* lineEdit = this->findChild<QLineEdit*>("filenameLine");
    QString filename = lineEdit->text();
    try{
        Signature sig1{filename.toStdString()};
        QMessageBox::information(this, "Hash", tr("The hash is ") + tr(sig1.get_hash().c_str()));
    }
    catch(std::ifstream::failure){
        QMessageBox::critical(this, "No such file!", "Can't check that file!");
    }
}


void AntivirusWindow::on_browseFileButton_clicked()
{
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this,
                                            tr("Choose File for checking"),
                                            "",
                                            tr("Executable files (*.exe)") //tr("text files (*.txt);; png files (*.png)")
                                            );
    //fileName = QFileDialog::getExistingDirectory(this, tr("something else"), "");

    if (!fileName.isNull())
    {
        QLineEdit* lineEdit = this->findChild<QLineEdit*>("filenameLine");
        lineEdit->setText(fileName);
        QMessageBox::information(nullptr, "Title", fileName);
        //auto a = QMessageBox(this);
        //a.setText(fileName);
        //a.show();
    }

    else
    {
        // Нажмите Да, чтобы отменить
    }
}

