#include "dao_commanddata.h"

CommandData::CommandData(QString name, QString decoratedName, QByteArray data)
{
    name_m = name;
    decoratedName_m = decoratedName;
    data_m = data;
}

QString CommandData::getName(){
    return name_m;
}

QString CommandData::getDecoratedName(){
    return decoratedName_m;
}

QByteArray CommandData::getData(){
    return data_m;
}
