#include "ws_searchcommandwidget.h"

const QString SearchCommandWidget::GROUP_NONE_KEYWORD = "NONE";
SearchCommandWidget::SearchCommandWidget(QWidget *parent, MessageBroker *messageBroker) :
    QWidget(parent)
{
    messageBroker_m = messageBroker;
    messageBroker_m->registerSearchCommandWidget(this);

    hbox_m = new QHBoxLayout();
    hbox_m->setContentsMargins(0, 0, 0, 0);
    hbox_m->setSpacing(0);
    this->setLayout(hbox_m);

    // LINE EDIT
    lineEdit_m = new QLineEdit(this);
    lineEdit_m->setFixedWidth(AppInfo::WINDOW_SEARCH_BOX_WIDTH);
    hbox_m->addWidget(lineEdit_m);

    //test
    int HEIGHT = AppInfo::WINDOW_WS_HEIGHT;

    // CLEAR BUTTON
    QToolButton *clearButton = new QToolButton(lineEdit_m);
    QImage image(AppInfo::SEARCH_ICON);
    clearButton->setIcon(QIcon(QPixmap::fromImage(image.scaled(HEIGHT-3, HEIGHT-3, Qt::KeepAspectRatio, Qt::SmoothTransformation))));
    clearButton->setStyleSheet("QToolButton { border: none; padding: 0px; }");
    clearButton->setCursor(Qt::ArrowCursor);
    int frameWidth = lineEdit_m->style()->pixelMetric(QStyle::PM_DefaultFrameWidth);
    setStyleSheet(QString("QLineEdit { padding-right: %1px; } ").arg(clearButton->sizeHint().width() + frameWidth + 1));
    QSize sz = clearButton->sizeHint();
    clearButton->move(lineEdit_m->rect().right() - frameWidth - sz.width(), 2);
    connect(clearButton, SIGNAL(clicked()), lineEdit_m, SLOT(clear()));

    // POPUP
    popup = new QTreeWidget;
    popup->setWindowFlags(Qt::Popup);
    popup->setFocusPolicy(Qt::NoFocus);
    popup->setFocusProxy(parent);
    popup->setMouseTracking(true);
    popup->setColumnCount(2);
    popup->setUniformRowHeights(true);
    popup->setRootIsDecorated(false);
    popup->setEditTriggers(QTreeWidget::NoEditTriggers);
    popup->setSelectionBehavior(QTreeWidget::SelectRows);
    popup->setFrameStyle(QFrame::Box | QFrame::Plain);
    popup->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    popup->header()->hide();
    popup->installEventFilter(this);
    connect(popup, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(doneCompletion()));

    //TIMER
    timer = new QTimer(this);
    timer->setSingleShot(true);
    timer->setInterval(500);
    connect(timer, SIGNAL(timeout()), this, SLOT(runSuggest()));

    // LINEEDIT EVENT
    connect(lineEdit_m, SIGNAL(textEdited(QString)), timer, SLOT(start()));
}


void SearchCommandWidget::runSuggest()
 {
    // Check
     QString keyword = lineEdit_m->text();
     if(keyword == ""){
         return;
     }
     if(!messageBroker_m->messageSearchCommand_loaded()){
         return;
     }
     QString clvFilePath = messageBroker_m->messageSearchCommand_getClvFilePath();
     QFile file(clvFilePath);
     if(!file.exists()){
         return;
     }

     // CLV file is OK.
     // Load data.
    ClvDataAccessor *accessor = new ClvDataAccessor(clvFilePath);
    accessor->open();
    QList<CommandGroupInfo> cgiList = accessor->getCommandGroupInfoList(keyword, 20);
    accessor->close();
    if(cgiList.length() == 0){
        return;
    }

    // create pannel data.
    QList<QString> commandNameList;
    QList<QString> commandGroupList;
    foreach(CommandGroupInfo cgi, cgiList){
        commandNameList.append(cgi.getCommand());
        if(cgi.getLayer() == "" || cgi.getGroup() == ""){
            commandGroupList.append(GROUP_NONE_KEYWORD);
        }else{
            QString group = QString("%1/%2").arg(cgi.getLayer(), cgi.getGroup());
            commandGroupList.append(group);
        }
    }

    showCompletion(commandNameList, commandGroupList);
 }

