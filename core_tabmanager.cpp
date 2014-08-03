#include "core_tabmanager.h"


const int TabManager::RESOURCE_QUEUE_SIZE = 10;

TabManager::TabManager(QWidget *parent, MessageBroker *messageBroker) :
    QObject(parent)
{
    messageBroker_m = messageBroker;
    messageBroker_m->registerTabManager(this);  
}

void TabManager::createLayerAndGroupTab(QList<QString> layerList, QMap<QString, QList<QString> > layerMap, QString clvFilePath){

    // highlight rule map
    QMap<QString, QList<QString> > groupHighlightTextListMap;

    // check if group has commands
    ClvDataAccessor *accessor = new ClvDataAccessor(clvFilePath);
    accessor->open();
    QMap<QString, bool> groupExistMap;
    foreach(QString layer, layerList){
        QList<QString> groupList = layerMap.value(layer);
        foreach(QString group, groupList){
            groupExistMap.insert(group, accessor->hasCommand(group));
            groupHighlightTextListMap.insert(group, accessor->getHighlightTextList(group));
        }
    }
    accessor->close();

    // add groups if it has commands
    foreach(QString layer, layerList){
        if(!layerMap.contains(layer)){
            continue;
        }
        QList<QString> groupList = layerMap.value(layer);
        foreach(QString group, groupList){
            if(groupExistMap.value(group, false)){
                insertLogView(layer, group, clvFilePath, groupHighlightTextListMap);
            }
        }
    }
}

void TabManager::insertLogView(QString layerName, QString groupName, QString clvFilePath, QMap<QString, QList<QString> > groupHighlightTextListMap){
    LogView *logview = new LogView(NULL, layerName, groupName, clvFilePath, "", true, true);
    MainWindow *mainWindow = messageBroker_m->messageTabManager_getMainWindow();
    if(mainWindow != NULL){
        connect(mainWindow, SIGNAL(signalMainWindowClosed()), logview, SLOT(mainWindowClosed()));
    }

    if(groupHighlightTextListMap.contains(groupName)){
        QList<HighlightRule> highlightRuleList;
        QList<QString> highlightTextList = groupHighlightTextListMap.value(groupName);
        foreach(QString highlightText, highlightTextList){
            QTextCharFormat format;
            format.setForeground(QColor(Qt::red));
            HighlightRule rule(highlightText, format, false);
            highlightRuleList.append(rule);
        }
        logview->setHighlightRules(highlightRuleList);
    }
    messageBroker_m->messageTabManager_addLogWidget(layerName, groupName, logview);

    if(!logViewMap_m.contains(layerName)){
        QMap<QString, LogView*> map;
        logViewMap_m.insert(layerName, map);
    }
    QMap<QString, LogView*> map = logViewMap_m.value(layerName);
    map.insert(groupName, logview);
    logViewMap_m.insert(layerName, map);
}

void TabManager::tabIndexChanged(QString layerName, QString groupName){
    // get logview
    if(!logViewMap_m.contains(layerName)){
        return;
    }
    QMap<QString, LogView*> map = logViewMap_m.value(layerName);
    if(!map.contains(groupName)){
        return;
    }
    messageBroker_m->messageTabManager_tabChanged(layerName, groupName);


    LogView *logView = map.value(groupName);
    // check resouce isn't allocated.
    bool resourceAllocated = false;
    for(int i=0; i<layerShownQueue.length(); i++){
        QString layer = layerShownQueue.at(i);
        QString group = groupShownQueue.at(i);
        if(layerName == layer && groupName == group){
            resourceAllocated = true;
        }
    }
    if(resourceAllocated){
        // already allocated. do nothing
        qDebug() << "already allocated";
        return;
    }

    // allocate resouce to new logView.
    logView->loadLogs();
    messageBroker_m->messageTabManager_setTextColor(layerName, groupName, Qt::red);
    layerShownQueue.append(layerName);
    groupShownQueue.append(groupName);

    // allocated resouce isn't large. not deallocate resouce.
    if(layerShownQueue.length() <= RESOURCE_QUEUE_SIZE){
        qDebug() << "allocate only. queue size:" << layerShownQueue.length();
        return;
    }

    // already uses much resouces. deallocate oldest resouce.
    QString oldestLayerName = layerShownQueue.at(0);
    QString oldestGroupName = groupShownQueue.at(0);
    layerShownQueue.removeFirst();
    groupShownQueue.removeFirst();

    if(!logViewMap_m.contains(oldestLayerName)){
        return;
    }
    QMap<QString, LogView*> oldestMap = logViewMap_m.value(oldestLayerName);
    if(!oldestMap.contains(oldestGroupName)){
        return;
    }
    LogView *oldestLogView = oldestMap.value(oldestGroupName);
    oldestLogView->unLoadLogs();
    messageBroker_m->messageTabManager_setTextColor(oldestLayerName, oldestGroupName, Qt::black);
    qDebug() << "dealloc oldest resouce";
}

void TabManager::showCommand(QString command, QString layer, QString group){
    if(!logViewMap_m.contains(layer)){
        return;
    }
    QMap<QString, LogView*> layerMap = logViewMap_m.value(layer);
    if(!layerMap.contains(group)){
        return;
    }
    LogView *logView = layerMap.value(group);
    tabIndexChanged(layer, group);
    messageBroker_m->messageTabManager_showLogWidget(layer, group);
    logView->showCommand(command);
}
