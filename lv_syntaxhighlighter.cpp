#include "lv_syntaxhighlighter.h"

const QFont::Weight SyntaxHighlighter::SEARCH_KEYWORD_FONT_WEIGHT = QFont::Bold;
const Qt::GlobalColor SyntaxHighlighter::SEARCH_KEYWORD_COLOR = Qt::red;

SyntaxHighlighter::SyntaxHighlighter(QTextDocument *parent) :
    QSyntaxHighlighter(parent)
{
    isRehighlightEnabled_m = false;
    searchKeywordFormat_m.setFontWeight(SEARCH_KEYWORD_FONT_WEIGHT);
    searchKeywordFormat_m.setForeground(SEARCH_KEYWORD_COLOR);

    setSearchKeyword("", false);
    PreferenceManager *pm = PreferenceManager::getInstance();
    connect(pm, SIGNAL(updated()), this, SLOT(generalRuleUpdated()));
}


void SyntaxHighlighter::enableSyntaxHighlight(bool enable){
    isRehighlightEnabled_m = enable;
}

bool SyntaxHighlighter::isEnabledSyntaxHilight(){
    return isRehighlightEnabled_m;
}

void SyntaxHighlighter::highlightBlock(const QString &text){
    if(!isRehighlightEnabled_m) return;

    for(int i=0; i<keywordRegexList_m.size(); i++){
        QRegExp regex = keywordRegexList_m.at(i);
        QTextCharFormat format = keywordFormatList_m.at(i);
        int index = text.indexOf(regex);
        while(index >= 0){
            int length = regex.matchedLength();
            setFormat(index, length, format);
            index = text.indexOf(regex, index + length);
        }
    }

    if(searchKeywordRegex_m.pattern() == "") return;
    int index = text.indexOf(searchKeywordRegex_m);
    while (index >= 0) {
        int length = searchKeywordRegex_m.matchedLength();
        setFormat(index, length, searchKeywordFormat_m);
        index = text.indexOf(searchKeywordRegex_m, index + length);
    }
}

void SyntaxHighlighter::setSearchKeyword(QString keyword, bool isCaseSensitive){
    searchKeywordRegex_m.setPattern(keyword);
    if(isCaseSensitive){
        searchKeywordRegex_m.setCaseSensitivity(Qt::CaseSensitive);
    }else{
        searchKeywordRegex_m.setCaseSensitivity(Qt::CaseInsensitive);
    }
}

void SyntaxHighlighter::setHighlightRules(QList<HighlightRule> rules){
    // clear
    groupRule_m = rules;
    generalRuleUpdated();
}

void SyntaxHighlighter::generalRuleUpdated(){
    keywordRegexList_m.clear();
    keywordFormatList_m.clear();

    QList<HighlightRule> highlightRules;
    highlightRules.append(groupRule_m);
    QList<HighlightRule> generalRules = (PreferenceManager::getInstance())->getHighlightRuleList();
    highlightRules.append(generalRules);

    foreach(HighlightRule rule, highlightRules){
        QRegExp expression(rule.getRegexString());
        if(rule.getCaseSensitive()){
            expression.setCaseSensitivity(Qt::CaseSensitive);
        }else{
            expression.setCaseSensitivity(Qt::CaseInsensitive);
        }

        keywordRegexList_m.append(expression);
        keywordFormatList_m.append(rule.getFormat());
    }

    emit requestRehighlight();
}

