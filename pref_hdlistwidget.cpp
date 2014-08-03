#include "pref_hdlistwidget.h"


HdListWidget::HdListWidget(QWidget *parent) :
    QWidget(parent)
{
    // SCROLL AREA
    QVBoxLayout *vl = new QVBoxLayout();
    vl->setContentsMargins(0,0,0,0);
    vl->setSpacing(0);
    setLayout(vl);
    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    vl->addWidget(scrollArea);

    // MAIN Widgent
    base_m = new QWidget();
    scrollArea->setWidget(base_m);
    vbox_m = new QVBoxLayout();
    vbox_m->setAlignment(Qt::AlignTop);
    vbox_m->setContentsMargins(0,0,0,0);
    vbox_m->setSpacing(0);
    base_m->setLayout(vbox_m);
}


void HdListWidget::insertNewDifinitionWidget(HighlightDifinitionWidget *caller){
    base_m->repaint();
    int index = vbox_m->indexOf(caller);
    HighlightDifinitionWidget *hdw = new HighlightDifinitionWidget(base_m);
    connect(hdw, SIGNAL(insertHighlight(HighlightDifinitionWidget*)), this, SLOT(insertNewDifinitionWidget(HighlightDifinitionWidget*)));
    connect(hdw, SIGNAL(removeHighlight(HighlightDifinitionWidget*)), this, SLOT(removeDifinitionWidget(HighlightDifinitionWidget*)));
    vbox_m->insertWidget(index + 1, hdw);
    base_m->update();
    update();
}



void HdListWidget::removeDifinitionWidget(HighlightDifinitionWidget *caller){
    if(vbox_m->count() <= 1) return;

    base_m->repaint();
    vbox_m->removeWidget(caller);
    caller->deleteLater();
    base_m->repaint();
    update();
}


void HdListWidget::initializeDifinitionWidgetes(QList<HighlightRule> list){
    // remove all
    while(vbox_m->count() != 0){
        QLayoutItem *item = vbox_m->itemAt(0);
        vbox_m->removeItem(item);
        delete item->widget();
    }

    if(list.length() == 0){
        HighlightDifinitionWidget *hdw = new HighlightDifinitionWidget(base_m);
        connect(hdw, SIGNAL(insertHighlight(HighlightDifinitionWidget*)), this, SLOT(insertNewDifinitionWidget(HighlightDifinitionWidget*)));
        connect(hdw, SIGNAL(removeHighlight(HighlightDifinitionWidget*)), this, SLOT(removeDifinitionWidget(HighlightDifinitionWidget*)));
        vbox_m->addWidget(hdw);
        return;
    }

    // add list
    for(int i=0; i<list.length(); i++){
        HighlightDifinitionWidget *hdw = new HighlightDifinitionWidget(base_m);
        HighlightRule rule = list.at(i);
        hdw->setValues(rule.getRegexString(), rule.getFormat(), rule.getCaseSensitive());
        connect(hdw, SIGNAL(insertHighlight(HighlightDifinitionWidget*)), this, SLOT(insertNewDifinitionWidget(HighlightDifinitionWidget*)));
        connect(hdw, SIGNAL(removeHighlight(HighlightDifinitionWidget*)), this, SLOT(removeDifinitionWidget(HighlightDifinitionWidget*)));
        hdw->applyHighLight();
        vbox_m->addWidget(hdw);
    }
}

QList<HighlightRule> HdListWidget::getHighLightRuleList(){
    QList<HighlightRule> list;

    int size = vbox_m->count();
    for(int i=0; i<size; i++){
        QLayoutItem *item = vbox_m->itemAt(i);
        HighlightDifinitionWidget *hdw = (HighlightDifinitionWidget*)item->widget();
        QString regexString = hdw->getRegexString();
        regexString = regexString.trimmed();
        if(regexString != ""){
            HighlightRule rule(regexString, hdw->getCharFormat(), hdw->getIsCaseSensitive());
            list.append(rule);
        }
    }

    return list;
}

