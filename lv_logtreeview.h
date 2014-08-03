#ifndef LV_LOGTREEVIEW_H
#define LV_LOGTREEVIEW_H

#include <QtWidgets>
#include "lv_logmodel.h"

class LogModel;
class LogTreeView : public QTreeWidget
{
    Q_OBJECT
public:
    explicit LogTreeView(QWidget *parent, LogModel *eventManager);
    void insertCommandToTreeWidget(int commandPosition, QString commandName, int startLineNum);
    void highlightCurrentTreeItem(int lineNum);
    void selectCommand(QString command);
    void clear();

protected:
    void resizeEvent(QResizeEvent *event);

private:
    LogModel *eventManager_m;
    QString group_m;

    QList<int> commandStartList_m;
    QList<int> commandEndList_m;
    int lastTreeHighlightIndex_m;
    void setTreeWidgetHeaderSize();

    QString tmp_jumpCommand_m;

signals:

public slots:
    void commandDoubleClicked();
    void selectCommand2();

};

#endif // LV_LOGTREEVIEW_H
