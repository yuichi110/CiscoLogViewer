#include "lv_logwindow.h"

//const bool LogWindow::DEBUG = false;

LogWindow::LogWindow(QWidget *parent, QString clvFilePath, QString layerName, QString groupName) :
    QMainWindow(parent)
{
    setWindowIcon(QIcon(AppInfo::APP_ICON));
    setMinimumSize(600, 300);

    QString title = QString("%1/%2 : %3").arg(layerName, groupName, AppInfo::APP_NAME);
    setWindowTitle(title);

    logview_m = new LogView(this, layerName, groupName, clvFilePath, "", true, false);
    setCentralWidget(logview_m);
}

void LogWindow::showWindow(){
    logview_m->loadLogs();
    show();
}

void LogWindow::receiveMainWindowCloseSignal(){
    logview_m->unLoadLogs();
    close();
}

void LogWindow::closeEvent(QCloseEvent *e){
    logview_m->unLoadLogs();
    QMainWindow::closeEvent(e);
}

