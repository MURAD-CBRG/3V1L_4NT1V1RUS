#include "addfiletodbdialog.h"
#include "ui_addfiletodbdialog.h"

addFIleToDBDialog::addFIleToDBDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addFIleToDBDialog)
{
    ui->setupUi(this);
}

addFIleToDBDialog::~addFIleToDBDialog()
{
    delete ui;
}

void addFIleToDBDialog::on_browseButton_clicked()
{
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this,
                                            tr("Choose File"),
                                            "",
                                            tr("Executable files (*.exe)")
                                            );

    if (!fileName.isNull())
    {
        QLineEdit* lineEdit = this->findChild<QLineEdit*>("pathLine");
        lineEdit->setText(fileName);
    }
}


void addFIleToDBDialog::on_addButton_clicked()
{
    QLineEdit* lineEdit = this->findChild<QLineEdit*>("pathLine");
    try{
        Signature sig{lineEdit->text().toStdString()};
        std::string hash_exe = sig.get_hash();
        database_control(hash_exe, "ADD");
    }
    catch(std::ifstream::failure){
        QMessageBox::critical(this, "Error", "Occured error while reading the file!");
    }
    catch(std::invalid_argument){
        QMessageBox::information(this, "Not exe!", "This file is not EXE!");
    }
}


void addFIleToDBDialog::on_removeButton_clicked()
{
    QLineEdit* lineEdit = this->findChild<QLineEdit*>("pathLine");
    std::string filename = lineEdit->text().toStdString();
    try{
        Signature sig{lineEdit->text().toStdString()};
        std::string hash_exe = sig.get_hash();
        database_control(hash_exe, "DELETE");
    }
    catch(std::ifstream::failure){
        QMessageBox::critical(this, "Error", "Occured error while reading the file!");
    }
    catch(std::invalid_argument){
        QMessageBox::information(this, "Not exe!", "This file is not EXE!");
    }
}
