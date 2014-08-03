#include "lv_highlightrule.h"

HighlightRule::HighlightRule(QString regexString, QTextCharFormat format, bool caseSensitive)
{
    regexString_m = regexString;
    format_m = format;
    caseSensitive_m = caseSensitive;
}

QString HighlightRule::getRegexString(){
    return regexString_m;
}

QTextCharFormat HighlightRule::getFormat(){
    return format_m;
}

bool HighlightRule::getCaseSensitive(){
    return caseSensitive_m;
}
