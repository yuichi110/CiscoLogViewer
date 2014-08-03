#ifndef DAO_COMMANDDATA_H
#define DAO_COMMANDDATA_H

#include <QtGui>

class CommandData
{
public:
    CommandData(QString name, QString decoratedName, QByteArray data);
    QString getName();
    QString getDecoratedName();
    QByteArray getData();

private:
    QString name_m;
    QString decoratedName_m;
    QByteArray data_m;
};

#endif // DAO_COMMANDDATA_H
