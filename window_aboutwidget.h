#ifndef ABOUTWIDGET_H
#define ABOUTWIDGET_H

#include <QtGui>
#include <QtWidgets>
#include "core_appinfo.h"

class AboutWidget : public QWidget
{
    Q_OBJECT

public:
    static AboutWidget *getInstance();

private:
    explicit AboutWidget();
    
signals:
    
public slots:
    
};

#endif // ABOUTWIDGET_H
