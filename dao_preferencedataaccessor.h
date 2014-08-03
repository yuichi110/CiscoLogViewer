#ifndef PREFERENCEDATAACCESSOR_H
#define PREFERENCEDATAACCESSOR_H

#include <QtSql>
#include "core_appinfo.h"
#include "lv_highlightrule.h"

class PreferenceDataAccessor
{
public:
    PreferenceDataAccessor(QString filePath);
    void open();
    void close();
    bool isOpen();
    void correct();

    QString getEditorFont();
    int getEditorFontSize();
    QString getEditorTextColor();
    QString getEditorBackgroundColor();
    void updateEditorSettings(QString font, int fontSize, QString textColor, QString backgroundColor);

    QList<HighlightRule> getHighlightRuleList();
    void updateHighlightRuleSettings(QList<HighlightRule> rule);

private:
    static const QString CHECK_TABLE_EDITER_QUERY;
    static const QString DROP_TABLE_EDITER_QUERY;
    static const QString CREATE_TABLE_EDITER_QUERY;
    static const QString INSERT_RAW_EDITER_QUERY;
    static const QString UPDATE_RAW_EDITER_QUERY;
    static const QString SELECT_EDITER_QUERY;

    static const QString CHECK_TABLE_HIGHLIGHT_QUERY;
    static const QString DROP_TABLE_HIGHLIGHT_QUERY;
    static const QString CREATE_TABLE_HIGHLIGHT_QUERY;
    static const QString INSERT_RAW_HIGHLIGHT_QUERY;
    static const QString DELETE_HIGHLIGHT_QUERY;
    static const QString SELECT_HIGHLIGHT_QUERY;

    static const int DOMAIN_INDEX;
    static const int PORT_INDEX;

    QSqlDatabase db_m;
    void correctEditorTable();
    void correctHighlightTable();
    QString getItem(int index);
};

#endif // PREFERENCEDATAACCESSOR_H
