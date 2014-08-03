#include "lv_logtreeview.h"

LogTreeView::LogTreeView(QWidget *parent, LogModel *eventManager) :
    QTreeWidget(parent)
{
    eventManager_m = eventManager;
    eventManager_m->registerLogTreeView(this);

    QStringList strList;
    strList << "Command" << "Line";
    setHeaderLabels(strList);
    setColumnCount(2);
    setMinimumWidth(160);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setContextMenuPolicy(Qt::ActionsContextMenu);
    connect(this, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(commandDoubleClicked()));
    clear();
}

void LogTreeView::clear(){
    commandStartList_m.clear();
    commandEndList_m.clear();
    lastTreeHighlightIndex_m = -1;
    QTreeWidget::clear();
}

void LogTreeView::insertCommandToTreeWidget(int commandPosition, QString commandName, int startLineNum){
    QTreeWidgetItem *item = new QTreeWidgetItem;
    item->setText(0, commandName);
    item->setText(1, QString::number(startLineNum));
    insertTopLevelItem(commandPosition, item);

    commandStartList_m.append(startLineNum);
    if(commandStartList_m.length() != 1){
        commandEndList_m.append(startLineNum);
    }
}

void LogTreeView::highlightCurrentTreeItem(int lineNum){
    int size = commandStartList_m.length();
    int hitIndex = -1;
    for(int i=0; i<size; i++){
        if(i==size-1){
            int start = commandStartList_m.at(i);
            if(start <= lineNum){
                hitIndex = i;
            }
        }else{
            int start = commandStartList_m.at(i);
            int end = commandEndList_m.at(i);
            if(start <= lineNum && lineNum < end){
                hitIndex = i;
                break;
            }
        }
    }

    if(hitIndex != lastTreeHighlightIndex_m){
        if(size > 0 && (0<=lastTreeHighlightIndex_m && lastTreeHighlightIndex_m<size)){
            QTreeWidgetItem *item = topLevelItem(lastTreeHighlightIndex_m);
            if(item){
                item->setForeground(0, QBrush(Qt::black));
            }
        }

        QTreeWidgetItem *item = topLevelItem(hitIndex);
        if(item){
            item->setForeground(0, QBrush(Qt::red));
        }
        lastTreeHighlightIndex_m = hitIndex;
    }
}

void LogTreeView::commandDoubleClicked(){
    QTreeWidgetItem *item = currentItem();
    QString strLine = item->text(1);
    int lineNum = strLine.toInt();
    eventManager_m->jumpToLine(lineNum);
}

void LogTreeView::selectCommand(QString command){
    tmp_jumpCommand_m = command;
    if(eventManager_m->isLoadingNow()){
        QTimer::singleShot(100, this, SLOT(selectCommand2()));
    }else{
        selectCommand2();
    }
}

void LogTreeView::selectCommand2(){
    if(eventManager_m->isLoadingNow()){
        QTimer::singleShot(100, this, SLOT(selectCommand2()));
    }else{
        for(int i=0; i<topLevelItemCount(); i++){
            QTreeWidgetItem *item = topLevelItem(i);
            QString treeCommand = item->text(0);
            qDebug() << treeCommand;

            if(tmp_jumpCommand_m == treeCommand){
                QString strLine = item->text(1);
                int lineNum = strLine.toInt();
                eventManager_m->jumpToLine(lineNum);
                break;
            }
        }
    }

}

void LogTreeView::setTreeWidgetHeaderSize(){
    int width = size().width();
    header()->resizeSection(0, width - 100);
}

void LogTreeView::resizeEvent(QResizeEvent *event){
    QTreeWidget::resizeEvent(event);
    setTreeWidgetHeaderSize();
}
