
#include "core_preferencemanager.h"

const QString PreferenceManager::DB_RELATIVE_PATH = "/settings.db";

PreferenceManager::PreferenceManager() :
    QObject(NULL)
{
    PreferenceDataAccessor *accessor = new PreferenceDataAccessor(getAbsoluteSettingFilePath());
    accessor->open();
    accessor->correct();
    accessor->close();

    load();
}

//////////
/// BASIC
//////////

QString PreferenceManager::getAbsoluteSettingFilePath(){
    QString dirPath = QCoreApplication::applicationDirPath();
    return dirPath + DB_RELATIVE_PATH;
}

PreferenceManager* PreferenceManager::getInstance(){
    static PreferenceManager manager;
    return &manager;
}

void PreferenceManager::save(){
    PreferenceDataAccessor *accessor = new PreferenceDataAccessor(getAbsoluteSettingFilePath());
    accessor->open();
    accessor->updateEditorSettings(editorFont_m, editorFontSize_m, editorTextColor_m, editorBackgroundColor_m);
    accessor->updateHighlightRuleSettings(highlightRuleList_m);
    accessor->close();
    emit updated();
}

void PreferenceManager::load(){
    PreferenceDataAccessor *accessor = new PreferenceDataAccessor(getAbsoluteSettingFilePath());
    accessor->open();
    editorFont_m = accessor->getEditorFont();
    editorFontSize_m = accessor->getEditorFontSize();
    editorTextColor_m = accessor->getEditorTextColor();
    editorBackgroundColor_m = accessor->getEditorBackgroundColor();
    highlightRuleList_m = accessor->getHighlightRuleList();
    accessor->close();
}

//////////
/// Editor
//////////

QString PreferenceManager::getEditorFont(){
    return editorFont_m;
}

int PreferenceManager::getEditorFontSize(){
    return editorFontSize_m;
}

QString PreferenceManager::getEditorTextColor(){
    return editorTextColor_m;
}

QString PreferenceManager::getEditorBackgroundColor(){
    return editorBackgroundColor_m;
}

void PreferenceManager::setEditorFont(QString font){
    editorFont_m = font;
}

void PreferenceManager::setEditorFontSize(int size){
    editorFontSize_m = size;
}

void PreferenceManager::setEditorTextColor(QString color){
    editorTextColor_m = color;
}

void PreferenceManager::setEditorBackgroundColor(QString color){
    editorBackgroundColor_m = color;
}


//////////
/// Highlight rule
//////////

QList<HighlightRule> PreferenceManager::getHighlightRuleList(){
    return highlightRuleList_m;
}

void PreferenceManager::setHighLightRuleList(QList<HighlightRule> highlightRuleList){
    highlightRuleList_m = highlightRuleList;
}
