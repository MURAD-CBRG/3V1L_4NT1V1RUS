#ifndef ADDFILETODBDIALOG_H
#define ADDFILETODBDIALOG_H

#include <QDialog>
#include <QFileDialog>
#include <QMessageBox>

#include "database_api.h"
#include "signature.h"

namespace Ui
{
    class addFIleToDBDialog;
}

/**
 * \brief A dialog window for adding files to a database.
 *
 * This class provides a dialog window with options for adding files to a database.
 */
class addFIleToDBDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * \brief Constructor for the addFIleToDBDialog class.
     * \param parent The parent widget, if any.
     *
     * This function constructs a new instance of the addFIleToDBDialog class and initializes its
     * user interface.
     */
    explicit addFIleToDBDialog(QWidget *parent = nullptr);

    /**
     * \brief Destructor for the addFIleToDBDialog class.
     *
     * This function frees any resources used by the addFIleToDBDialog class.
     */
    ~addFIleToDBDialog();

private slots:
    /**
     * \brief Function called when the browse button is clicked.
     *
     * This function opens a file browser dialog to allow the user to select an executable file to add
     * to the database. If a file is selected, its path is displayed in the pathLine QLineEdit widget.
     */
    void on_browseButton_clicked();

    /**
     * \brief Function called when the add button is clicked.
     *
     * This function adds the selected file to the database, if it is an executable file. If the file
     * is not an executable file, an appropriate error message is displayed.
     */
    void on_addButton_clicked();

    /**
     * \brief Function called when the remove button is clicked.
     *
     * This function removes the selected file from the database, if it is an executable file. If the file
     * is not an executable file, an appropriate error message is displayed.
     */
    void on_removeButton_clicked();

private:
    Ui::addFIleToDBDialog *ui; /**< A pointer to the user interface object for the addFIleToDBDialog class. */
};

#endif // ADDFILETODBDIALOG_H
