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

/**
 * \brief A dialog box for configuring the automatic analysis feature.
 *
 * This class represents a dialog box for configuring the automatic analysis feature of the antivirus application.
 */
class configureDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * \brief Constructs a new configureDialog object.
     *
     * This constructor creates a new configureDialog object and sets its parent widget to the given parent.
     * It creates the QPlainTextEdit, QCheckBox, and QSpinBox widgets and adds them to the dialog box.
     */
    explicit configureDialog(QWidget *parent = nullptr);

    /**
     * \brief Destroys the configureDialog object.
     *
     * This destructor destroys the configureDialog object and frees any resources used by the object.
     */
    ~configureDialog();

private slots:
    /**
     * \brief Called when the save button is clicked.
     *
     * This function is called when the save button is clicked. It reads the values from the QPlainTextEdit,
     * QCheckBox, and QSpinBox widgets and saves them to a file using the setConfigurationAnalysis() function
     * from the conf.h header file.
     */
    void on_saveButton_clicked();

private:
    Ui::configureDialog *ui; /**< The user interface for the configureDialog object. */
    QPlainTextEdit* dirsEdit; /**< The QPlainTextEdit widget for entering the directories to be included in the automatic analysis. */
    QCheckBox* isonCheckbox; /**< The QCheckBox widget for enabling or disabling automatic analysis. */
    QSpinBox* timeintervalEdit; /**< The QSpinBox widget for setting the time interval between automatic analyses. */
};

#endif // CONFIGUREDIALOG_H
