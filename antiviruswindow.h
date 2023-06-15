#ifndef ANTIVIRUSWINDOW_H
#define ANTIVIRUSWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class AntivirusWindow; }
QT_END_NAMESPACE

class AntivirusWindow : public QMainWindow
{
    Q_OBJECT

public:
    AntivirusWindow(QWidget *parent = nullptr);
    ~AntivirusWindow();

private:
    Ui::AntivirusWindow *ui;
};
#endif // ANTIVIRUSWINDOW_H
