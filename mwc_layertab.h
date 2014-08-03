#ifndef MWC_LAYERTAB_H
#define MWC_LAYERTAB_H

#include <QtWidgets>
#include "core_messagebroker.h"

class MessageBroker;
class LayerTabWidget : public QTabWidget
{
    Q_OBJECT
public:
    explicit LayerTabWidget(QWidget *parent, MessageBroker *messageBroker);
    void addLogWidget(QString layerName, QString groupName, QWidget *logWidget);
    void setTabTextColor(QString layerName, QString groupName, Qt::GlobalColor color);
    void showLogWidget(QString layerName, QString groupName);
    void tabUp();
    void tabDown();
    void tabLeft();
    void tabRight();

private:
    QMap<QString, QTabWidget *> tabMap_m;
    MessageBroker *messageBroker_m;
    bool acceptIndexChangeFlag_m;

protected:

signals:

public slots:
    void currentTabChanged(int index);
};

#endif // MWC_LAYERTAB_H
