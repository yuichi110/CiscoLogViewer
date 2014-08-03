#ifndef WS_ONECOMMANDWIDGET_H
#define WS_ONECOMMANDWIDGET_H

#include <QtWidgets>
#include "ws_onecommandedit.h"

class OneCommandEdit;

class OneCommandWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OneCommandWidget(QWidget *parent, QString command, QString contents);

private:
    QLineEdit *searchWordLineEdit_m;
    QCheckBox *caseSensitiveCheckBox_m;
    OneCommandEdit *textEdit_m;

protected:
    bool eventFilter(QObject *obj, QEvent *e);

signals:

public slots:
    void findForward();
    void findBackward();
    void keywordChanged();
    void controlF();
};

#endif // WS_ONECOMMANDWIDGET_H
