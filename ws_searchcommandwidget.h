#ifndef SHORTCUTTABWIDGET_H
#define SHORTCUTTABWIDGET_H

#include <QtGui>
#include <QtWidgets>
#include "core_appinfo.h"
#include "core_messagebroker.h"
#include "ws_onecommandwidget.h"

class SearchCommandWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SearchCommandWidget(QWidget *parent, MessageBroker *messageBroker);
    void loadCommandList(QList<QString> commandList, QList<QString> layerList, QList<QString> groupList);
    void focusOnWidget();

private:
    static const QString GROUP_NONE_KEYWORD;
    MessageBroker *messageBroker_m;
    QList<QString> commandList_m;
    QList<QString> layerList_m;
    QList<QString> groupList_m;

    QHBoxLayout *hbox_m;
    QLineEdit *lineEdit_m;
    QTreeWidget *popup;
    QTimer *timer;

    void showCompletion(QList<QString> commandList, QList<QString> tabList);
    bool handlePopupEvent(QEvent *event);

protected:
    bool eventFilter(QObject *obj, QEvent *event);

signals:

public slots:
    void doneCompletion();
    void runSuggest();

};

#endif // SHORTCUTTABWIDGET_H
