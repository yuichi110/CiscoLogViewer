#include "ws_onecommandedit.h"

OneCommandEdit::OneCommandEdit(QWidget *parent) :
    QPlainTextEdit(parent)
{
    previousHeadBlock_m = -1;
    flag_ControlKey_m = false;
    flag_ShiftKey_m = false;
    flag_MetaKey_m = false;

    syntaxHighlighter_m = new SyntaxHighlighter(this->document());
    syntaxHighlighter_m->enableSyntaxHighlight(true);
    QFont font("Courier");
    font.setStyleHint(QFont::Courier);
    setFont(font);
    this->setWordWrapMode(QTextOption::NoWrap);
    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));
}

void OneCommandEdit::setSearchKeyword(QString string, bool isCaseSensitive){
    syntaxHighlighter_m->setSearchKeyword(string, isCaseSensitive);
}

void OneCommandEdit::rehighLight(bool isForce){
    if(!syntaxHighlighter_m->isEnabledSyntaxHilight()) return;

    QTextBlock block = firstVisibleBlock();
    int lineNum = block.blockNumber();
    if(lineNum == previousHeadBlock_m && !isForce) return;
    previousHeadBlock_m = lineNum;

    QRect rect = this->rect();
    while(block.isValid()){
        const int y = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
        if(y >= rect.bottom()) break;
        syntaxHighlighter_m->rehighlightBlock(block);
        block = block.next();
    }
}

void OneCommandEdit::highlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> extraSelections;
    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection;

        QColor lineColor = QColor(Qt::yellow).lighter(160);
        QColor fgColor = QColor(Qt::red);
        selection.format.setBackground(lineColor);
        selection.format.setForeground(fgColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }

    setExtraSelections(extraSelections);
}

void OneCommandEdit::keyPressEvent(QKeyEvent *e){
    bool filtered = false;
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
                emit findBackward();
            }else{
                emit findForward();
            }
            filtered = true;

        case Qt::Key_F2:
            emit findBackward();
            filtered = true;

        default:
            if(flag_ControlKey_m && !isProhibitedCntKey(key)){
                if(key == Qt::Key_F){
                    emit controlF();
                    filtered = true;
                }
                break;
            }else{
                filtered = true;
            }
    }


    if(!filtered){
        QPlainTextEdit::keyPressEvent(e);
    }
}

void OneCommandEdit::keyReleaseEvent(QKeyEvent *e){
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

bool OneCommandEdit::isProhibitedCntKey(int key){
    switch(key){
        case Qt::Key_V: // paste
        case Qt::Key_X: // cut
        case Qt::Key_K: // kill line
            return true;

        default:
            return false;
    }
}
