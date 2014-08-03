#ifndef THREADEDTEXTLOADER_H
#define THREADEDTEXTLOADER_H

#include <QThread>
#include <QtGui>
#include "dao_clvdataaccessor.h"
#include "dao_commanddata.h"

class CommandLoader : public QThread
{
    Q_OBJECT

private:
    static const int CHUNK_SIZE;
    QString group_m;
    QString clvPath_m;
    bool idListMode_m;
    QList<int> idList_m;

public:
    explicit CommandLoader(QString group_m, QString clvPath);
    void run();
    void setGroupLoadMode();
    void setIdListMode(QList<int> idList);
    int loadCommand(int commandNumber, int currentLine, QString command, QByteArray data);

signals:
    void signalAppendString(QString line);
    void signalInsertCommand(int commandPosition, QString commandName, int startLinePosition);
    void signalDoneLoading();

public slots:
    
};


#endif // THREADEDTEXTLOADER_H
