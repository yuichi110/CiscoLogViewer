#include "mwc_dropzone.h"

DropZone::DropZone(QWidget *parent, MessageBroker *messageBroker) :
    QLabel(parent)
{
    messageBroker_m = messageBroker;

    setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    QPixmap pic(AppInfo::DZ_ICON);
    QPixmap scaled=pic.scaled (AppInfo::WINDOW_DZ_WIDTH, AppInfo::WINDOW_DZ_HEIGHT,
                               Qt::IgnoreAspectRatio, Qt::FastTransformation );
    setPixmap(scaled);
    setAcceptDrops(true);
}

void DropZone::dragEnterEvent(QDragEnterEvent *event){
    QList<QUrl> urls = event->mimeData()->urls();
    QList<QString> pathList = urlsToPathList(urls);
    if(pathList.count() != 1){
        return;
    }

    if(messageBroker_m->messageDropZone_isFileOK(pathList.at(0))){
        event->acceptProposedAction();
    }
}

void DropZone::dropEvent(QDropEvent *event){
    QList<QUrl> urls = event->mimeData()->urls();
    QList<QString> pathList = urlsToPathList(urls);
    if(pathList.count() != 1){
        return;
    }

    QString clvFilePath = pathList.at(0);
    if(messageBroker_m->messageDropZone_isFileOK(clvFilePath)){
        messageBroker_m->messageDropZone_clvFileDropped(clvFilePath);
    }
}

QList<QString> DropZone::urlsToPathList(QList<QUrl> urls){
    QList<QString> pathList;
    foreach(QUrl url, urls){
        QString path = url.toLocalFile();
        pathList.append(path);
    }
    return pathList;
}
