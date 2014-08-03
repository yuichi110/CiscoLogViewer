#ifndef LV_HIGHLIGHTRULE_H
#define LV_HIGHLIGHTRULE_H

#include <QtWidgets>

class HighlightRule
{
public:
    HighlightRule(QString regexString, QTextCharFormat format, bool caseSensitive);
    QString getRegexString();
    QTextCharFormat getFormat();
    bool getCaseSensitive();

private:
    QString regexString_m;
    QTextCharFormat format_m;
    bool caseSensitive_m;

};

#endif // LV_HIGHLIGHTRULE_H
