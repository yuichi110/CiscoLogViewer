#include "lv_logview.h"

LogView::LogView(QWidget *parent, QString layerName, QString groupName, QString clvFilePath,
                 QString title, bool showTreeWidget, bool showPopupButton) :
    QWidget(parent)
{
    logEventManager_m = new LogModel(this, layerName, groupName, clvFilePath, showPopupButton);

    QVBoxLayout *layout = new QVBoxLayout();
    if(title != ""){
        QLabel *label = new QLabel(this);
        label->setText(title);
        label->setMaximumHeight(20);
        label->setTextInteractionFlags(Qt::TextSelectableByMouse);
        layout->addWidget(label);
    }

    LogSearchWidget *logSearchWidget = new LogSearchWidget(this, logEventManager_m, showPopupButton);
    layout->addWidget(logSearchWidget);

    if(!showTreeWidget){
        LogEdit *logEdit = new LogEdit(this, logEventManager_m);
        layout->addWidget(logEdit);
    }else{
        logTreeView_m = new LogTreeView(this, logEventManager_m);
        LogEdit *logEdit = new LogEdit(this, logEventManager_m);

        QSplitter *splitter = new QSplitter();
        splitter->setOpaqueResize(false);
        splitter->addWidget(logTreeView_m);
        splitter->addWidget(logEdit);

        int splitterWidth = splitter->size().width();
        QList<int> sizeList;
        sizeList.append(splitterWidth/3);        //  tree:1/3
        sizeList.append(splitterWidth * 2 / 3);  //  editer:2/3
        splitter->setSizes(sizeList);
        layout->addWidget(splitter);
    }

    setLayout(layout);
}

void LogView::loadLogs(){
    logEventManager_m->loadLogs();
}

void LogView::loadLogs(QList<int> idList){
    logEventManager_m->loadLogs(idList);
}

void LogView::unLoadLogs(){
    logEventManager_m->unLoadLogs();
}

void LogView::setHighlightRules(QList<HighlightRule> rules){
    logEventManager_m->setHighlightRules(rules);
}

void LogView::showCommand(QString command){
    logTreeView_m->selectCommand(command);
}

void LogView::mainWindowClosed(){
    if(logEventManager_m != NULL){
        logEventManager_m->closeLogWindow();
    }
}
