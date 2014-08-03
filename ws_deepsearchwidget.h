#ifndef WS_DEEPSEARCHWIDGET_H
#define WS_DEEPSEARCHWIDGET_H

#include <QtWidgets>
#include "lv_logview.h"
#include "dao_clvdataaccessor.h"
#include "ws_progressdialog.h"
#include "ws_deepcommandsearcher.h"

class DeepSearchWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DeepSearchWidget(QWidget *parent, QString clvFilePath);

private:
    static const QString GROUP_SEARCH;
    QString clvFilePath_m;
    QLineEdit *searchWordArea_m;
    LogView *searchLogView_m;

    DeepCommandSearcher *searcher_m;
    ProgressDialog *progressDialog_m;

protected:
    bool eventFilter(QObject *obj, QEvent *event);

signals:

public slots:
    void searchButtonClicked();
    void searchFinished(QString);
};

#endif // WS_DEEPSEARCHWIDGET_H
