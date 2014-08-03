#include "core_messagebroker.h"

MessageBroker::MessageBroker()
{
    mainWindow_m = NULL;
    menuBar_m = NULL;
    tabManager_m = NULL;
    wsTabManager_m = NULL;
    layerTabWidget_m = NULL;
    shortcutWidget_m = NULL;
    searchCommandWidget_m = NULL;
    clvLoader_m = NULL;
}

/////////////
///  Static
/////////////

void MessageBroker::showWarningMessage(QString title, QString contents){
    QMessageBox msgBox;
    msgBox.setWindowTitle(title);
    msgBox.warning(NULL, title, contents);
}

void MessageBroker::showInformationMessage(QString title, QString contents){
    QMessageBox msgBox;
    msgBox.setWindowTitle(title);
    msgBox.information(NULL, title, contents);
}

////////////////
/// REGISTER
////////////////

void MessageBroker::registerMainWindow(MainWindow *window){
    mainWindow_m = window;
}

void MessageBroker::registerMenuBar(MenuBar *menuBar){
    menuBar_m = menuBar;
}

void MessageBroker::registerLayerTab(LayerTabWidget *layerTab){
    layerTabWidget_m = layerTab;
}

void MessageBroker::registerTabManager(TabManager *tabManager){
    tabManager_m = tabManager;
}

void MessageBroker::registerWsTabManager(WsTabManager *wsTabManager){
    wsTabManager_m = wsTabManager;
}

void MessageBroker::registerClvLoader(ClvLoader *clvLoader){
    clvLoader_m = clvLoader;
}

void MessageBroker::registerShortcutWidget(ShortcutWidget *shortcutWidget){
    shortcutWidget_m = shortcutWidget;
}

void MessageBroker::registerSearchCommandWidget(SearchCommandWidget *searchCommandWidget){
    searchCommandWidget_m = searchCommandWidget;
}

////////////////
/// KEY
////////////////

void MessageBroker::messageKey_save(){
    messageMenuBar_saveMemo();
}

void MessageBroker::messageKey_newWindow(){
    (new MainWindow())->show();
}

void MessageBroker::messageKey_tabUp(){
    if(layerTabWidget_m != NULL){
        layerTabWidget_m->tabUp();
    }
}

void MessageBroker::messageKey_tabDown(){
    if(layerTabWidget_m != NULL){
        layerTabWidget_m->tabDown();
    }
}

void MessageBroker::messageKey_tabLeft(){
    if(layerTabWidget_m != NULL){
        layerTabWidget_m->tabLeft();
    }
}

void MessageBroker::messageKey_tabRight(){
    if(layerTabWidget_m != NULL){
        layerTabWidget_m->tabRight();
    }
}

void MessageBroker::messageKey_focusCommandSearch(){
    if(searchCommandWidget_m != NULL){
        searchCommandWidget_m->focusOnWidget();
    }
}

////////////////
/// CLV Loader
////////////////

void MessageBroker::messageClvLoader_createWsTab(QString clvFilePath){
    if(wsTabManager_m != NULL){
        wsTabManager_m->createWorkSpaceTab(clvFilePath);
    }else{

    }
}

void MessageBroker::messageClvLoader_createLayerAndGroupTab(QList<QString> layerList, QMap<QString, QList<QString> > layerMap, QString clvFilePath){
    if(tabManager_m != NULL){
        tabManager_m->createLayerAndGroupTab(layerList, layerMap, clvFilePath);
    }else{

    }
}

void MessageBroker::messageClvLoader_disableOpenMenu(){
    if(menuBar_m != NULL){
        menuBar_m->disableOpenMenu();
    }
}

////////////////
/// Tab Manager
////////////////

MainWindow *MessageBroker::messageTabManager_getMainWindow(){
    return mainWindow_m;
}

void MessageBroker::messageTabManager_addLogWidget(QString layerName, QString groupName, QWidget *logWidget){
    if(layerTabWidget_m != NULL){
        layerTabWidget_m->addLogWidget(layerName, groupName, logWidget);
    }

}

