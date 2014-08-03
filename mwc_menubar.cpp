
#include "mwc_menubar.h"

MenuBar::MenuBar(QWidget *parent, MessageBroker *messageBroker) :
    QMenuBar(parent)
{
    messageBroker_m = messageBroker;
    messageBroker_m->registerMenuBar(this);

    QMenu *prefMenu = addMenu("Preference");
    QAction *actionPreference = new QAction("Setting", parent);
    connect(actionPreference, SIGNAL(triggered()), this, SLOT(openPreferenceClicked()));
    prefMenu->addAction(actionPreference);
    QAction *actionAbout = new QAction("About CiscoLogViewer", parent);
    connect(actionAbout, SIGNAL(triggered()), this, SLOT(openAboutClicked()));
    prefMenu->addAction(actionAbout);

    // File
    QMenu *fileMenu = addMenu("File");
    QAction *fileMenu_New_m = new QAction("New Window", this);
    connect(fileMenu_New_m, SIGNAL(triggered()), this, SLOT(openNewWindow()));
    fileMenu->addAction(fileMenu_New_m);
    fileMenu_OpenFile_m = new QAction("Open CLV File", this);
    connect(fileMenu_OpenFile_m, SIGNAL(triggered()),this,SLOT(openClvFile()));
    fileMenu->addAction(fileMenu_OpenFile_m);
    fileMenu_SaveMemo_m = new QAction("Save Memo", this);
    connect(fileMenu_SaveMemo_m, SIGNAL(triggered()), this, SLOT(saveMemo()));
    fileMenu->addAction(fileMenu_SaveMemo_m);
    fileMenu_SaveMemo_m->setEnabled(false);


    // Window
    QMenu *windowMenu = addMenu("Window");
    QAction *actionMinimize = new QAction("Minimize", parent);
    connect(actionMinimize, SIGNAL(triggered()), this, SLOT(minimizeClicked()));
    windowMenu->addAction(actionMinimize);
    QAction *actionMaximize = new QAction("Maximize", this);
    connect(actionMaximize, SIGNAL(triggered()), this, SLOT(maximizeClicked()));
    windowMenu->addAction(actionMaximize);

    // Help
    QMenu *helpMenu = addMenu("Help");
    QAction *actionOpenHelp = new QAction("Open help page", parent);
    connect(actionOpenHelp, SIGNAL(triggered()), this, SLOT(openHelpPageClicked()));
    helpMenu->addAction(actionOpenHelp);
    QAction *actionReportNewBug = new QAction("Report new bug", parent);
    connect(actionReportNewBug, SIGNAL(triggered()), this, SLOT(reportNewBugClicked()));
    helpMenu->addAction(actionReportNewBug);
    QAction *actionContact = new QAction("Contact to author", parent);
    connect(actionContact, SIGNAL(triggered()), this, SLOT(contactToAuthorClicked()));
    helpMenu->addAction(actionContact);
    QAction *actionCheckUpdate = new QAction("Check software update", parent);
    connect(actionCheckUpdate, SIGNAL(triggered()), this, SLOT(checkSoftwareUpdateClicked()));
    helpMenu->addAction(actionCheckUpdate);
}

void MenuBar::enableSaveMenu(){
    fileMenu_SaveMemo_m->setEnabled(true);
}

void MenuBar::disableOpenMenu(){
    fileMenu_OpenFile_m->setEnabled(false);
}

/////////////
////  Preference
/////////////

void MenuBar::openPreferenceClicked(){
    if(AppInfo::DEBUG_MENUBAR) qDebug() << "MenuBar::openPreferenceClicked()";
    PreferenceWidget::getInstance()->show();
}

void MenuBar::openAboutClicked(){
    if(AppInfo::DEBUG_MENUBAR) qDebug() << "MenuBar::openAboutClicked()";
    AboutWidget::getInstance()->show();
}


/////////////
////  File
/////////////

void MenuBar::openNewWindow(){
    (new MainWindow())->show();
}

void MenuBar::openClvFile(){
    qDebug() << "new window";
    QString dirPath = QDir::homePath();
    QFileDialog fd(this, "Log Files", dirPath);
    fd.setFileMode(QFileDialog::ExistingFile);
    fd.setAcceptMode(QFileDialog::AcceptOpen);
    if(!fd.exec()){
        return;
    }

    QStringList slist = fd.selectedFiles();
    if(slist.size() != 1){
        return;
    }

    QString fileName = slist.at(0);
    if(!fileName.endsWith(".clv")){
        return;
    }

    if(!messageBroker_m->messageMenuBar_isFileOK(fileName)){
        return;
    }

    messageBroker_m->messageMenuBar_openClvFile(fileName);
}

