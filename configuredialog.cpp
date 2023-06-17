#include "configuredialog.h"
#include "ui_configuredialog.h"

configureDialog::configureDialog(QWidget *parent) : QDialog(parent),
                                                    ui(new Ui::configureDialog)
{
    ui->setupUi(this);

    dirsEdit = findChild<QPlainTextEdit *>("dirsTextEdit");
    isonCheckbox = findChild<QCheckBox *>("isonCheckbox");
    timeintervalEdit = findChild<QSpinBox *>("timeintervalEdit");

    try
    {
        ConfigurationAnalyse conf = getConfigurationForAnalysis();
        isonCheckbox->setChecked(conf.work_flag);
        timeintervalEdit->setValue(conf.time_interval);
        std::string result = std::accumulate(conf.baseDirs.begin(), conf.baseDirs.end(), std::string(),
                                             [](const std::string &a, const std::string &b) -> std::string
                                             {
                                                 return a.empty() ? b : a + "\n" + b;
                                             });
        dirsEdit->setPlainText(QString::fromStdString(result));
    }
    catch (std::ofstream::failure)
    {
        QMessageBox::critical(this, "Error!", "Failed to read config file!");
    }

    QPushButton *cancelButton = findChild<QPushButton *>("cancelButton");
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

configureDialog::~configureDialog()
{
    delete ui;
}

void configureDialog::on_saveButton_clicked()
{
    bool mode = isonCheckbox->isChecked();
    int interval = timeintervalEdit->value();
    std::string dirs_str = dirsEdit->toPlainText().toStdString();
    std::vector<std::string> dirs;

    std::istringstream iss(dirs_str);
    std::string line;
    while (std::getline(iss, line))
        dirs.push_back(line);
    ConfigurationAnalyse conf{mode, interval, dirs};
    try
    {
        setConfigurationAnalysis(conf);
        accept();
    }
    catch (std::ofstream::failure)
    {
        QMessageBox::critical(this, "Error!", "Failed to create config file!");
        reject();
    }
}