void MessageBroker::messageTabManager_setTextColor(QString layerName, QString groupName, Qt::GlobalColor color){
    if(layerTabWidget_m != NULL){
        layerTabWidget_m->setTabTextColor(layerName, groupName, color);
    }else{

    }
}

void MessageBroker::messageTabManager_tabChanged(QString layerName, QString groupName){
    if(shortcutWidget_m != NULL){
        shortcutWidget_m->addShortcutButton(layerName, groupName);
    }
}

void MessageBroker::messageTabManager_showLogWidget(QString layerName, QString groupName){
    if(layerTabWidget_m != NULL){
        layerTabWidget_m->showLogWidget(layerName, groupName);
    }
}

////////////////
/// Ws Tab Manager
////////////////

void MessageBroker::messageWsTabManager_addWsWidget(QString layerName, QString groupName, QWidget *wsWidget){
    if(layerTabWidget_m != NULL){
        layerTabWidget_m->addLogWidget(layerName, groupName, wsWidget);
    }else{

    }
}

void MessageBroker::messageWsTabManager_enableSaveMenu(){
    if(menuBar_m != NULL){
        menuBar_m->enableSaveMenu();
    }
}

////////////////
/// Layer Tab
////////////////

void MessageBroker::messageLayerTab_tabChanged(QString layerName, QString groupName){
    if(tabManager_m != NULL){
        tabManager_m->tabIndexChanged(layerName, groupName);
    }else{

    }

}

////////////////
/// Search Command
////////////////

bool MessageBroker::messageSearchCommand_loaded(){
    if(clvLoader_m == NULL){
        qDebug() << "CLV Loader isn't registered.";
        return false;
    }else{
        return clvLoader_m->getLoaded();
    }
}

QString MessageBroker::messageSearchCommand_getClvFilePath(){
    if(clvLoader_m == NULL){
        qDebug() << "CLV Loader isn't registered.";
        return "";
    }else{
        return clvLoader_m->getClvFilePath();
    }
}

void MessageBroker::messageSearchCommand_showCommand(QString command, QString layer, QString group){
    if(tabManager_m == NULL){
        qDebug() << command;
        qDebug() << layer << "," << group;
        return;
    }
    tabManager_m->showCommand(command, layer, group);
}


///////////
/// drop zone
///////////

bool MessageBroker::messageDropZone_isFileOK(QString filePath){
    if(clvLoader_m == NULL){
        qDebug() << "clvLoader isn't registered.";
        return false;
    }

    return clvLoader_m->checkClvFile(filePath);
}

void MessageBroker::messageDropZone_clvFileDropped(QString filePath){
    if(clvLoader_m == NULL){
        qDebug() << "clvLoader isn't registered.";
    }else{
        clvLoader_m->loadClvFile(filePath);
    }

    if(mainWindow_m == NULL){
        qDebug() << "mainWindow isn't registered.";
    }else{
        mainWindow_m->swapDZtoLayerTab();
    }
}

///////////
/// shortcut widget
///////////

void MessageBroker::messageShortcutWidget_showLogWidget(QString layerName, QString groupName){
    if(layerTabWidget_m != NULL){
        layerTabWidget_m->showLogWidget(layerName, groupName);
    }
}

///////////
/// menu bar
///////////

bool MessageBroker::messageMenuBar_isFileOK(QString filePath){
    if(clvLoader_m == NULL){
        qDebug() << "clvLoader isn't registered.";
        return false;
    }

    return clvLoader_m->checkClvFile(filePath);
}

void MessageBroker::messageMenuBar_openClvFile(QString filePath){
    messageDropZone_clvFileDropped(filePath);
}

void MessageBroker::messageMenuBar_saveMemo(){
    if(wsTabManager_m == NULL){
        qDebug() << "wsTabManager is not registered";
    }else{
       wsTabManager_m->saveButtonClicked();
    }
}
