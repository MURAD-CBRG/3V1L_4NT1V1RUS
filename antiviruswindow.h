#ifndef ANTIVIRUSWINDOW_H
#define ANTIVIRUSWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QSystemTrayIcon>
#include <QMessageBox>
#include <QMenu>
#include <QFileDialog>

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

private slots:
    void on_checkDirButton_clicked();

    void on_actionExit_triggered();

    void on_checkFileButton_clicked();

    void on_browseFileButton_clicked();

private:
    Ui::AntivirusWindow *ui;
    QSystemTrayIcon *mySysTrayIcon;
};
#endif // ANTIVIRUSWINDOW_H
