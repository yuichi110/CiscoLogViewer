#include "lv_logmodel.h"

LogModel::LogModel(QObject *parent, QString layerName, QString groupName, QString clvFilePath, bool showPopupButton) :
    QObject(parent)
{
    // key
    flag_ControlKey_m = false;
    flag_MetaKey_m = false;
    flag_ShiftKey_m = false;

    // view
    logView_m = NULL;
    logTreeView_m = NULL;
    logSearchView_m = NULL;
    logEdit_m = NULL;
    if(showPopupButton){
        logWindow_m = new LogWindow(logView_m, clvFilePath, layerName, groupName);
    }else{
        logWindow_m = NULL;
    }

    // loader
    loadFinished_m = true;
    loader_m = new CommandLoader(groupName, clvFilePath);
    connect(loader_m, SIGNAL(signalAppendString(QString)), this, SLOT(appendStringToEditer(QString)));
    connect(loader_m, SIGNAL(signalInsertCommand(int,QString,int)), this, SLOT(insertCommandToTreeWidget(int,QString,int)));
    connect(loader_m, SIGNAL(signalDoneLoading()), this, SLOT(doneLoading()));
}

void LogModel::registerLogView(LogView *logView){
    logView_m = logView;
}

void LogModel::registerLogTreeView(LogTreeView *logTreeView){
    logTreeView_m = logTreeView;
}

void LogModel::registerLogSearchView(LogSearchWidget *logSearchView){
    logSearchView_m = logSearchView;
}

void LogModel::registerLogEdit(LogEdit *logEdit){
    logEdit_m = logEdit;
}

void LogModel::registerHighlighter(SyntaxHighlighter *highlighter){
    highlighter_m = highlighter;
}

void LogModel::setHighlightRules(QList<HighlightRule> rules){
    highlighter_m->setHighlightRules(rules);
    logEdit_m->rehighLight(true);
}

void LogModel::handleKeyReleaseEvent(QKeyEvent *e){
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

        default:
            break;
    }
}

bool LogModel::handleKeyPressEvent(QKeyEvent *e){
    int key = e->key();
    qDebug() << "key: " << key;
    switch(key){
        case Qt::Key_Left:
        case Qt::Key_Right:
        case Qt::Key_Up:
        case Qt::Key_Down:
        case Qt::Key_PageUp:
        case Qt::Key_PageDown:  break;

        case Qt::Key_Control:
            flag_ControlKey_m = true; break;
        case Qt::Key_Meta:
            flag_MetaKey_m = true; break;
        case Qt::Key_Shift:
            flag_ShiftKey_m = true; break;

        case Qt::Key_F3:
            if(flag_ShiftKey_m){
                findBackward();
            }else{
                findForward();
            }
            return true;

        case Qt::Key_F2:
            findBackward();
            return true;

        default:
            if(flag_ControlKey_m && !isProhibitedCntKey(key)){
                if(key == Qt::Key_F){
                    logSearchView_m->focusOnSearchTextField();
                    return true;
                }
                break;
            }else{
                return true;
            }
    }

    qDebug() << "false";
    return false;
}

bool LogModel::isProhibitedCntKey(int key){
    switch(key){
        case Qt::Key_V: // paste
        case Qt::Key_X: // cut
        case Qt::Key_K: // kill line
            return true;

        default:
            return false;
    }
}


void LogModel::jumpToLine(int lineNumber){
    logEdit_m->jumpToLine(lineNumber);
}

void LogModel::highlightCurrentTreeItem(int lineNum){
    if(logTreeView_m == NULL){
        return;
    }
    logTreeView_m->highlightCurrentTreeItem(lineNum);
}

void LogModel::popupLogWindow(){
    if(logWindow_m != NULL){
        logWindow_m->showWindow();
    }
}

void LogModel::keywordChanged(){
    QString keyword = logSearchView_m->getKeyword();
    bool caseSensitive = logSearchView_m->getCaseSensitive();
    logEdit_m->setSearchKeyword(keyword, caseSensitive);
    logEdit_m->rehighLight(true);
}

void LogModel::findForward(){
    QString keyword = logSearchView_m->getKeyword();
    bool caseSensitive = logSearchView_m->getCaseSensitive();
    if(keyword == "") return;

    bool exist;
    if(caseSensitive){
        exist = logEdit_m->find(keyword, QTextDocument::FindCaseSensitively);
    }else{
        exist = logEdit_m->find(keyword);
    }

    if(!exist){
        logEdit_m->moveCursor(QTextCursor::Start);
        if(caseSensitive){
            exist = logEdit_m->find(keyword, QTextDocument::FindCaseSensitively);
        }else{
            exist = logEdit_m->find(keyword);
        }
    }

    if(exist){
        logEdit_m->centerCursor();
    }
}

void LogModel::findBackward(){
    QString keyword = logSearchView_m->getKeyword();
    bool caseSensitive = logSearchView_m->getCaseSensitive();
    if(keyword == "") return;

    bool exist;
     if(caseSensitive){
         exist = logEdit_m->find(keyword, QTextDocument::FindCaseSensitively | QTextDocument::FindBackward);
     }else{
         exist = logEdit_m->find(keyword, QTextDocument::FindBackward);
     }
     if(!exist){
         logEdit_m->moveCursor(QTextCursor::End);
         if(caseSensitive){
             exist = logEdit_m->find(keyword, QTextDocument::FindCaseSensitively | QTextDocument::FindBackward);
         }else{
             exist = logEdit_m->find(keyword, QTextDocument::FindBackward);
         }
     }

     if(exist) {
         logEdit_m->centerCursor();
     }
}

void LogModel::loadLogs(){
    unLoadLogs();
    loadFinished_m = false;
    loader_m->setGroupLoadMode();
    loader_m->start();
}

void LogModel::loadLogs(QList<int> idList){
    unLoadLogs();
    loadFinished_m = false;
    loader_m->setIdListMode(idList);
    loader_m->start();
}

void LogModel::unLoadLogs(){
    logEdit_m->enableSyntaxHighlight(false);
    logEdit_m->setPlainText("");
    logEdit_m->setReadOnly(true);
    logTreeView_m->clear();
}

void LogModel::appendStringToEditer(QString line){
    if(logEdit_m == NULL){
        qDebug() << "FATAL ERROR at LogView::appendStringToEditer";
        return;
    }

    // move cursol to last block.
    int pos = logEdit_m->document()->lastBlock().position();
    QTextCursor tcursor = logEdit_m->textCursor();
    tcursor.setPosition(pos);
    logEdit_m->setTextCursor(tcursor);

    // append
    logEdit_m->insertPlainText(line);
}

void LogModel::insertCommandToTreeWidget(int commandPosition, QString commandName, int startLineNum){
    if(logTreeView_m == NULL){
        // treeview isn't shown.
        return;
    }

    logTreeView_m->insertCommandToTreeWidget(commandPosition, commandName, startLineNum);
}

void LogModel::doneLoading(){
    int pos = logEdit_m->document()->findBlockByLineNumber(0).position();
    QTextCursor tcursor = logEdit_m->textCursor();
    tcursor.setPosition(pos);
    logEdit_m->setTextCursor(tcursor);
    logEdit_m->enableSyntaxHighlight(true);
    logEdit_m->setReadOnly(false);
    loadFinished_m = true;
}

bool LogModel::isLoadingNow(){
    return !loadFinished_m;
}

void LogModel::closeLogWindow(){
    if(logWindow_m != NULL){
        logWindow_m->close();
    }
}
