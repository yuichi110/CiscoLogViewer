#ifndef MYSYNTAXHIGHLIGHTER_H
#define MYSYNTAXHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QtGui>
#include "core_appinfo.h"
#include "core_messagebroker.h"
#include "lv_highlightrule.h"
#include "core_preferencemanager.h"

class SyntaxHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT
private:
    // search keyword
    static const QFont::Weight SEARCH_KEYWORD_FONT_WEIGHT;
    static const Qt::GlobalColor SEARCH_KEYWORD_COLOR;

    // enabled
    bool isRehighlightEnabled_m;

    // search keyword
    QRegExp searchKeywordRegex_m;
    QTextCharFormat searchKeywordFormat_m;

    // highlight rule
    QList<HighlightRule> groupRule_m;
    QList<QRegExp> keywordRegexList_m;
    QList<QTextCharFormat> keywordFormatList_m;

public:
    explicit SyntaxHighlighter(QTextDocument *parent);
    void setSearchKeyword(QString string, bool isCaseSensitive);
    void setHighlightRules(QList<HighlightRule> rules);
    bool isEnabledSyntaxHilight();
    void enableSyntaxHighlight(bool enable);

protected:
    void highlightBlock(const QString &text);

signals:
    void requestRehighlight();

public slots:
    void generalRuleUpdated();
};

#endif // MYSYNTAXHIGHLIGHTER_H
