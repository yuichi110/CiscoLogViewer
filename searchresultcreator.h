#ifndef SEARCHRESULTCREATOR_H
#define SEARCHRESULTCREATOR_H

#include <QThread>
#include <QtGui>

class SearchResultCreator : public QThread
{
    Q_OBJECT

private:
    static const bool DEBUG;

    QString _originalFilePath;
    QString _searchFilePath;
    QString _keyword;
    bool _isResultFileExist;
    bool _isCompleted;
    bool createSearchedFile(QString keyword, QString outPath);

public:
    explicit SearchResultCreator(QString originalFilePath, QString SearchFileName, QString keyword);
    QString getFilePath();
    QString getKeyword();
    bool isFileCreationCompleted();
    bool isResultFileExist();

protected:
    void run();

signals:
    void signalProgressValue(int value);
    void signalProgressMaximum(int value);


public slots:

    
};

#endif // SEARCHRESULTCREATOR_H
