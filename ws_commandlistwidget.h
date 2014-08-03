#ifndef WS_COMMANDLISTWIDGET_H
#define WS_COMMANDLISTWIDGET_H

#include <QtGui>
#include "core_messagebroker.h"
#include "dao_commandgroupinfo.h"
#include "ws_onecommandwidget.h"

class CommandListWidget : public QWidget
{
    Q_OBJECT
public:
    CommandListWidget(QWidget *parent, QList<CommandGroupInfo> cgiList, QString clvFilePath, bool showGroupColumn);

private:
    QTreeWidget *commandView_m;
    QString clvFilePath_m;
    bool showGroupColumn_m;
    void loadCommandList(QList<CommandGroupInfo> cgiList);
    void resizeHeadersWidth();

protected:
    void resizeEvent(QResizeEvent *event);

signals:

public slots:
    void commandDoubleClicked();

};

#endif // WS_COMMANDLISTWIDGET_H
