#ifndef MESSAGEBROKER_H
#define MESSAGEBROKER_H

#include <QMap>
#include "mwc_mainwindow.h"
#include "mwc_menubar.h"
#include "mwc_layertab.h"
#include "core_tabmanager.h"
#include "core_wstabmanager.h"
#include "lv_highlightrule.h"
#include "ws_shortcutwidget.h"
#include "ws_searchcommandwidget.h"

class MainWindow;
class MenuBar;
class ConfigTextView;
class TabManager;
class LayerTabWidget;
class WsTabManager;
class ShortcutWidget;
class ClvLoader;
class SearchCommandWidget;

class MessageBroker
{
public:
    MessageBroker();

    // static
    static void showWarningMessage(QString title, QString contents);
    static void showInformationMessage(QString title, QString contents);

    // register
    void registerMainWindow(MainWindow *window);
    void registerMenuBar(MenuBar *menuBar);
    void registerLayerTab(LayerTabWidget *layerTabWidget);
    void registerTabManager(TabManager *tabManager);
    void registerWsTabManager(WsTabManager *wsTabManager);
    void registerClvLoader(ClvLoader *clvLoader);
    void registerShortcutWidget(ShortcutWidget *shortcutWidget);
    void registerSearchCommandWidget(SearchCommandWidget *searchCommandWidget);


    // mainwindow
    void messageKey_save();
    void messageKey_newWindow();
    void messageKey_tabUp();
    void messageKey_tabDown();
    void messageKey_tabLeft();
    void messageKey_tabRight();
    void messageKey_focusCommandSearch();

    // clvLoader
    void messageClvLoader_createWsTab(QString clvFilePath);
    void messageClvLoader_createLayerAndGroupTab(QList<QString> layerList, QMap<QString, QList<QString> > layerMap, QString clvFilePath);
    void messageClvLoader_disableOpenMenu();

    // tabManager
    MainWindow *messageTabManager_getMainWindow();
    void messageTabManager_addLogWidget(QString layerName, QString groupName, QWidget *logWidget);
    void messageTabManager_setTextColor(QString layerName, QString groupName, Qt::GlobalColor color);
    void messageTabManager_tabChanged(QString layerName, QString groupName);
    void messageTabManager_showLogWidget(QString layerName, QString groupName);

    // wsTabManager
    void messageWsTabManager_addWsWidget(QString layerName, QString groupName, QWidget *wsWidget);
    void messageWsTabManager_enableSaveMenu();

    // layerTab
    void messageLayerTab_tabChanged(QString layerName, QString groupName);

    // search command
    bool messageSearchCommand_loaded();
    QString messageSearchCommand_getClvFilePath();
    void messageSearchCommand_showCommand(QString command, QString layer, QString group);

    // dropzone
    bool messageDropZone_isFileOK(QString filePath);
    void messageDropZone_clvFileDropped(QString filePath);

    // shortcut widget
    void messageShortcutWidget_showLogWidget(QString layerName, QString groupName);

    // menubar
    bool messageMenuBar_isFileOK(QString filePath);
    void messageMenuBar_openClvFile(QString filePath);
    void messageMenuBar_saveMemo();

private:
    MainWindow *mainWindow_m;
    MenuBar *menuBar_m;
    TabManager *tabManager_m;
    WsTabManager *wsTabManager_m;
    LayerTabWidget *layerTabWidget_m;
    ShortcutWidget *shortcutWidget_m;
    SearchCommandWidget *searchCommandWidget_m;
    ClvLoader *clvLoader_m;

};

#endif // MESSAGEBROKER_H
