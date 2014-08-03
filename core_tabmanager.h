#ifndef TABMANAGER_H
#define TABMANAGER_H

#include <QtGui>
#include "core_messagebroker.h"
#include "lv_logview.h"
#include "mwc_mainwindow.h"

class MessageBroker;
class LogView;
class MainWindow;

class TabManager : public QObject
{
    Q_OBJECT

public:
    TabManager(QWidget *parent, MessageBroker *messageBroker);
    void createLayerAndGroupTab(QList<QString> layerList, QMap<QString, QList<QString> > layerMap, QString clvFilePath);
    void tabIndexChanged(QString layerName, QString groupName);
    void showCommand(QString command, QString layer, QString group);

private:
    void insertLogView(QString layerName, QString groupName, QString clvFilePath, QMap<QString, QList<QString> > groupHighlightTextListMap);

    static const int RESOURCE_QUEUE_SIZE;


    MessageBroker *messageBroker_m;

    // get logview from layer and group
    QMap<QString, QMap<QString, LogView*> > logViewMap_m;

    // resource allocation management queue
    QList<QString> layerShownQueue;
    QList<QString> groupShownQueue;

public slots:

};

#endif // TABMANAGER_H
