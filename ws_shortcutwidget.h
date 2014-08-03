#ifndef WS_SHORTCUTWIDGET_H
#define WS_SHORTCUTWIDGET_H

#include <QWidget>
#include "core_messagebroker.h"
#include "ws_shortcutbutton.h"

class ShortcutWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ShortcutWidget(QWidget *parent, MessageBroker *messageBroker);
    void addShortcutButton(QString layer, QString group);

private:
    static const int BUTTON_WIDTH;
    static const int BUTTON_SPACE;
    static const int MARGIN;

    MessageBroker *messageBroker_m;
    QHBoxLayout *layout_m;
    QList<QString> oldLayerList_m;
    QList<QString> oldGroupList_m;

    int getIndexOfSameContents(QString layer, QString group);

protected:
    void resizeEvent(QResizeEvent *event);
    bool eventFilter(QObject *obj, QEvent *event);

signals:

public slots:

};

#endif // WS_SHORTCUTWIDGET_H
