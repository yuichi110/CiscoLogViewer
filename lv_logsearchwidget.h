#ifndef LV_LOGSEARCHWIDGET_H
#define LV_LOGSEARCHWIDGET_H

#include <QtWidgets>
#include "lv_logmodel.h"

class LogModel;
class LogSearchWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LogSearchWidget(QWidget *parent, LogModel *eventManager, bool isShowPopupButton);
    QString getKeyword();
    bool getCaseSensitive();
    void focusOnSearchTextField();

private:
    LogModel *eventManager_m;
    QLineEdit* searchWordLineEdit_m;
    QCheckBox* caseSensitiveCheckBox_m;
    QPushButton* bkButton_m;
    QPushButton* fwdButton_m;

protected:
    virtual void keyPressEvent(QKeyEvent *e);

signals:
    /*
    void searchNext(QString keyword, bool caseSensitive);
    void searchBefore(QString keyword, bool caseSensitive);
    void popupButtonClicked();
    */
public slots:

};

#endif // LV_LOGSEARCHWIDGET_H
