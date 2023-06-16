#ifndef ANTIVIRUSWINDOW_H
#define ANTIVIRUSWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QSystemTrayIcon>
#include <QMessageBox>
#include <QMenu>
#include <QFileDialog>
#include <QThread>

#include "signature.h"
#include "bypass.h"
#include "addfiletodbdialog.h"
#include "db_manager/database_api.h"
#include "conf.h"
#include "analizerseparated.h"
#include "dir_reader.h"

QT_BEGIN_NAMESPACE
namespace Ui { class AntivirusWindow; }
QT_END_NAMESPACE

class QSystemTrayIcon;

class AntivirusWindow : public QMainWindow
{
    Q_OBJECT

public:
    AntivirusWindow(QWidget *parent = nullptr);
    ~AntivirusWindow();

protected:
    void closeEvent(QCloseEvent* event) override;

    void changeEvent(QEvent* event) override;

private slots:
    void on_checkDirButton_clicked();

    void on_actionExit_triggered();

    void on_checkFileButton_clicked();

    void on_browseFileButton_clicked();

    void on_browseDirectoryButton_clicked();

    void on_actionNew_Signature_triggered();

    void trayIconActivated(QSystemTrayIcon::ActivationReason reason);

private:
    Ui::AntivirusWindow *ui;
    QSystemTrayIcon *mySysTrayIcon;
};
#endif // ANTIVIRUSWINDOW_H
