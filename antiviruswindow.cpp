#include "antiviruswindow.h"
#include "./ui_antiviruswindow.h"

AntivirusWindow::AntivirusWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AntivirusWindow)
{
    ui->setupUi(this);
    mySysTrayIcon = new QSystemTrayIcon(this);
    QMenu* trayMenu = new QMenu(this);

    trayMenu->addAction("Open", this, &AntivirusWindow::showNormal);
    trayMenu->addAction("Quit", this, &AntivirusWindow::close);

    mySysTrayIcon->setContextMenu(trayMenu);
    mySysTrayIcon->setIcon(QIcon(":/sprites/anti.png"));
    connect(mySysTrayIcon, &QSystemTrayIcon::activated, this, &AntivirusWindow::trayIconActivated);

    mySysTrayIcon->setVisible(true);



    // init auto checker
    try{
        ConfigurationAnalyse conf = getConfigurationForAnalysis();
        if(conf.work_flag){
            QThread* thread = new QThread(this);
            analizerSeparated* t1 = new analizerSeparated("t1", conf.time_interval, conf.baseDirs);
            t1->moveToThread(thread);
            connect(thread, &QThread::started, t1, &analizerSeparated::do_something);

            // Start the thread
            thread->start();
        }
    }
    catch(std::fstream::failure){
        std::cout<<"No conf file!"<<std::endl;
    }
}

AntivirusWindow::~AntivirusWindow()
{
    QList<QThread*> threads = findChildren<QThread*>();
    for (QThread* thread : threads) {
        thread->requestInterruption();
        thread->quit();
        thread->wait();
    }
    delete ui;
}


void AntivirusWindow::on_checkDirButton_clicked()
{
    QLineEdit* lineEdit = this->findChild<QLineEdit*>("dirnameLine");
    QTextEdit* textEdit = this->findChild<QTextEdit*>("logging");
    QString dirname = lineEdit->text();
    std::vector<std::string> files = bypassDirectory(dirname.toStdString());
    for(auto filename: files){
        try{
            Signature sig1{filename};
            std::string sig_hash = sig1.get_hash();

            if(database_control(sig_hash, "FIND"))
                textEdit->append(tr("<font color=\"red\">This file is a virus ") +
                                          QString::fromStdString(filename) + tr("</font>"));
            else
                textEdit->append(tr("This file is clear ") +
                                          QString::fromStdString(filename));
        }
        catch(std::ifstream::failure){
            QMessageBox::critical(this, "No such file!", "Can't check that file!\n" + QString::fromStdString(filename));
        }
        catch(std::invalid_argument){
            QMessageBox::information(this, "Not exe!", "This file is not EXE!\n" + QString::fromStdString(filename));
        }
    }
}


void AntivirusWindow::on_actionExit_triggered()
{
    QCoreApplication::quit();
}


void AntivirusWindow::on_checkFileButton_clicked()
{
    QLineEdit* lineEdit = this->findChild<QLineEdit*>("filenameLine");
    QTextEdit* textEdit = this->findChild<QTextEdit*>("logging");
    QString filename = lineEdit->text();
    try{
        Signature sig1{filename.toStdString()};
        std::string sig_hash = sig1.get_hash();
        QMessageBox::information(this, "Hash", tr("The hash is ") + tr(sig_hash.c_str()));
        if(database_control(sig_hash, "FIND"))
            textEdit->append(tr("<font color=\"red\">This file is a virus ") + filename + tr("</font>"));
        else
            textEdit->append(tr("This file is clear ") + filename);
    }
    catch(std::ifstream::failure){
        QMessageBox::critical(this, "No such file!", "Can't check that file!");
    }
}


void AntivirusWindow::on_browseFileButton_clicked()
{
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this,
                                            tr("Choose File for checking"),
                                            "",
                                            tr("Executable files (*.exe)") //tr("text files (*.txt);; png files (*.png)")
                                            );
    if (!fileName.isNull())
    {
        QLineEdit* lineEdit = this->findChild<QLineEdit*>("filenameLine");
        lineEdit->setText(fileName);
    }
}


void AntivirusWindow::on_browseDirectoryButton_clicked()
{
    QString dirName;
    dirName = QFileDialog::getExistingDirectory(this, tr("Choose directory for checking"), "");

    if (!dirName.isNull())
    {
        QLineEdit* lineEdit = this->findChild<QLineEdit*>("dirnameLine");
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

void AntivirusWindow::closeEvent(QCloseEvent* event)
{
    if (mySysTrayIcon->isVisible()) {
        hide();
    } else {
        QMainWindow::closeEvent(event);
    }
}

void AntivirusWindow::changeEvent(QEvent* event)
{
    if (event->type() == QEvent::WindowStateChange) {
        if (isMinimized()) {
            hide();
        }
    }
    QMainWindow::changeEvent(event);
}
