#include "mwc_layertab.h"

LayerTabWidget::LayerTabWidget(QWidget *parent, MessageBroker *messageBroker) :
    QTabWidget(parent)
{
    messageBroker_m = messageBroker;
    messageBroker_m->registerLayerTab(this);
    setTabPosition(QTabWidget::West);
    acceptIndexChangeFlag_m = true;
    connect(this , SIGNAL(currentChanged(int)),this,SLOT(currentTabChanged(int)));
}

void LayerTabWidget::addLogWidget(QString layerName, QString groupName, QWidget *logWidget){
    if(!tabMap_m.contains(layerName)){
        QTabWidget *layerTab = new QTabWidget(this);
        connect(layerTab , SIGNAL(currentChanged(int)),this,SLOT(currentTabChanged(int)));
        tabMap_m.insert(layerName, layerTab);
        addTab(layerTab, layerName);
    }

    QTabWidget *layerTab = tabMap_m.value(layerName);
    layerTab->addTab(logWidget, groupName);
}

void LayerTabWidget::currentTabChanged(int index){
    if(!acceptIndexChangeFlag_m){
        return;
    }

    int layerIndex = currentIndex();
    QString layerName = tabText(layerIndex);
    QWidget *widget = currentWidget();
    QTabWidget *layerTab = qobject_cast<QTabWidget *>(widget);
    if(!layerTab) return;

    int groupIndex = layerTab->currentIndex();
    QString groupName = layerTab->tabText(groupIndex);

    messageBroker_m->messageLayerTab_tabChanged(layerName, groupName);
}

void LayerTabWidget::setTabTextColor(QString layerName, QString groupName, Qt::GlobalColor color){
    int layerIndex = -1;
    for(int i=0; i<count(); i++){
        if(layerName == tabText(i)){
            layerIndex = i;
        }
    }
    if(layerIndex < 0){
        return;
    }

    QTabWidget *layerTab = qobject_cast<QTabWidget *>(widget(layerIndex));
    if(!layerTab){
        return;
    }

    int groupIndex = -1;
    for(int i=0; i<layerTab->count(); i++){
        if(groupName == layerTab->tabText(i)){
            groupIndex = i;
        }
    }
    if(groupIndex < 0){
        return;
    }

    layerTab->tabBar()->setTabTextColor(groupIndex, color);
}

void LayerTabWidget::showLogWidget(QString layerName, QString groupName){
    int layerIndex = -1;
    for(int i=0; i<count(); i++){
        if(layerName == tabText(i)){
            layerIndex = i;
        }
    }
    if(layerIndex < 0){
        return;
    }

    QTabWidget *layerTab = qobject_cast<QTabWidget *>(widget(layerIndex));
    if(!layerTab){
        return;
    }

    int groupIndex = -1;
    for(int i=0; i<layerTab->count(); i++){
        if(groupName == layerTab->tabText(i)){
            groupIndex = i;
        }
    }
    if(groupIndex < 0){
        return;
    }

    acceptIndexChangeFlag_m = false;
    setCurrentIndex(layerIndex);
    acceptIndexChangeFlag_m = true;
    layerTab->setCurrentIndex(groupIndex);
}

void LayerTabWidget::tabUp(){
    if(count() == 0 || count() == 1){
        return;
    }

    int index = currentIndex();
    if(index == 0){
        setCurrentIndex(count() - 1);
    }else{
        setCurrentIndex(index - 1);
    }
}

void LayerTabWidget::tabDown(){
    if(count() == 0 || count() == 1){
        return;
    }

    int index = currentIndex();
    if(index == (count()-1)){
        setCurrentIndex(0);
    }else{
        setCurrentIndex(index + 1);
    }
}

void LayerTabWidget::tabLeft(){
    if(count() == 0){
        return;
    }

    QTabWidget *layerTab = qobject_cast<QTabWidget *>(currentWidget());
    if(!layerTab){
        return;
    }
    if(layerTab->count() == 0 || layerTab->count() == 1){
        return;
    }

    int index = layerTab->currentIndex();
    if(index == 0){
        layerTab->setCurrentIndex(layerTab->count() - 1);
    }else{
        layerTab->setCurrentIndex(index - 1);
    }
}

void LayerTabWidget::tabRight(){
    if(count() == 0){
        return;
    }

    QTabWidget *layerTab = qobject_cast<QTabWidget *>(currentWidget());
    if(!layerTab){
        return;
    }
    if(layerTab->count() == 0 || layerTab->count() == 1){
        return;
    }

    int index = layerTab->currentIndex();
    if(index == (layerTab->count() -1)){
        layerTab->setCurrentIndex(0);
    }else{
        layerTab->setCurrentIndex(index + 1);
    }
}
