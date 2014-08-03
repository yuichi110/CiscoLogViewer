#include "ws_deepcommandsearcher.h"

DeepCommandSearcher::DeepCommandSearcher(QObject *parent, QString clvFilePath) :
    QThread(parent)
{
    clvFilePath_m = clvFilePath;
    searchText_m = "";
}

void DeepCommandSearcher::setSearchText(QString searchText){
    searchText_m = searchText;
}

void DeepCommandSearcher::run(){
    QList<int> idList;
    if(searchText_m == ""){
        emit signalSearchFinished("");
        return;
    }

    emit signalSetProgressString("Searching match command.");
    emit signalSetProgressMaximumValue(100);

    ClvDataAccessor *accessor = new ClvDataAccessor(clvFilePath_m);
    accessor->open();
    idList = accessor->getIdList(searchText_m, this);
    accessor->close();
    if(idList.length() == 0){
        emit signalSearchFinished("");
        return;
    }

    QString idListString = "";
    int length = idList.length();
    for(int i=0; i<length; i++){
        if(i != 0){
            idListString = QString("%1,%2").arg(idListString, QString::number(idList.at(i)));
        }else{
            idListString = QString::number(idList.at(0));
        }
    }

    emit signalSetProgressValue(100);

    emit signalSearchFinished(idListString);
}

void DeepCommandSearcher::setProgressValue(int value){
    emit signalSetProgressValue(value);
}
