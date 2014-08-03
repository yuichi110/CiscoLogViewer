#include "lv_logedit.h"

LogEdit::LogEdit(QWidget *parent, LogModel *eventManager) :
    QPlainTextEdit(parent)
{
    eventManager_m = eventManager;
    eventManager_m->registerLogEdit(this);
    syntaxHighlighter_m = new SyntaxHighlighter(this->document());
    eventManager_m->registerHighlighter(syntaxHighlighter_m);

    // style
    QFont font("Courier");
    font.setStyleHint(QFont::Courier);
    setFont(font);
    this->setWordWrapMode(QTextOption::NoWrap);

    // code line number area
    lineNumberArea_m = new QWidget(this);
    lineNumberArea_m->installEventFilter(this);
    lineNumberWidth_m = fontMetrics().width('8') * 8;
    lineNumberAreaWidth_m = fontMetrics().width('8') * 10;
    setViewportMargins(lineNumberAreaWidth_m, 0, 0, 0);

    // syntax highlighter
    previousHeadBlock_m = -1;
    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));
    connect(syntaxHighlighter_m, SIGNAL(requestRehighlight()), this, SLOT(highlightRequested()));
}

/*
void LogEdit::setWindowStyle(QColor backgroundColor, QColor textColor,
                                    QColor clBackgroundColor, QColor clTextColor){

    QPalette p = palette();
    p.setColor(QPalette::Active, QPalette::Base, Qt::red);
    p.setColor(QPalette::Inactive, QPalette::Base, Qt::red);
    p.setColor(QPalette::Text, Qt::blue);
    setPalette(p);

}
*/

///////////////////////
////   HIGH LIGHTER
///////////////////////

void LogEdit::jumpToLine(int lineNum){
    int pos = document()->findBlockByLineNumber(lineNum - 1).position();
    QTextCursor tcursor = textCursor();
    tcursor.setPosition(pos);
    setTextCursor(tcursor);
    centerCursor();
}

void LogEdit::enableSyntaxHighlight(bool enable){
    syntaxHighlighter_m->enableSyntaxHighlight(enable);
    rehighLight(true);
}

void LogEdit::rehighLight(bool isForce){
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

void LogEdit::setSearchKeyword(QString string, bool isCaseSensitive){
    syntaxHighlighter_m->setSearchKeyword(string, isCaseSensitive);
}

void LogEdit::highlightCurrentLine()
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
    QTextCursor cursor = textCursor();
    int currentBlock = cursor.blockNumber();

    eventManager_m->highlightCurrentTreeItem(currentBlock + 1);
}



///////////////////////
/////   KEY EVENT
///////////////////////

void LogEdit::keyPressEvent(QKeyEvent *e){
    bool filtered = eventManager_m->handleKeyPressEvent(e);
    if(!filtered){
        QPlainTextEdit::keyPressEvent(e);
    }else{
        QWidget::keyPressEvent(e);
    }
}

void LogEdit::keyReleaseEvent(QKeyEvent *e){
    eventManager_m->handleKeyReleaseEvent(e);
    QPlainTextEdit::keyReleaseEvent(e);
}


//////////////////////////
//////   LINE NUMBER AREA
//////////////////////////

bool LogEdit::eventFilter(QObject *obj, QEvent *e){
    if(obj == lineNumberArea_m && e->type() == QEvent::Paint){
        drawLineNumbers();
        return true;
    }
    return false;
}

void LogEdit::drawLineNumbers(){

    QPainter painter(lineNumberArea_m);
    painter.setPen(Qt::black);
    QRect r = lineNumberArea_m->rect();
    painter.fillRect(r, Qt::lightGray);
    const int ht = fontMetrics().height();
    QTextBlock block = firstVisibleBlock();
    int lineNumber = block.blockNumber() + 1;
    while(block.isValid()){
        const int y = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
        if(y>=r.bottom()) break;
        QString number = QString::number(lineNumber);
        painter.drawText(0, y, lineNumberWidth_m, ht, Qt::AlignRight, number);
        ++lineNumber;
        block = block.next();
    }
}

void LogEdit::resizeEvent(QResizeEvent *event){
    QPlainTextEdit::resizeEvent(event);
    QRect r = rect();
    lineNumberArea_m->setGeometry(QRect(r.left(), r.top(), lineNumberAreaWidth_m, r.height()));
}

void LogEdit::paintEvent(QPaintEvent *e){
    QPlainTextEdit::paintEvent(e);
    lineNumberArea_m->update();
    rehighLight(false);
}

void LogEdit::highlightRequested(){
    rehighLight(true);
}

