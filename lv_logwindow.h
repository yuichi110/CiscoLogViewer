#ifndef LOGWINDOW_H
#define LOGWINDOW_H

#include <QtWidgets>
#include "core_appinfo.h"
#include "lv_logview.h"
#include "lv_logmodel.h"

class MainWindow;
class LogView;

class LogWindow : public QMainWindow
{
    Q_OBJECT

private:
    LogView *logview_m;

public:
    explicit LogWindow(QWidget *parent, QString clvFilePath, QString layerName, QString groupName);
    void showWindow();

protected:
    void closeEvent(QCloseEvent *);

signals:
    void signalLogWindowClosed();
    
public slots:
    void receiveMainWindowCloseSignal();
    //void updateWindowTitle();
    //void updateWindow();
};


#endif // LOGWINDOW_H
