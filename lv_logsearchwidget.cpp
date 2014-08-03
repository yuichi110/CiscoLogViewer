#include "lv_logsearchwidget.h"

LogSearchWidget::LogSearchWidget(QWidget *parent, LogModel *eventManager, bool isShowPopupButton) :
    QWidget(parent)
{  
    setFixedHeight(50);
    eventManager_m = eventManager;
    eventManager_m->registerLogSearchView(this);

    QHBoxLayout *searchHbox = new QHBoxLayout();
    if(isShowPopupButton){
        QIcon popupIcon(AppInfo::SEARCH_ICON_WINDOW);
        QPushButton *popupButton = new QPushButton(popupIcon, "", this);
        connect(popupButton, SIGNAL(clicked()), eventManager_m, SLOT(popupLogWindow()));
        searchHbox->addWidget(popupButton);
    }

    searchHbox->addWidget(new QLabel("Search Keyword: "));
    searchWordLineEdit_m = new QLineEdit(this);
    connect(searchWordLineEdit_m, SIGNAL(textChanged(QString)), eventManager_m, SLOT(keywordChanged()));
    searchHbox->addWidget(searchWordLineEdit_m);

    searchHbox->addWidget(new QLabel("  Case Sensitive:"));
    caseSensitiveCheckBox_m = new QCheckBox(this);
    connect(caseSensitiveCheckBox_m, SIGNAL(clicked()), eventManager_m, SLOT(keywordChanged()));
    searchHbox->addWidget(caseSensitiveCheckBox_m);

    QIcon leftIcon(AppInfo::SEARCH_ICON_LEFT);
    bkButton_m = new QPushButton(leftIcon, "", this);
    bkButton_m->installEventFilter(this);
    connect(bkButton_m,SIGNAL(clicked()),eventManager_m, SLOT(findBackward()));
    searchHbox->addWidget(bkButton_m);

    QIcon rightIcon(AppInfo::SEARCH_ICON_RIGHT);
    fwdButton_m = new QPushButton(rightIcon, "", this);
    fwdButton_m->installEventFilter(this);
    connect(fwdButton_m,SIGNAL(clicked()),eventManager_m, SLOT(findForward()));
    searchHbox->addWidget(fwdButton_m);

    setLayout(searchHbox);
}

void LogSearchWidget::keyPressEvent(QKeyEvent *e){
    int key = e->key();
    switch(key){
        case Qt::Key_Return:
        case Qt::Key_Enter:
            eventManager_m->findForward();
            break;
        default:
            break;
    }

    QWidget::keyPressEvent(e);
}

QString LogSearchWidget::getKeyword(){
    return searchWordLineEdit_m->text();
}

bool LogSearchWidget::getCaseSensitive(){
    return caseSensitiveCheckBox_m->isChecked();
}

void LogSearchWidget::focusOnSearchTextField(){
    searchWordLineEdit_m->setFocus();
    searchWordLineEdit_m->selectAll();
}
