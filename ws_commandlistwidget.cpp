#include "ws_commandlistwidget.h"

CommandListWidget::CommandListWidget(QWidget *parent, QList<CommandGroupInfo> cgiList, QString clvFilePath, bool showGroupColumn) :
    QWidget(parent)
{
    clvFilePath_m = clvFilePath;
    showGroupColumn_m = showGroupColumn;

    commandView_m = new QTreeWidget(this);
    if(showGroupColumn_m){
        commandView_m->setColumnCount(3);
        QStringList strList;
        strList << "Command" << "Layer" << "Group";
        commandView_m->setHeaderLabels(strList);
    }else{
        commandView_m->setColumnCount(1);
        commandView_m->header()->hide();
    }

    commandView_m->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    commandView_m->setContextMenuPolicy(Qt::ActionsContextMenu);
    connect(commandView_m, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(commandDoubleClicked()));

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(commandView_m);
    setLayout(mainLayout);
    resizeHeadersWidth();
    loadCommandList(cgiList);
}

void CommandListWidget::commandDoubleClicked(){
    QTreeWidgetItem *item = commandView_m->currentItem();
    if (!item) return;
    QString commandName = item->text(0);
    ClvDataAccessor *accessor = new ClvDataAccessor(clvFilePath_m);
    accessor->open();
    QByteArray data = accessor->getCommandData(commandName);
    accessor->close();
    if(data.length() == 0){
        return;
    }

    QString commandContents = QString(qUncompress(data));
    OneCommandWidget *ocw = new OneCommandWidget(NULL, commandName, commandContents);
    ocw->show();

}

void CommandListWidget::loadCommandList(QList<CommandGroupInfo> cgiList){
    commandView_m->clear();
    foreach(CommandGroupInfo cgi, cgiList){
        QTreeWidgetItem *item = new QTreeWidgetItem(commandView_m);
        item->setText(0, cgi.getCommand());
        if(showGroupColumn_m){
            item->setText(1, cgi.getLayer());
            item->setText(2, cgi.getGroup());
        }
    }
    commandView_m->setCurrentItem(commandView_m->topLevelItem(0));
}

void CommandListWidget::resizeEvent(QResizeEvent *event){
    QWidget::resizeEvent(event);
    resizeHeadersWidth();
}

void CommandListWidget::resizeHeadersWidth(){
    if(showGroupColumn_m){
        int width = commandView_m->size().width();
        commandView_m->header()->resizeSection(0, width - 160);
        commandView_m->header()->resizeSection(1, 80);
        commandView_m->header()->resizeSection(2, 80);
    }
}
