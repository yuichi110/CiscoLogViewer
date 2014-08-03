#include "dao_preferencedataaccessor.h"

const QString PreferenceDataAccessor::CHECK_TABLE_EDITER_QUERY = "SELECT sql FROM sqlite_master WHERE type='table' AND name='pref_editer'";
const QString PreferenceDataAccessor::DROP_TABLE_EDITER_QUERY = "DROP TABLE pref_editer";
const QString PreferenceDataAccessor::CREATE_TABLE_EDITER_QUERY = "CREATE TABLE pref_editer (font TEXT, font_size INT, text_color TEXT, background_color TEXT)";
const QString PreferenceDataAccessor::INSERT_RAW_EDITER_QUERY = "INSERT INTO pref_editer VALUES ('%1', %2, '%3', '%4')";
const QString PreferenceDataAccessor::UPDATE_RAW_EDITER_QUERY = "UPDATE pref_editer SET font = '%1', font_size = %2, text_color = '%3', background_color = '%4'";
const QString PreferenceDataAccessor::SELECT_EDITER_QUERY = "SELECT * FROM pref_editer";

const QString PreferenceDataAccessor::CHECK_TABLE_HIGHLIGHT_QUERY = "SELECT sql FROM sqlite_master WHERE type='table' AND name='pref_highlight'";
const QString PreferenceDataAccessor::DROP_TABLE_HIGHLIGHT_QUERY = "DROP TABLE pref_highlight";
const QString PreferenceDataAccessor::CREATE_TABLE_HIGHLIGHT_QUERY = "CREATE TABLE pref_highlight (id INTEGER PRIMARY KEY AUTOINCREMENT, regex_string TEXT, case_sensitive INT, color TEXT, bold INT, italic INT, underline INT)";
const QString PreferenceDataAccessor::INSERT_RAW_HIGHLIGHT_QUERY = "INSERT INTO pref_highlight (regex_string, case_sensitive, color, bold, italic, underline) VALUES (:regex_string, :case_sensitive, :color, :bold, :italic, :underline)";
const QString PreferenceDataAccessor::DELETE_HIGHLIGHT_QUERY = "DELETE FROM pref_highlight";
const QString PreferenceDataAccessor::SELECT_HIGHLIGHT_QUERY = "SELECT regex_string, case_sensitive, color, bold, italic, underline FROM pref_highlight";

const int PreferenceDataAccessor::DOMAIN_INDEX = 0;
const int PreferenceDataAccessor::PORT_INDEX = 1;

PreferenceDataAccessor::PreferenceDataAccessor(QString filePath)
{
    db_m =  QSqlDatabase::addDatabase("QSQLITE");
    db_m.setDatabaseName(filePath);
}

void PreferenceDataAccessor::open(){
    if(db_m.isOpen()){
        qDebug() << "already open";
    }else{
        qDebug() << "open database()";
        db_m.open();
    }
}

void PreferenceDataAccessor::close(){
    if(db_m.isOpen()){
        QString connectionName = db_m.connectionName();
        db_m.close();
        delete &db_m;
        QSqlDatabase::removeDatabase(connectionName);
    }else{
        qDebug() << "not opened.";
    }
}

bool PreferenceDataAccessor::isOpen(){
    return db_m.isOpen();
}

void PreferenceDataAccessor::correct(){
    correctEditorTable();
    correctHighlightTable();
}

void PreferenceDataAccessor::correctEditorTable(){
    QSqlQuery query;
    bool allOk = true;

    // check Table exists
    do{
        query.exec(CHECK_TABLE_EDITER_QUERY);
        if(query.next()){
            // check Table syntax
            QString createTableQuery = query.value(0).toString();
            if(createTableQuery != CREATE_TABLE_EDITER_QUERY){
                qDebug() << "editor incorrect";
                allOk = false;
                break;
            }
        }else{
            qDebug() << "editor missing";
            allOk = false;
            break;
        }

        // check table has 1 or more raws.
        query.exec(SELECT_EDITER_QUERY);
        if(query.next()){
            //ok
        }else{
            allOk = false;
            break;
        }
    }while(false);

    if(!allOk){
        // This DB File have some problem.
        // initialize it.
        query.exec(DROP_TABLE_EDITER_QUERY);
        query.exec(CREATE_TABLE_EDITER_QUERY);
        QString insertQuery = QString(INSERT_RAW_EDITER_QUERY).arg("font_test", QString::number(10), "black", "white");
        query.exec(insertQuery);
    }
}

