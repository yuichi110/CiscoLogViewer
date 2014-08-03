#include "ws_progressdialog.h"

const QString ProgressDialog::INITIAL_TEXT = "";
const QString ProgressDialog::CANCEL_TEXT = "cancel";
const int ProgressDialog::MIN_PROGRESS = 0;
const int ProgressDialog::MAX_PROGRESS = 100;

ProgressDialog::ProgressDialog(QWidget *parent, DeepCommandSearcher *searcher) :
    QProgressDialog(INITIAL_TEXT, CANCEL_TEXT, MIN_PROGRESS, MAX_PROGRESS, parent)
{
    connect(searcher, SIGNAL(signalSetProgressMaximumValue(int)), this, SLOT(setProgressMaximum(int)));
    connect(searcher, SIGNAL(signalSetProgressValue(int)), this, SLOT(setProgressValue(int)));
    connect(searcher, SIGNAL(signalSetProgressString(QString)), this, SLOT(setProgressString(QString)));
    connect(searcher, SIGNAL(finished()), this, SLOT(searchFinished()));
}

void ProgressDialog::setProgressMaximum(int max){
    if(AppInfo::DEBUG_PROGRESS_DIALOG) qDebug() << "ProgressDialog::setProgressMaximum()";
    setMaximum(max);
}

void ProgressDialog::setProgressValue(int value){
    if(AppInfo::DEBUG_PROGRESS_DIALOG) qDebug() << "ProgressDialog::setProgressValue()";
    setValue(value);
}

void ProgressDialog::setProgressString(QString string){
    if(AppInfo::DEBUG_PROGRESS_DIALOG) qDebug() << "ProgressDialog::setProgressString()";
    setLabelText(string);
    update();
}

void ProgressDialog::progressCanceld(){
    if(AppInfo::DEBUG_PROGRESS_DIALOG) qDebug() << "ProgressDialog::progressCanceld()";

}

void ProgressDialog::searchFinished(){
    if(AppInfo::DEBUG_PROGRESS_DIALOG) qDebug() << "ProgressDialog::creationComplete()";
    close();
}
