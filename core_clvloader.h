#ifndef CORE_CLVLOADER_H
#define CORE_CLVLOADER_H

#include <QtGui>
#include "core_messagebroker.h"
#include "dao_clvdataaccessor.h"

class MessageBroker;

class ClvLoader
{
public:
    ClvLoader(MessageBroker *messageBroker);
    bool checkClvFile(QString filePath);
    void loadClvFile(QString filePath);
    QString getClvFilePath();
    bool getLoaded();

private:
    MessageBroker *messageBroker_m;
    bool clvFileLoaded_m;
    QString clvFilePath_m;
};

#endif // CORE_CLVLOADER_H