void MenuBar::saveMemo(){
    qDebug() << "saveMemo";
    messageBroker_m->messageMenuBar_saveMemo();
}

/////////////
////  Window
/////////////

void MenuBar::minimizeClicked(){
    if(AppInfo::DEBUG_MENUBAR) qDebug() << "MenuBar::minimizeClicked()";
    QWidget *mainWindow = parentWidget();
    if(mainWindow->isMinimized()){
        mainWindow->showNormal();
    }else{
        mainWindow->showMinimized();
    }
}

void MenuBar::maximizeClicked(){
    if(AppInfo::DEBUG_MENUBAR) qDebug() << "MenuBar::maximizedClicked()";
    QWidget *mainWindow = parentWidget();
    if(mainWindow->isMaximized()){
        mainWindow->showNormal();
    }else{
        mainWindow->showMaximized();
    }
}


/////////////
////  Window
/////////////


void MenuBar::openHelpPageClicked(){
    if(AppInfo::DEBUG_MENUBAR) qDebug() << "MenuBar::openHelpPageClicked()";
    QDesktopServices::openUrl(AppInfo::WEB_PAGE_URL);
}

void MenuBar::reportNewBugClicked(){
    if(AppInfo::DEBUG_MENUBAR) qDebug() << "MenuBar::reportNewBugClicked()";
    QString url = QString(AppInfo::REPORT_BUG_URL).arg(AppInfo::MAIL_ADDRESS, QString::number(AppInfo::MAJOR_VERSION),
                                                       QString::number(AppInfo::MINOR_VERSION));
    qDebug() << url;
    url = url.replace(" ", "%20");
    qDebug() << url;
    QDesktopServices::openUrl(url);
}

void MenuBar::contactToAuthorClicked(){
    if(AppInfo::DEBUG_MENUBAR) qDebug() << "MenuBar::reportNewBugClicked()";
    QString url = QString(AppInfo::CONTACT_URL).arg(AppInfo::MAIL_ADDRESS);
    QDesktopServices::openUrl(url);
}

void MenuBar::checkSoftwareUpdateClicked(){
    if(AppInfo::DEBUG_MENUBAR) qDebug() << "MenuBar::checkSoftwareUpdateClicked()";

    // update file on the server has
    // X.Y
    // on top line.
    // where X is majorversion and Y is minorversion
    // the path is
    // http://DOMAIN/version/latest

    QString url = "http://clv.yuichi.com/version/latest";
    QEventLoop eventLoop;
    QNetworkAccessManager mgr;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    QNetworkReply *reply = mgr.get(QNetworkRequest(QUrl(url)));
    eventLoop.exec();

    if (reply->error() != QNetworkReply::NoError) {
        MessageBroker::showWarningMessage("Warning", "Unable to get version information from server.");
        return;
    }

    QString text = reply->readAll();
    QStringList slist = text.split("\n");
    QString versionText = slist.at(0);
    QRegExp regex("(\\d+)\\.(\\d+)");
    if(regex.indexIn(versionText) < 0){
        MessageBroker::showWarningMessage("Warning", "CLP can access to server. But unable to get version information.");
        return;
    }

    int majorVersion = regex.cap(1).toInt();
    int minorVersion = regex.cap(2).toInt();
    bool isLatest = true;
    if(majorVersion > AppInfo::MAJOR_VERSION){
        isLatest = false;
    }else if(majorVersion == AppInfo::MAJOR_VERSION){
        if(minorVersion > AppInfo::MINOR_VERSION){
            isLatest = false;
        }
    }

    if(isLatest){
        QString message = QString("You are using latest version.\nVersion: %1.%2").arg(QString::number(AppInfo::MAJOR_VERSION),
                                                                       QString::number(AppInfo::MINOR_VERSION));
        MessageBroker::showInformationMessage("OK", message);
    }else{
        QString message = QString("Your Application isn't latest.\nLatest version is %1.%2.").arg(QString::number(majorVersion),
                                                                                                 QString::number(minorVersion));
        MessageBroker::showWarningMessage("Warning", message);
    }
}




