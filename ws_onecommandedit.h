#ifndef WS_ONECOMMANDEDIT_H
#define WS_ONECOMMANDEDIT_H

#include <QPlainTextEdit>
#include "lv_syntaxhighlighter.h"
#include "ws_onecommandwidget.h"

class OneCommandEdit : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit OneCommandEdit(QWidget *parent);
    void setSearchKeyword(QString string, bool isCaseSensitive);
    void rehighLight(bool isForce);

protected:
    virtual void keyPressEvent(QKeyEvent *e);
    virtual void keyReleaseEvent(QKeyEvent *e);

private:
    SyntaxHighlighter *syntaxHighlighter_m;
    int previousHeadBlock_m;
    bool flag_ControlKey_m;
    bool flag_ShiftKey_m;
    bool flag_MetaKey_m;

    bool isProhibitedCntKey(int key);

signals:
    void findForward();
    void findBackward();
    void controlF();

public slots:

private slots:
    void highlightCurrentLine();

};

#endif // WS_ONECOMMANDEDIT_H
