#ifndef ADDFILETODBDIALOG_H
#define ADDFILETODBDIALOG_H

#include <QDialog>
#include <QFileDialog>

namespace Ui {
class addFIleToDBDialog;
}

class addFIleToDBDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addFIleToDBDialog(QWidget *parent = nullptr);
    ~addFIleToDBDialog();

private slots:
    void on_browseButton_clicked();

    void on_addButton_clicked();

    void on_removeButton_clicked();

private:
    Ui::addFIleToDBDialog *ui;
};

#endif // ADDFILETODBDIALOG_H
