#ifndef CONFIGTEXTVIEW_H
#define CONFIGTEXTVIEW_H

#include <QWidget>
#include <QtGui>
#include "core_messagebroker.h"
#include "lv_logmodel.h"
#include "lv_logedit.h"
#include "lv_logsearchwidget.h"
#include "lv_logtreeview.h"
#include "lv_commandloader.h"

class LogEventManager;
class LogEdit;
class LogTreeView;
class LogSearchWidget;
class LogView : public QWidget
{
    Q_OBJECT

private:
    LogModel *logEventManager_m;

public:
    explicit LogView(QWidget *parent, QString layerName, QString groupName, QString clvFilePath,
                     QString title, bool showTreeWidget, bool showPopupButton);
    //resource
    void loadLogs();
    void loadLogs(QList<int> idList);
    void unLoadLogs();
    //void loadSyntaxRule();
    void setHighlightRules(QList<HighlightRule> rules);
    void showCommand(QString command);

private:
    LogTreeView *logTreeView_m;

public slots:
    void mainWindowClosed();

};


#endif // CONFIGTEXTVIEW_H