void SearchCommandWidget::showCompletion(QList<QString> commandList, QList<QString> groupList){
    if (commandList.isEmpty() || commandList.count() != groupList.count()) return;
    popup->setUpdatesEnabled(false);
    popup->clear();

    for (int i = 0; i < commandList.count(); ++i) {
        QTreeWidgetItem * item;
        item = new QTreeWidgetItem(popup);
        QString group = groupList[i];
        item->setText(0, group);
        if(group == GROUP_NONE_KEYWORD){
            item->setTextColor(0, Qt::red);
        }
        item->setText(1, commandList[i]);
    }

    popup->setCurrentItem(popup->topLevelItem(0));
    popup->resizeColumnToContents(0);
    popup->resizeColumnToContents(1);
    popup->adjustSize();
    popup->setUpdatesEnabled(true);

    int h = popup->sizeHintForRow(0) * qMin(20, commandList.count()) + 3;
    popup->resize(300, h);

    int x = lineEdit_m->width() - popup->width();
    popup->move(lineEdit_m->mapToGlobal(QPoint(x, lineEdit_m->height())));
    popup->setFocus();
    popup->show();
}

bool SearchCommandWidget::eventFilter(QObject *obj, QEvent *event){
    if(obj == popup){
        return handlePopupEvent(event);
    }

    return false;
}

bool SearchCommandWidget::handlePopupEvent(QEvent *event){
    if (event->type() == QEvent::MouseButtonPress) {
        popup->hide();
        lineEdit_m->setFocus();
        return true;
    }

    if (event->type() == QEvent::KeyPress) {
        bool consumed = false;
        int key = static_cast<QKeyEvent*>(event)->key();
        switch (key) {
        case Qt::Key_Enter:
        case Qt::Key_Return:
            doneCompletion();
            consumed = true;

        case Qt::Key_Escape:
            lineEdit_m->setFocus();
            popup->hide();
            consumed = true;

        case Qt::Key_Up:
        case Qt::Key_Down:
        case Qt::Key_Home:
        case Qt::Key_End:
        case Qt::Key_PageUp:
        case Qt::Key_PageDown:
            break;

        default:
            lineEdit_m->setFocus();
            lineEdit_m->event(event);
            popup->hide();
            break;
        }

        return consumed;
    }

    return false;
}

void SearchCommandWidget::doneCompletion(){
    //if(DEBUG) qDebug() << "ShortCutTabWidget::DoneComplention()";

    timer->stop();
    popup->hide();
    lineEdit_m->setFocus();

    QTreeWidgetItem *item = popup->currentItem();
    if (!item) return;
    QString commandName = item->text(1);
    lineEdit_m->setText(commandName);

    QString groupLayer = item->text(0);
    if(groupLayer == GROUP_NONE_KEYWORD){
        ClvDataAccessor *accessor = new ClvDataAccessor(messageBroker_m->messageSearchCommand_getClvFilePath());
        accessor->open();
        QByteArray data = accessor->getCommandData(commandName);
        accessor->close();
        if(data.length() == 0){
            return;
        }

        QString commandContents = QString(qUncompress(data));
        OneCommandWidget *ocw = new OneCommandWidget(NULL, commandName, commandContents);
        ocw->show();

    }else{
        QStringList stlist = groupLayer.split("/");
        if(stlist.length() != 2){
            qDebug() << "unexpected: searchCommand";
            return;
        }
        QString layer = stlist.at(0);
        QString group = stlist.at(1);
        messageBroker_m->messageSearchCommand_showCommand(commandName, layer, group);
    }
}

void SearchCommandWidget::focusOnWidget(){
    lineEdit_m->setFocus();
    lineEdit_m->selectAll();
}
