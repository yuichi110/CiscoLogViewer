#ifndef DAO_COMMANDGROUPINFO_H
#define DAO_COMMANDGROUPINFO_H

#include <QtGui>

class CommandGroupInfo
{
public:
    CommandGroupInfo(QString command, QString layer, QString group);
    QString getCommand();
    QString getLayer();
    QString getGroup();
private:
    QString command_m;
    QString layer_m;
    QString group_m;
};

#endif // DAO_COMMANDGROUPINFO_H
