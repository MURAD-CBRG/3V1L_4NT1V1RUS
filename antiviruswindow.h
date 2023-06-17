#ifndef ANTIVIRUSWINDOW_H
#define ANTIVIRUSWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QSystemTrayIcon>
#include <QMessageBox>
#include <QMenu>
#include <QFileDialog>
#include <QThread>
#include <filesystem>

#include "signature.h"
#include "database_api.h"
#include "conf.h"
#include "analizerseparated.h"
#include "dir_reader.h"
#include "addfiletodbdialog.h"
#include "configuredialog.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class AntivirusWindow;
}
QT_END_NAMESPACE

class QSystemTrayIcon;

/**
 * \brief The main window class for the antivirus application.
 *
 * This class defines the main window for the antivirus application. It contains slots for responding
 * to user actions, such as checking a file or directory, adding a new signature, or opening the settings
 * dialog.
 *
 */
class AntivirusWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * \brief Constructs the main window for the antivirus application.
     *
     * This function initializes the user interface and sets up the system tray icon and the autoanalyzer thread.
     */
    AntivirusWindow(QWidget *parent = nullptr);

    /**
     * \brief Destroys the main window for the antivirus application.
     *
     * This function stops the autoanalyzer thread, hides the system tray icon and deletes the user interface and system tray icon objects.
     */
    ~AntivirusWindow();

protected:
    /**
     * \brief Overridden function for handling close events.
     *
     * This function is called when the main window is closed. If the system tray icon is visible, it hides
     * the main window instead of closing it.
     */
    void closeEvent(QCloseEvent *event) override;

    /**
     * \brief Overridden function for handling change events.
     *
     * This function is called when the main window changes state, such as when it is minimized or restored.
     * If the main window is minimized, it hides the window instead of minimizing it.
     */
    void changeEvent(QEvent *event) override;

private slots:
    /**
     * \brief Function for checking a directory for viruses.
     *
     * This function gets the directory path from the "dirnameLine" QLineEdit object in the user interface,
     * and calls the read_dir() function to analyze the files in the directory. The results are displayed
     * in the "logging" QTextEdit object.
     */
    void on_checkDirButton_clicked();

    /**
     * \brief Function for exiting the application.
     *
     * This function quits the QApplication, closing the application.
     */
    void on_actionExit_triggered();

    /**
     * \brief Function for checking a file for viruses.
     *
     * This function gets the file path from the "filenameLine" QLineEdit object in the user interface,
     * and creates a Signature object to calculate the file's hash. It then checks the hash in the database
     * and displays the results in the "logging" QTextEdit object.
     */
    void on_checkFileButton_clicked();

    /**
     * \brief Function for opening a file dialog to choose a file to check.
     *
     * This function opens a file dialog using QFileDialog to allow the user to choose a file to check.
     * Once a file is selected, the file path is displayed in the "filenameLine" QLineEdit object in the user interface.
     */
    void on_browseFileButton_clicked();

    /**
     * \brief Function for opening a file dialog to choose a directory to check.
     *
     * This function opens a file dialog using QFileDialog to allow the user to choose a directory to check.
     * Once a directory is selected, the directory path is displayed in the "dirnameLine" QLineEdit object in the user interface.
     */
    void on_browseDirectoryButton_clicked();

    /**
     * \brief Function for opening a dialog to add a new signature to the database.
     *
     * This function opens a dialog window to allow the user to add a new signature file to the database.
     */
    void on_actionNew_Signature_triggered();

    /**
     * \brief Function for responding to system tray icon activation events.
     *
     * It brings the main window back into focus after the double click on the tray icon.
     */
    void trayIconActivated(QSystemTrayIcon::ActivationReason reason);

    /**
     * \brief Function for opening the settings dialog.
     *
     * This function opens a dialog window to allow the user to change the application settings, such as the
     * directories to be scanned and the scanning interval.
     */
    void on_actionSettings_triggered();

    /**
     * \brief Function for starting the automatic directory analysis.
     *
     * This function reads the current configuration for the automatic analysis from the configuration file,
     * and starts the directory analysis in a separate thread using the analizerSeparated class. The results
     * are displayed in the "logging" QTextEdit object.
     */
    void autocheck_on();

private:
    Ui::AntivirusWindow *ui;        /**< The user interface for the antivirus application. */
    QSystemTrayIcon *mySysTrayIcon; /**< The system tray icon for the antivirus application. */
    QThread *autoanalyzerThread;    /**< The QThread object for the automatic analysis. */
};
#endif // ANTIVIRUSWINDOW_H
