#include "mwc_mainwindow.h"

//const bool MainWindow::DEBUG = false;

MainWindow::MainWindow() :
    QMainWindow(NULL)
{
    flag_ControlKey_m = false;
    flag_MetaKey_m = false;
    flag_ShiftKey_m = false;

    messageBroker_m = new MessageBroker();
    messageBroker_m->registerMainWindow(this);

    // new preferenceManager();
    new ClvLoader(messageBroker_m);
    new WsTabManager(this, messageBroker_m);
    new TabManager(this, messageBroker_m);


    setWindowIcon(QIcon(AppInfo::APP_ICON));
    setWindowTitle(AppInfo::APP_NAME);
    setMinimumSize(800, 400);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    mainLayout->setSpacing(5);
    QHBoxLayout *topLayout = new QHBoxLayout();
    topLayout->setContentsMargins(0, 0, 0, 0);
    shortcutWidget_m = new ShortcutWidget(this, messageBroker_m);
    shortcutWidget_m->setFixedHeight(AppInfo::WINDOW_WS_HEIGHT);
    topLayout->addWidget(shortcutWidget_m);
    topLayout->addStretch();
    searchCommandWidget_m = new SearchCommandWidget(this, messageBroker_m);
    searchCommandWidget_m->setFixedSize(AppInfo::WINDOW_SEARCH_BOX_WIDTH, AppInfo::WINDOW_WS_HEIGHT);
    topLayout->addWidget(searchCommandWidget_m);
    mainLayout->addLayout(topLayout);

    dropZone_m = new DropZone(this, messageBroker_m);
    tabWidget_m = new LayerTabWidget(this, messageBroker_m);
    tabWidget_m->hide();
    mainLayout->addWidget(dropZone_m);

    QWidget *centerWidget = new QWidget(this);
    centerWidget->setLayout(mainLayout);
    this->setCentralWidget(centerWidget);
    setMenuBar(new MenuBar(this, messageBroker_m));
}

MainWindow::~MainWindow()
{
}

/////////////////////
///////   DRAG AND DROP
/////////////////////

void MainWindow::swapDZtoLayerTab(){
    qDebug() << "swap";
    QLayout *mainLayout = this->centralWidget()->layout();
    mainLayout->replaceWidget(dropZone_m, tabWidget_m);
    tabWidget_m->show();
    dropZone_m->hide();
}

void MainWindow::resizeEvent(QResizeEvent *event){
    QMainWindow::resizeEvent(event);
    int width = centralWidget()->width() - searchCommandWidget_m->width() - 30;
    shortcutWidget_m->setFixedWidth(width);
}

void MainWindow::keyPressEvent(QKeyEvent *e){
    qDebug() << "Main Key Pressed:" << e->key();

    int key = e->key();
    switch(key){
        case Qt::Key_Control:
            qDebug() << "control";
            flag_ControlKey_m = true; break;
        case Qt::Key_Meta:
            qDebug() << "meta";
            flag_MetaKey_m = true; break;
        case Qt::Key_Shift:
            qDebug() << "shift";
            flag_ShiftKey_m = true; break;

        default:
            break;
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *e){
    qDebug() << "Main Key Released:" << QString::number(e->key(), 16);

    int key = e->key();
    switch(key){
        case Qt::Key_Control:
            qDebug() << "control";
            flag_ControlKey_m = false; break;
        case Qt::Key_Meta:
            qDebug() << "meta";
            flag_MetaKey_m = false; break;
        case Qt::Key_Shift:
            qDebug() << "shift";
            flag_ShiftKey_m = false; break;

        case Qt::Key_S:
            if(flag_ControlKey_m || flag_MetaKey_m){
                messageBroker_m->messageKey_save();
            }
            break;

        case Qt::Key_N:
            if(flag_ControlKey_m || flag_MetaKey_m){
                messageBroker_m->messageKey_newWindow();
            }
            break;

        case Qt::Key_K:
            if(flag_ControlKey_m || flag_MetaKey_m){
                messageBroker_m->messageKey_tabUp();
            }
            break;
        case Qt::Key_L:
            if(flag_ControlKey_m || flag_MetaKey_m){
                messageBroker_m->messageKey_tabRight();
            }
            break;
        case Qt::Key_J:
            if(flag_ControlKey_m || flag_MetaKey_m){
                messageBroker_m->messageKey_tabDown();
            }
            break;
        case Qt::Key_H:
            if(flag_ControlKey_m || flag_MetaKey_m){
                messageBroker_m->messageKey_tabLeft();
            }
            break;
        case Qt::Key_G:
            if(flag_ControlKey_m || flag_MetaKey_m){
                messageBroker_m->messageKey_focusCommandSearch();
            }

        default:
            break;
    }
}

void MainWindow::closeEvent(QCloseEvent *e){
    emit signalMainWindowClosed();
    QMainWindow::closeEvent(e);
}
