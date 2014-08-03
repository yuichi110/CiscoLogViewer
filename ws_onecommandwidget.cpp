#include "ws_onecommandwidget.h"

OneCommandWidget::OneCommandWidget(QWidget *parent,  QString command, QString contents) :
    QWidget(parent)
{
    setWindowIcon(QIcon(AppInfo::APP_ICON));
    QString title = QString("%1 : %2").arg(command, AppInfo::APP_NAME);
    setWindowTitle(title);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // search
    QHBoxLayout *searchLayout = new QHBoxLayout(this);
    searchLayout->addWidget(new QLabel("Search Keyword: "));
    searchWordLineEdit_m = new QLineEdit(this);
    connect(searchWordLineEdit_m, SIGNAL(textChanged(QString)), this, SLOT(keywordChanged()));
    searchLayout->addWidget(searchWordLineEdit_m);
    searchLayout->addWidget(new QLabel("  Case Sensitive:"));
    caseSensitiveCheckBox_m = new QCheckBox(this);
    connect(caseSensitiveCheckBox_m, SIGNAL(clicked()), this, SLOT(keywordChanged()));
    searchLayout->addWidget(caseSensitiveCheckBox_m);
    QIcon leftIcon(AppInfo::SEARCH_ICON_LEFT);
    QPushButton *bkButton = new QPushButton(leftIcon, "", this);
    bkButton->installEventFilter(this);
    connect(bkButton,SIGNAL(clicked()),this, SLOT(findBackward()));
    searchLayout->addWidget(bkButton);
    QIcon rightIcon(AppInfo::SEARCH_ICON_RIGHT);
    QPushButton *fwdButton = new QPushButton(rightIcon, "", this);
    fwdButton->installEventFilter(this);
    connect(fwdButton,SIGNAL(clicked()), this, SLOT(findForward()));
    searchLayout->addWidget(fwdButton);
    mainLayout->addLayout(searchLayout);

    textEdit_m = new OneCommandEdit(this);
    textEdit_m->setPlainText(contents);
    connect(textEdit_m, SIGNAL(controlF()), this, SLOT(controlF()));
    connect(textEdit_m, SIGNAL(findForward()), this, SLOT(findForward()));
    connect(textEdit_m, SIGNAL(findBackward()), this, SLOT(findBackward()));
    mainLayout->addWidget(textEdit_m);
    setLayout(mainLayout);
}

////////
/// SEARCH
////////


void OneCommandWidget::keywordChanged(){
    QString keyword = searchWordLineEdit_m->text();
    bool caseSensitive = caseSensitiveCheckBox_m->isChecked();
    textEdit_m->setSearchKeyword(keyword, caseSensitive);
    textEdit_m->rehighLight(true);
}



void OneCommandWidget::findForward(){
    QString keyword = searchWordLineEdit_m->text();
    bool caseSensitive = caseSensitiveCheckBox_m->isChecked();
    if(keyword == "") return;

    bool exist;
    if(caseSensitive){
        exist = textEdit_m->find(keyword, QTextDocument::FindCaseSensitively);
    }else{
        exist = textEdit_m->find(keyword);
    }

    if(!exist){
        textEdit_m->moveCursor(QTextCursor::Start);
        if(caseSensitive){
            exist = textEdit_m->find(keyword, QTextDocument::FindCaseSensitively);
        }else{
            exist = textEdit_m->find(keyword);
        }
    }

    if(exist){
        textEdit_m->centerCursor();
    }
}

void OneCommandWidget::findBackward(){
    QString keyword = searchWordLineEdit_m->text();
    bool caseSensitive = caseSensitiveCheckBox_m->isChecked();
    if(keyword == "") return;

    bool exist;
     if(caseSensitive){
         exist = textEdit_m->find(keyword, QTextDocument::FindCaseSensitively | QTextDocument::FindBackward);
     }else{
         exist = textEdit_m->find(keyword, QTextDocument::FindBackward);
     }
     if(!exist){
         textEdit_m->moveCursor(QTextCursor::End);
         if(caseSensitive){
             exist = textEdit_m->find(keyword, QTextDocument::FindCaseSensitively | QTextDocument::FindBackward);
         }else{
             exist = textEdit_m->find(keyword, QTextDocument::FindBackward);
         }
     }

     if(exist) {
         textEdit_m->centerCursor();
     }
}

void OneCommandWidget::controlF(){
    searchWordLineEdit_m->setFocus();
    searchWordLineEdit_m->selectAll();
}

////////////
/// KEY EVENT
/////////////

bool OneCommandWidget::eventFilter(QObject *obj, QEvent *e){
    if(obj == searchWordLineEdit_m && e->type() == QEvent::KeyPress){

    }

    return false;
}
