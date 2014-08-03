#ifndef LV_LOGEVENTMANAGER_H
#define LV_LOGEVENTMANAGER_H

#include <QObject>
#include "lv_commandloader.h"
#include "lv_logview.h"
#include "lv_logedit.h"
#include "lv_logsearchwidget.h"
#include "lv_logtreeview.h"
#include "lv_syntaxhighlighter.h"
#include "lv_highlightrule.h"
#include "lv_logwindow.h"

class CommandLoader;
class LogView;
class LogEdit;
class SyntaxHighlighter;
class HighlightRule;
class LogTreeView;
class LogSearchWidget;
class LogWindow;

class LogModel : public QObject
{
    Q_OBJECT
public:
    explicit LogModel(QObject *parent, QString layerName, QString groupName, QString clvPath, bool showPopupButton);

    // register
    void registerLogView(LogView *logView);
    void registerLogTreeView(LogTreeView *logTreeView);
    void registerLogSearchView(LogSearchWidget *logSearchView);
    void registerLogEdit(LogEdit *logEdit);
    void registerHighlighter(SyntaxHighlighter *highlighter);

    // tree
    void registerBookMark(int currentLine, QString line);
    void highlightCurrentTreeItem(int lineNum);
    void jumpToLine(int lineNumber);

    // search
    void forcusSearchBox();

    // general
    bool handleKeyPressEvent(QKeyEvent *e);
    void handleKeyReleaseEvent(QKeyEvent *e);
    bool isProhibitedCntKey(int key);

    // loader
    void loadLogs();
    void loadLogs(QList<int> idList);
    void unLoadLogs();
    bool isLoadingNow();

    // highlight
    void setHighlightRules(QList<HighlightRule> rules);

    // window
    void closeLogWindow();

protected:

private:
    // loader
    bool loadFinished_m;
    CommandLoader *loader_m;

    // view
    LogView *logView_m;
    LogTreeView *logTreeView_m;
    LogSearchWidget *logSearchView_m;
    LogEdit *logEdit_m;
    SyntaxHighlighter *highlighter_m;

    // window
    LogWindow *logWindow_m;

    // key flag
    bool flag_ControlKey_m;
    bool flag_MetaKey_m;
    bool flag_ShiftKey_m;

signals:

public slots:

    // loader
    void appendStringToEditer(QString line);
    void insertCommandToTreeWidget(int commandPosition, QString commandName, int startLineNum);
    void doneLoading();

    // search
    void popupLogWindow();
    void keywordChanged();
    void findForward();
    void findBackward();

    // tree

    // edit
};

#endif // LV_LOGEVENTMANAGER_H
