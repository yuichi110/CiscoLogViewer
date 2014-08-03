#ifndef HDMANAGER_H
#define HDMANAGER_H

#include <QWidget>
#include <QtGui>
#include "pref_highlightdifinitionwidget.h"
#include "lv_highlightrule.h"

class HighlightDifinitionWidget;
class HdListWidget : public QWidget
{
    Q_OBJECT

public:
    HdListWidget(QWidget *parent = 0);

    void initializeDifinitionWidgetes(QList<HighlightRule> highlightRuleList);
    QList<HighlightRule> getHighLightRuleList();

private:
    //static const bool DEBUG;
    QVBoxLayout *vbox_m;
    QWidget *base_m;

signals:
    
public slots:
    void insertNewDifinitionWidget(HighlightDifinitionWidget *caller);
    void removeDifinitionWidget(HighlightDifinitionWidget *caller);

};


#endif // HDMANAGER_H
