#ifndef ANALIZERSEPARATED_H
#define ANALIZERSEPARATED_H

#include <QObject>
#include <QThread>
#include <QTextEdit>
#include <QMessageBox>
#include <iostream>
#include <vector>
#include <string>

#include "dir_reader.h"

/**
 * \brief A class for analyzing directories in a separate thread.
 *
 * This class provides a separate thread for analyzing directories at regular intervals. It takes
 * an interval in seconds at which to perform the analysis, a vector of directory paths to analyze,
 * and a pointer to a QTextEdit widget to display the results of the analysis.
 */
class analizerSeparated : public QObject  // EXAMPLE OF THREAD
{
public:
    /**
     * \brief Constructor for the analizerSeparated class.
     * \param interval_seconds The interval in seconds at which to perform the analysis.
     * \param dirs A vector of directory paths to analyze.
     * \param redactor A pointer to a QTextEdit widget to display the results of the analysis.
     *
     * This constructor initializes the member variables of the analizerSeparated class.
     */
    explicit analizerSeparated(int interval_in_seconds,
                               std::vector<std::string> dirs,
                               QTextEdit* redactor);

    /**
     * \brief Function for running the analysis in a separate thread.
     *
     * This function runs the analysis in a separate thread, looping through the specified directories
     * at regular intervals and displaying the results in the QTextEdit widget.
     */
    void analize_for_intervals();

private:
    int interval_seconds; /**< The interval in seconds at which to perform the analysis. */
    std::vector<std::string> dirs; /**< An array of directory paths to analyze. */
    QTextEdit* redactor; /**< QTextEdit to display the results of the analysis. */
};


#endif // ANALIZERSEPARATED_H
