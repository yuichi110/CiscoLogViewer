#ifndef SEARCHTABMANAGER_H
#define SEARCHTABMANAGER_H

#include <QWidget>
#include <QtGui>
#include "searchresultcreator.h"
#include "configtextview.h"
#include "mainwindow.h"
#include "savingmanager.h"
#include "messagebroker.h"

class MainWindow;
class MessageBroker;
class SearchTabManager : public QWidget
{
    Q_OBJECT
private:
    static const bool DEBUG;

    QString directoryPath;
    MainWindow *window;

    QList<QString> keywordList;
    QList<QString> pathList;
    QLineEdit *lineEdit;
    QPushButton *searchButton;

    int fileIndex;
    QTabWidget *searchResultTab;

    SearchResultCreator *srCreator;
    QProgressDialog *progressDialog;

    QList<int> searchList;
    QMap<int, QString> keywordMap;
    QString getFileNameFromIndex(int index);
    int getIndexFromFileName(QString fileName);
    MessageBroker *messageBroker_m;

public:
    explicit SearchTabManager(QWidget *parent, QString _directoryPath, MainWindow* _window);
    void loadSyntaxRule();
    QList<int> getSearchList();
    QString getSearchKeyword(int index);
    QMap<int, QString> getKeywordMap();
    void restoreSearchTab(QMap<int, QString> keywordMap);

signals:
    
public slots:
    void createSearchResultTab();
    void closeTab(int index);
    void indexOfSearchTabChanged();

    void setProgressMaximum(int max);
    void setProgressValue(int value);
    void progressCanceld();
    void creationComplete();


};

#endif // SEARCHTABMANAGER_H
