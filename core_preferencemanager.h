#ifndef PREFERENCEMANAGER_H
#define PREFERENCEMANAGER_H

#include "dao_preferencedataaccessor.h"
#include "lv_highlightrule.h"

class PreferenceManager : public QObject
{
    Q_OBJECT

public:
    // base
    static PreferenceManager* getInstance();
    void load();
    void save();

    // editor
    QString getEditorFont();
    int getEditorFontSize();
    QString getEditorTextColor();
    QString getEditorBackgroundColor();
    void setEditorFont(QString font);
    void setEditorFontSize(int size);
    void setEditorTextColor(QString color);
    void setEditorBackgroundColor(QString color);

    // highlight rule
    QList<HighlightRule> getHighlightRuleList();
    void setHighLightRuleList(QList<HighlightRule> list);

private:
    const static QString DB_RELATIVE_PATH;
    explicit PreferenceManager();
    QString getAbsoluteSettingFilePath();

    // editor
    QString editorFont_m;
    int editorFontSize_m;
    QString editorTextColor_m;
    QString editorBackgroundColor_m;

    // highlight
    QList<HighlightRule> highlightRuleList_m;



signals:
    void updated();

public slots:

protected:
    
};


#endif // PREFERENCEMANAGER_H
