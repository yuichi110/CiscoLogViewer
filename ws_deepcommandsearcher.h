#ifndef WS_DEEPCOMMANDSEARCHER_H
#define WS_DEEPCOMMANDSEARCHER_H

#include <QThread>
#include "dao_clvdataaccessor.h"

class DeepCommandSearcher : public QThread
{
    Q_OBJECT
public:
    explicit DeepCommandSearcher(QObject *parent, QString clvFilePath);
    void setSearchText(QString searchText);

protected:
    void run();

private:
    QString clvFilePath_m;
    QString searchText_m;

signals:
    void signalSetProgressMaximumValue(int max);
    void signalSetProgressValue(int value);
    void signalSetProgressString(QString string);
    void signalSearchFinished(QString idListString);

public slots:
    void setProgressValue(int value);
};

#endif // WS_DEEPCOMMANDSEARCHER_H
