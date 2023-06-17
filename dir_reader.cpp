#include "dir_reader.h"

void read_dir(std::string dir, QTextEdit *redactor)
{
    try
    {
        std::vector<std::string> files = bypassDirectory(dir);
        for (std::string filename : files)
        {
            try
            {
                Signature sig1{filename};
                std::string sig_hash = sig1.get_hash();

                if (database_control(sig_hash, "FIND"))
                {
                    QString log = QString::fromStdString("<font color=\"red\">This file is virus: " + filename + "</font>");
                    redactor->append(log);
                }
                else
                {
                    QString log = QString::fromStdString("<font color=\"black\">This file is clear: " + filename + "</font>");
                    redactor->append(log);
                }
            }
            catch (std::ifstream::failure)
            {
                QString log = QString::fromStdString("<font color=\"orange\">No such file: " + filename + "</font>");
                redactor->append(log);
            }
            catch (std::invalid_argument)
            {
                QString log = QString::fromStdString("<font color=\"orange\">The file isn't exe: " + filename + "</font>");
                redactor->append(log);
            }
        }
    }
    catch (std::filesystem::__cxx11::filesystem_error)
    {
        QString log = QString::fromStdString("<font color=\"orange\">No directory: " + dir + "</font>");
        redactor->append(log);
    }
}
