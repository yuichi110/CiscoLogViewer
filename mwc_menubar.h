#ifndef MWC_MAINMENU_H
#define MWC_MAINMENU_H

#include <QtWidgets>
#include <QtNetwork>
#include "core_messagebroker.h"
#include "mwc_mainwindow.h"
#include "pref_preferencewidget.h"
#include "window_aboutwidget.h"

class MessageBroker;

class MenuBar : public QMenuBar
{
    Q_OBJECT
public:
    explicit MenuBar(QWidget *parent, MessageBroker *messageBroker);
    void enableSaveMenu();
    void disableOpenMenu();

private:
    MessageBroker *messageBroker_m;
    QAction *fileMenu_OpenFile_m;
    QAction *fileMenu_SaveMemo_m;

signals:

private slots:
    //preference
    void openPreferenceClicked();
    void openAboutClicked();

    // file
    void openNewWindow();
    void openClvFile();
    void saveMemo();

    // window
    void minimizeClicked();
    void maximizeClicked();

    // help
    void openHelpPageClicked();
    void reportNewBugClicked();
    void contactToAuthorClicked();
    //void updateCategorizeRuleClicked();
    void checkSoftwareUpdateClicked();
};


#endif // MWC_MAINMENU_H
