#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QtWidgets>

// core
#include "core_messagebroker.h"
#include "core_appinfo.h"
#include "core_clvloader.h"
#include "core_preferencemanager.h"
#include "core_tabmanager.h"
#include "core_wstabmanager.h"

// gui parts
#include "ws_shortcutwidget.h"
#include "ws_searchcommandwidget.h"
#include "mwc_dropzone.h"
#include "mwc_layertab.h"
#include "mwc_menubar.h"

class MessageBroker;
class SearchCommandWidget;
class ShortcutWidget;
class LayerTabWidget;
class DropZone;

class MainWindow : public QMainWindow
{
public:
    explicit MainWindow();
    ~MainWindow();
    void swapDZtoLayerTab();

private:
    MessageBroker *messageBroker_m;
    ShortcutWidget *shortcutWidget_m;
    SearchCommandWidget *searchCommandWidget_m;
    LayerTabWidget *tabWidget_m;
    DropZone *dropZone_m;

    Q_OBJECT
private slots:

protected:
    void resizeEvent(QResizeEvent *event);
    virtual void keyPressEvent(QKeyEvent *e);
    virtual void keyReleaseEvent(QKeyEvent *e);
    void closeEvent(QCloseEvent *);

private:
    bool flag_ControlKey_m;
    bool flag_MetaKey_m;
    bool flag_ShiftKey_m;

signals:
    void signalMainWindowClosed();

};

#endif // MAINWINDOW_H
