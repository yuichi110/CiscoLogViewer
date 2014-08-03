#ifndef MWC_PROGRESSDIALOG_H
#define MWC_PROGRESSDIALOG_H

#include <QtGui>
#include <QtWidgets>
#include "core_appinfo.h"
#include "ws_deepcommandsearcher.h"

class ProgressDialog : QProgressDialog
{
    Q_OBJECT
public:
    ProgressDialog(QWidget *parent, DeepCommandSearcher *searcher);

private:
    static const QString INITIAL_TEXT;
    static const QString CANCEL_TEXT;
    static const int MIN_PROGRESS;
    static const int MAX_PROGRESS;

private slots:
    void setProgressMaximum(int max);
    void setProgressValue(int value);
    void setProgressString(QString string);
    void progressCanceld();
    void searchFinished();
};

#endif // MWC_PROGRESSDIALOG_H
