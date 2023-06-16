#ifndef CONFIGUREDIALOG_H
#define CONFIGUREDIALOG_H

#include <QDialog>
#include <QPlainTextEdit>>
#include <QCheckBox>
#include <QSpinBox>
#include <QMessageBox>
#include <string>
#include <sstream>
#include <numeric>

#include "conf.h"

namespace Ui {
class configureDialog;
}

class configureDialog : public QDialog
{
    Q_OBJECT

public:
    explicit configureDialog(QWidget *parent = nullptr);
    ~configureDialog();

private slots:
    void on_saveButton_clicked();

private:
    Ui::configureDialog *ui;
    QPlainTextEdit* dirsEdit;
    QCheckBox* isonCheckbox;
    QSpinBox* timeintervalEdit;
};

#endif // CONFIGUREDIALOG_H
