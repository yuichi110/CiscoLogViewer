#include "lv_commandloader.h"

const int CommandLoader::CHUNK_SIZE = 1000000;

CommandLoader::CommandLoader(QString group, QString clvPath) :
    QThread(NULL)
{
    group_m = group;
    clvPath_m = clvPath;
    idListMode_m = false;
}

void CommandLoader::setGroupLoadMode(){
    idListMode_m = false;
}

void CommandLoader::setIdListMode(QList<int> idList){
    idList_m = idList;
    idListMode_m = true;
}

void CommandLoader::run(){
    ClvDataAccessor *reader = new ClvDataAccessor(clvPath_m);
    reader->open();
    QList<CommandData> commandDataList;
    if(idListMode_m){
        commandDataList = reader->getCommandDataList(idList_m);
    }else{
        commandDataList = reader->getCommandDataList(group_m);
    }
    reader->close();

    int commandCounter = 0;
    int lineCounter = 0;
    foreach(CommandData commandData, commandDataList){
        lineCounter = loadCommand(commandCounter, lineCounter,
                                  commandData.getDecoratedName(),
                                  commandData.getData());
        commandCounter++;
    }
    emit signalDoneLoading();
}

int CommandLoader::loadCommand(int commandNumber, int currentLine, QString commandName, QByteArray data){

    // tree
    emit signalInsertCommand(commandNumber, commandName, currentLine + 1);

    // editer
    QString text = QString(qUncompress(data));
    for(int i=0; i*CHUNK_SIZE < text.length(); i++){
        QString chunk = text.mid(i*CHUNK_SIZE, CHUNK_SIZE);
        emit signalAppendString(chunk);
    }

    // update current line number
    return currentLine + text.count("\n");
}
