#include "antiviruswindow.h"
#include "./ui_antiviruswindow.h"

AntivirusWindow::AntivirusWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::AntivirusWindow)
{
    ui->setupUi(this);
    mySysTrayIcon = new QSystemTrayIcon(this);
    QMenu *trayMenu = new QMenu(this);

    trayMenu->addAction("Open", this, &AntivirusWindow::showNormal);
    trayMenu->addAction("Quit", this, &AntivirusWindow::close);

    mySysTrayIcon->setContextMenu(trayMenu);
    mySysTrayIcon->setIcon(QIcon(":/sprites/anti.png"));
    connect(mySysTrayIcon, &QSystemTrayIcon::activated, this, &AntivirusWindow::trayIconActivated);

    mySysTrayIcon->setVisible(true);

    autoanalyzerThread = new QThread(this);
    // init auto checker
    autocheck_on();
}

AntivirusWindow::~AntivirusWindow()
{
    autoanalyzerThread->requestInterruption();
    autoanalyzerThread->quit();
    autoanalyzerThread->wait();
    mySysTrayIcon->hide();
    delete mySysTrayIcon;
    delete ui;
}

void AntivirusWindow::on_checkDirButton_clicked()
{
    QLineEdit *lineEdit = this->findChild<QLineEdit *>("dirnameLine");
    QTextEdit *textEdit = this->findChild<QTextEdit *>("logging");
    read_dir(lineEdit->text().toStdString(), textEdit);
}

void AntivirusWindow::on_actionExit_triggered()
{
    QCoreApplication::quit();
}

void AntivirusWindow::on_checkFileButton_clicked()
{
    QLineEdit *lineEdit = this->findChild<QLineEdit *>("filenameLine");
    QTextEdit *textEdit = this->findChild<QTextEdit *>("logging");
    QString filename = lineEdit->text();
    try
    {
        Signature sig1{filename.toStdString()};
        std::string sig_hash = sig1.get_hash();
        QMessageBox::information(this, "Hash", tr("The hash is ") + tr(sig_hash.c_str()));
        if (database_control(sig_hash, "FIND")){
            textEdit->append(tr("<font color=\"red\">This file is a virus ") + filename + tr("</font>"));
            // std::filesystem::path p(filename.toStdString());
            // std::filesystem::remove(p);
        }
        else
            textEdit->append(QString::fromStdString("<font color=\"black\">This file is clear: " +
                                                    filename.toStdString() + "</font>"));
    }
    catch (std::ifstream::failure)
    {
        QMessageBox::critical(this, "No such file!", "Can't check that file!");
    }
}

void AntivirusWindow::on_browseFileButton_clicked()
{
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this,
                                            tr("Choose File for checking"),
                                            "",
                                            tr("Executable files (*.exe)") // tr("text files (*.txt);; png files (*.png)")
    );
    if (!fileName.isNull())
    {
        QLineEdit *lineEdit = this->findChild<QLineEdit *>("filenameLine");
        lineEdit->setText(fileName);
    }
}

void AntivirusWindow::on_browseDirectoryButton_clicked()
{
    QString dirName;
    dirName = QFileDialog::getExistingDirectory(this, tr("Choose directory for checking"), "");

    if (!dirName.isNull())
    {
        QLineEdit *lineEdit = this->findChild<QLineEdit *>("dirnameLine");
        lineEdit->setText(dirName);
    }
}

void AntivirusWindow::on_actionNew_Signature_triggered()
{
    addFIleToDBDialog new_file_dialog(this);
    new_file_dialog.exec();
}

void AntivirusWindow::trayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::DoubleClick)
        showNormal();
}

void AntivirusWindow::closeEvent(QCloseEvent *event)
{
    if (mySysTrayIcon->isVisible())
    {
        hide();
    }
    else
    {
        QMainWindow::closeEvent(event);
    }
}

void AntivirusWindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::WindowStateChange)
    {
        if (isMinimized())
        {
            hide();
        }
    }
    QMainWindow::changeEvent(event);
}

void AntivirusWindow::on_actionSettings_triggered()
{
    configureDialog confDialog(this);
    if (confDialog.exec() == QDialog::Accepted)
    {
        autoanalyzerThread->requestInterruption();
        autoanalyzerThread->quit();

        autocheck_on();
    }
}

void AntivirusWindow::autocheck_on()
{
    try
    {
        ConfigurationAnalyse conf = getConfigurationForAnalysis();
        if (conf.work_flag)
        {
            QTextEdit *main_log = findChild<QTextEdit *>("logging");
            analizerSeparated *analizer = new analizerSeparated(conf.time_interval, conf.baseDirs, main_log);
            analizer->moveToThread(autoanalyzerThread);
            connect(autoanalyzerThread, &QThread::started, analizer, &analizerSeparated::analize_for_intervals);

            // Start the thread
            autoanalyzerThread->start();
        }
    }
    catch (std::fstream::failure)
    {
        QMessageBox::critical(this, "Error!", "Autocheck can't be run because there is no conf file!");
    }
}
