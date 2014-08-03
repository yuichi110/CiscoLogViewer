#include "ws_shortcutwidget.h"

const int ShortcutWidget::BUTTON_WIDTH = 60;
const int ShortcutWidget::BUTTON_SPACE = 10;
const int ShortcutWidget::MARGIN = 30;

ShortcutWidget::ShortcutWidget(QWidget *parent, MessageBroker *messageBroker) :
    QWidget(parent)
{
    messageBroker_m = messageBroker;
    messageBroker_m->registerShortcutWidget(this);

    layout_m = new QHBoxLayout(this);
    layout_m->setContentsMargins(MARGIN/3, 0, MARGIN/3, 0);
    layout_m->setSpacing(BUTTON_SPACE);
    layout_m->setAlignment(Qt::AlignLeft);
    setLayout(layout_m);
}

int ShortcutWidget::getIndexOfSameContents(QString layer, QString group){
    for(int i=0; i<layout_m->count(); i++){
        QLayoutItem *item = layout_m->itemAt(i);
        if(!item->widget()) continue;
        ShortcutButton *scb = qobject_cast<ShortcutButton*>(item->widget());
        if(scb==NULL) continue;

        bool sameLayer = (layer == scb->getLayer());
        bool sameGroup = (group == scb->getGroup());
        if(sameLayer && sameGroup){
            return i;
        }
    }

    return -1;
}

void ShortcutWidget::addShortcutButton(QString layer, QString group){
    for(int i=0; i<oldLayerList_m.length(); i++){
        bool sameLayer = (layer == oldLayerList_m.at(i));
        bool sameGroup = (group == oldGroupList_m.at(i));
        if(sameLayer && sameGroup){
            oldLayerList_m.removeAt(i);
            oldGroupList_m.removeAt(i);
            oldLayerList_m.append(layer);
            oldGroupList_m.append(group);
            return;
        }
    }

    // create button
    ShortcutButton *button = new ShortcutButton(this, layer, group);
    QString text = QString("%1/%2").arg(layer.mid(0, 3), group.mid(0, 3));
    button->setText(text);
    button->setFixedWidth(BUTTON_WIDTH);
    button->installEventFilter(this);

    // check size
    int n = oldLayerList_m.length() + 1;
    int sumButtonWidth = BUTTON_WIDTH * n + BUTTON_SPACE * (n-1);
    sumButtonWidth += MARGIN;

    if(this->width() > sumButtonWidth){
        // add new
        layout_m->addWidget(button);

    }else{
        if(oldLayerList_m.size() == 0){
            // too small do nothing.
            return;
        }
        // location
        QString oldLayer = oldLayerList_m.first();
        QString oldGroup = oldGroupList_m.first();
        int deleteIndex = getIndexOfSameContents(oldLayer, oldGroup);
        if(deleteIndex < 0){
            qDebug() << "unexpected";
            deleteIndex = 0;
        }

        // delete oldest
        oldLayerList_m.removeFirst();
        oldGroupList_m.removeFirst();
        QWidget *oldButton = layout_m->itemAt(deleteIndex)->widget();
        layout_m->removeWidget(oldButton);
        oldButton->deleteLater();

        // add new
        layout_m->insertWidget(deleteIndex, button);
    }

    oldLayerList_m.append(layer);
    oldGroupList_m.append(group);
}

void ShortcutWidget::resizeEvent(QResizeEvent *event){
    QWidget::resizeEvent(event);

    int n = oldLayerList_m.length();
    int sumButtonWidth = 0;
    if(n != 0){
        sumButtonWidth = BUTTON_WIDTH * n + BUTTON_SPACE * (n-1);
        sumButtonWidth += MARGIN;
        if(this->width() > sumButtonWidth){
            return;
        }
    }else{
        return;
    }

    // remove 1 or more.
    while(this->width() < sumButtonWidth){
        // delete button
        QString group = oldGroupList_m.first();
        QString layer = oldLayerList_m.first();
        int index = getIndexOfSameContents(layer, group);
        oldLayerList_m.removeFirst();
        oldGroupList_m.removeFirst();
        if(index >= 0){
            QWidget *oldButton = layout_m->itemAt(index)->widget();
            layout_m->removeWidget(oldButton);
        }else{
            qDebug() << "unexpected";
            layout_m->removeWidget(layout_m->itemAt(0)->widget());
        }

        // update button width
        int n = oldLayerList_m.length();
        sumButtonWidth = BUTTON_WIDTH * n + BUTTON_SPACE * (n-1);
        sumButtonWidth += MARGIN;
    }
}

bool ShortcutWidget::eventFilter(QObject *obj, QEvent *event){
    if(event->type() == QEvent::MouseButtonPress){
       ShortcutButton *button = qobject_cast<ShortcutButton*>(obj);
       if(button == NULL) return false;

       QString layer = button->getLayer();
       QString group = button->getGroup();
       messageBroker_m->messageShortcutWidget_showLogWidget(layer, group);
   }

    return false;
}
