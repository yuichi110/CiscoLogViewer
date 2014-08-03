#ifndef CONFIGTEXTEDIT_H
#define CONFIGTEXTEDIT_H

#include <QtGui>
#include <QtWidgets>
#include "core_messagebroker.h"
#include "lv_logmodel.h"
#include "lv_syntaxhighlighter.h"

class LogModel;
class SyntaxHighlighter;

class LogEdit : public QPlainTextEdit
{
    Q_OBJECT

private:
    SyntaxHighlighter *syntaxHighlighter_m;

    // LINE NUMBER AREA
    int lineNumberWidth_m;
    int lineNumberAreaWidth_m;
    int previousHeadBlock_m;
    QWidget *lineNumberArea_m;

public:
    explicit LogEdit(QWidget *parent, LogModel *eventManager);
    //void setWindowStyle(QColor backgroundColor, QColor textColor, QColor clBackgroundColor, QColor clTextColor);

    // SYNTAX HIGHLIGHTER
    void setSearchKeyword(QString string, bool isCaseSensitive);
    void rehighLight(bool isForce);
    void enableSyntaxHighlight(bool enable);
    void jumpToLine(int lineNumber);

protected:
    virtual void keyPressEvent(QKeyEvent *e);
    virtual void keyReleaseEvent(QKeyEvent *e);
    bool eventFilter(QObject *obj, QEvent *event);
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *e);

private:
    LogModel *eventManager_m;
    void drawLineNumbers();

private slots:
    void highlightCurrentLine();
    void highlightRequested();

signals:

};

#endif // CONFIGTEXTEDIT_H
