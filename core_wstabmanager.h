#ifndef CORE_WSTABMANAGER_H
#define CORE_WSTABMANAGER_H

#include <QtWidgets>
#include "core_messagebroker.h"
#include "lv_logview.h"
#include "ws_commandlistwidget.h"
#include "ws_deepsearchwidget.h"
#include "dao_commandgroupinfo.h"
#include "dao_clvdataaccessor.h"

class CommandListWidget;

class WsTabManager : public QObject
{
    Q_OBJECT
public:
    explicit WsTabManager(QObject *parent, MessageBroker *messageBroker);
    void createWorkSpaceTab(QString clvFilePath);

private:
    static const QString WS_TAB_NAME;
    static const QString MEMO_TAB_NAME;
    static const QString SEARCH_TAB_NAME;
    static const QString ALL_COMMAND_TAB_NAME;
    static const QString NON_USED_COMMAND_TAB_NAME;

    // core
    MessageBroker *messageBroker_m;
    QString clvFilePath_m;
    bool initialized_m;

    // memo
    QWidget *memoWidget_m;
    QTextEdit *memoArea_m;

    // all
    CommandListWidget *allWidget_m;

    // not selected
    CommandListWidget *notSelectedWidget_m;

    QWidget *getMemoWidget();
    QWidget *getCommandListWidget();
    QWidget *getNonUsedCommandListWidget();

signals:

public slots:
    void loadButtonClicked();
    void saveButtonClicked();

};

#endif // CORE_WSTABMANAGER_H
