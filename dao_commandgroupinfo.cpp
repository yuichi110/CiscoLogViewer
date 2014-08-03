#include "dao_commandgroupinfo.h"

CommandGroupInfo::CommandGroupInfo(QString command, QString layer, QString group)
{
    command_m = command;
    layer_m = layer;
    group_m = group;
}

QString CommandGroupInfo::getCommand(){
    return command_m;
}

QString CommandGroupInfo::getLayer(){
    return layer_m;
}

QString CommandGroupInfo::getGroup(){
    return group_m;
}