void PreferenceDataAccessor::correctHighlightTable(){
    QSqlQuery query;
    bool allOk = true;

    // check Table exists
    do{
        query.exec(CHECK_TABLE_HIGHLIGHT_QUERY);
        if(query.next()){
            // check Table syntax
            QString createTableQuery = query.value(0).toString();
            if(createTableQuery != CREATE_TABLE_HIGHLIGHT_QUERY){
                qDebug() << "highlight incorrect";
                allOk = false;
                break;
            }
        }else{
            qDebug() << "highlight missing";
            allOk = false;
            break;
        }
    }while(false);

    if(!allOk){
        // This DB File have some problem.
        // initialize it.
        query.exec(DROP_TABLE_HIGHLIGHT_QUERY);
        query.exec(CREATE_TABLE_HIGHLIGHT_QUERY);
    }
}

QString PreferenceDataAccessor::getItem(int index){
    QSqlQuery query;
    query.exec(SELECT_EDITER_QUERY);
    if(query.next()){
        return query.value(index).toString();
    }

    return "";
}

QString PreferenceDataAccessor::getEditorFont(){
    QString value = getItem(0);
    if(value == ""){
        // default font
        value = "";
    }

    return value;
}

int PreferenceDataAccessor::getEditorFontSize(){
    QString value = getItem(1);
    bool ok;
    int size = value.toInt(&ok);
    if(!ok){
        // default
        size = 12;
    }

    return size;
}

QString PreferenceDataAccessor::getEditorTextColor(){
    QString value = getItem(2);
    if(value == ""){
        // default color
        value = "black";
    }

    return value;
}

QString PreferenceDataAccessor::getEditorBackgroundColor(){
    QString value = getItem(3);
    if(value == ""){
        // default color
        value = "white";
    }

    return value;
}

void PreferenceDataAccessor::updateEditorSettings(QString font, int fontSize, QString textColor, QString backgroundColor){
    QString updateQuery = QString(UPDATE_RAW_EDITER_QUERY).arg(font, QString::number(fontSize),
                                                               textColor, backgroundColor);
    QSqlQuery query;
    query.exec(updateQuery);
}

QList<HighlightRule> PreferenceDataAccessor::getHighlightRuleList(){
    QList<HighlightRule> ruleList;
    QSqlQuery query;
    query.exec(SELECT_HIGHLIGHT_QUERY);
    while(query.next()){
        QString regexString = query.value(0).toString();

        bool caseSensitive = true;
        if(query.value(1).toInt() == 0){
            caseSensitive = false;
        }

        QString textColor = query.value(2).toString();

        bool bold = true;
        if(query.value(3).toInt() == 0){
            bold = false;
        }

        bool italic = true;
        if(query.value(4).toInt() == 0){
            italic = false;
        }

        bool underline = true;
        if(query.value(5).toInt() == 0){
            underline = false;
        }

        QTextCharFormat format;
        QColor color(textColor);
        format.setForeground(color);
        if(bold) format.setFontWeight(QFont::Bold);
        if(italic) format.setFontItalic(true);
        if(underline) format.setFontUnderline(true);

        HighlightRule rule(regexString, format, caseSensitive);
        ruleList.append(rule);
    }

    return ruleList;
}

void PreferenceDataAccessor::updateHighlightRuleSettings(QList<HighlightRule> ruleList){
    QSqlQuery query;
    query.exec(DELETE_HIGHLIGHT_QUERY);
    foreach(HighlightRule rule, ruleList){
        QString regexString = rule.getRegexString();
        if(regexString.trimmed() == ""){
            continue;
        }

        int caseSensitive = 0;
        if(rule.getCaseSensitive()){
            caseSensitive = 1;
        }
        QTextCharFormat format = rule.getFormat();
        QColor color = format.foreground().color();
        QString textColor = color.name();
        int bold = 0;
        if(format.fontWeight() == QFont::Bold){
            bold = 1;
        }
        int italic = 0;
        if(format.fontItalic()){
            italic = 1;
        }
        int underline = 0;
        if(format.fontUnderline()){
            underline = 1;
        }

        query.prepare(INSERT_RAW_HIGHLIGHT_QUERY);
        query.bindValue(":regex_string", regexString);
        query.bindValue(":case_sensitive", caseSensitive);
        query.bindValue(":color", textColor);
        query.bindValue(":bold", bold);
        query.bindValue(":italic", italic);
        query.bindValue(":underline", underline);
        query.exec();
        qDebug() << query.lastQuery();
    }
}
