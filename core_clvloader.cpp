#include "core_clvloader.h"

ClvLoader::ClvLoader(MessageBroker *messageBroker)
{
    clvFileLoaded_m = false;
    clvFilePath_m = "";
    messageBroker_m = messageBroker;
    messageBroker->registerClvLoader(this);
}

bool ClvLoader::checkClvFile(QString filePath){
    if(!filePath.endsWith(".clv")){
        return false;
    }
    QFile file(filePath);
    if(!file.exists()){
        return false;
    }

    ClvDataAccessor *accessor = new ClvDataAccessor(filePath);
    accessor->open();
    bool isOk = accessor->checkTableSyntax();
    accessor->close();
    return isOk;
}

void ClvLoader::loadClvFile(QString filePath){
    // WorkSpace
    clvFileLoaded_m = true;
    clvFilePath_m = filePath;
    messageBroker_m->messageClvLoader_createWsTab(filePath);

    // Layer and Group
    ClvDataAccessor *accessor = new ClvDataAccessor(filePath);
    accessor->open();
    QList<QString> layerList = accessor->getLayerList();
    QMap<QString, QList<QString> > layerMap = accessor->getLayerMap();
    accessor->close();

    messageBroker_m->messageClvLoader_disableOpenMenu();
    messageBroker_m->messageClvLoader_createLayerAndGroupTab(layerList, layerMap, filePath);
}

QString ClvLoader::getClvFilePath(){
    return clvFilePath_m;
}

bool ClvLoader::getLoaded(){
    return clvFileLoaded_m;
}

