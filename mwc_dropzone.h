#ifndef MWC_DROPZONE_H
#define MWC_DROPZONE_H

#include <QtWidgets>
#include "core_appinfo.h"
#include "core_messagebroker.h"

class DropZone : public QLabel
{
    Q_OBJECT
public:
    explicit DropZone(QWidget *parent, MessageBroker *messageBroker);

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);

private:
    MessageBroker *messageBroker_m;
    QList<QString> urlsToPathList(QList<QUrl> urls);

signals:

public slots:

};

#endif // MWC_DROPZONE_H
