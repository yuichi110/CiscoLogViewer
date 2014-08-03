#include "core_wstabmanager.h"

const QString WsTabManager::WS_TAB_NAME = "ws";
const QString WsTabManager::MEMO_TAB_NAME = "memo";
const QString WsTabManager::SEARCH_TAB_NAME = "search";
const QString WsTabManager::ALL_COMMAND_TAB_NAME = "all commands";
const QString WsTabManager::NON_USED_COMMAND_TAB_NAME = "not categorized commands";


WsTabManager::WsTabManager(QObject *parent, MessageBroker *messageBroker) :
    QObject(parent)
{
    messageBroker_m = messageBroker;
    messageBroker_m->registerWsTabManager(this);

    initialized_m = false;
    memoWidget_m = NULL;
    allWidget_m = NULL;
    notSelectedWidget_m = NULL;
}

void WsTabManager::createWorkSpaceTab(QString clvFilePath){
    clvFilePath_m = clvFilePath;
    messageBroker_m->messageWsTabManager_addWsWidget(WS_TAB_NAME, MEMO_TAB_NAME, getMemoWidget());
    messageBroker_m->messageWsTabManager_enableSaveMenu();
    messageBroker_m->messageWsTabManager_addWsWidget(WS_TAB_NAME, SEARCH_TAB_NAME, new DeepSearchWidget(NULL, clvFilePath_m));
    messageBroker_m->messageWsTabManager_addWsWidget(WS_TAB_NAME, ALL_COMMAND_TAB_NAME, getCommandListWidget());
    messageBroker_m->messageWsTabManager_addWsWidget(WS_TAB_NAME, NON_USED_COMMAND_TAB_NAME, getNonUsedCommandListWidget());

    //load memo
    loadButtonClicked();
    initialized_m = true;
}

QWidget *WsTabManager::getMemoWidget(){
    if(memoWidget_m){
        return memoWidget_m;
    }

    memoWidget_m = new QWidget(NULL);
    QVBoxLayout *layout = new QVBoxLayout(memoWidget_m);
    memoArea_m = new QTextEdit(memoWidget_m);
    layout->addWidget(memoArea_m);
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->setAlignment(Qt::AlignRight);
    QPushButton *loadButton = new QPushButton("load", memoWidget_m);
    connect(loadButton, SIGNAL(clicked()), this, SLOT(loadButtonClicked()));
    loadButton->setFixedWidth(100);
    buttonLayout->addWidget(loadButton);
    QPushButton *saveButton = new QPushButton("save", memoWidget_m);
    connect(saveButton, SIGNAL(clicked()), this, SLOT(saveButtonClicked()));
    saveButton->setFixedWidth(100);
    buttonLayout->addWidget(saveButton);
    layout->addLayout(buttonLayout);
    memoWidget_m->setLayout(layout);

    return memoWidget_m;
}

QWidget *WsTabManager::getCommandListWidget(){
    if(allWidget_m != NULL){
        return allWidget_m;
    }

    ClvDataAccessor *accessor = new ClvDataAccessor(clvFilePath_m);
    accessor->open();
    QList<CommandGroupInfo> allList = accessor->getCommandGroupInfoList();
    accessor->close();
    allWidget_m = new CommandListWidget(NULL, allList, clvFilePath_m, true);

    return allWidget_m;
}

QWidget *WsTabManager::getNonUsedCommandListWidget(){
    if(notSelectedWidget_m != NULL){
        return notSelectedWidget_m;
    }

    ClvDataAccessor *accessor = new ClvDataAccessor(clvFilePath_m);
    accessor->open();
    QList<CommandGroupInfo> notSelectedList = accessor->getCommandGroupInfoListNone();
    accessor->close();
    notSelectedWidget_m = new CommandListWidget(NULL, notSelectedList, clvFilePath_m, false);

    return notSelectedWidget_m;
}

void WsTabManager::loadButtonClicked(){
    if(!initialized_m){
        return;
    }
    if(memoArea_m == NULL){
        return;
    }

    ClvDataAccessor *accessor = new ClvDataAccessor(clvFilePath_m);
    accessor->open();
    QString content = accessor->readMemo();
    accessor->close();
    memoArea_m->setPlainText(content);
}

void WsTabManager::saveButtonClicked(){
    if(!initialized_m){
        return;
    }
    if(memoArea_m == NULL){
        return;
    }

    QString content = memoArea_m->toPlainText();
    ClvDataAccessor *accessor = new ClvDataAccessor(clvFilePath_m);
    accessor->open();
    accessor->writeMemo(content);
    accessor->close();
}

