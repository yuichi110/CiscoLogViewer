#include "dao_clvdataaccessor.h"

/////////////////
///  BASIC FUNCTIONS
/////////////////

ClvDataAccessor::ClvDataAccessor(QString filePath)
    //:QObject(NULL)
{
    db_m =  QSqlDatabase::addDatabase("QSQLITE");
    db_m.setDatabaseName(filePath);
}

void ClvDataAccessor::open(){
    if(db_m.isOpen()){
        qDebug() << "Database is already opened.";
    }else{
        db_m.open();
    }
}

bool ClvDataAccessor::isOpen(){
    return db_m.isOpen();
}

void ClvDataAccessor::close(){
    if(db_m.isOpen()){
        QString connectionName = db_m.connectionName();
        db_m.close();
        delete &db_m;
        QSqlDatabase::removeDatabase(connectionName);
    }else{
        qDebug() << "Database is not opened.";
    }
}

QSqlQuery ClvDataAccessor::execSql(QSqlQuery query){
    bool success = query.exec();
    if(AppInfo::DEBUG_CLV_DATA_ACCESSOR){
        qDebug() << "EXEC SQL: " << query.lastQuery();
    }
    if(!success){
        qDebug();
        qDebug() << QString("SQL Error:'%1'").arg(query.executedQuery());
        qDebug() << query.lastError().text();
        qDebug();
    }
    return query;
}

bool ClvDataAccessor::checkTableSyntax(){
    QList<QString> tableList;
    QList<QString> checkList;
    QList<QString> createList;

    tableList.append(PROJECT_TABLE);
    checkList.append(PROJECT_CHECK_TABLE);
    createList.append(PROJECT_CREATE_TABLE);

    tableList.append(COMMAND_TABLE);
    checkList.append(COMMAND_CHECK_TABLE);
    createList.append(COMMAND_CREATE_TABLE);

    tableList.append(GROUP_TABLE);
    checkList.append(GROUP_CHECK_TABLE);
    createList.append(GROUP_CREATE_TABLE);

    tableList.append(HIGHLIGHT_TABLE);
    checkList.append(HIGHLIGHT_CHECK_TABLE);
    createList.append(HIGHLIGHT_CREATE_TABLE);

    tableList.append(LAYER_TABLE);
    checkList.append(LAYER_CHECK_TABLE);
    createList.append(LAYER_CREATE_TABLE);

    tableList.append(SEARCH1_TABLE);
    checkList.append(SEARCH1_CHECK_TABLE);
    createList.append(SEARCH1_CREATE_TABLE);

    tableList.append(SEARCH2_TABLE);
    checkList.append(SEARCH2_CHECK_TABLE);
    createList.append(SEARCH2_CREATE_TABLE);

    tableList.append(BOOKMARK_TABLE);
    checkList.append(BOOKMARK_CHECK_TABLE);
    createList.append(BOOKMARK_CREATE_TABLE);

    tableList.append(MEMO_TABLE);
    checkList.append(MEMO_CHECK_TABLE);
    createList.append(MEMO_CREATE_TABLE);

    bool isAllOK = true;
    for(int i=0; i<tableList.length(); i++){
        bool isOK = checkTableSyntax2(tableList.at(i), checkList.at(i), createList.at(i));
        if(!isOK){
            isAllOK = false;
            break;
        }
    }

    return isAllOK;
}

bool ClvDataAccessor::checkTableSyntax2(QString tableString, QString checkQuery, QString createQuery){
    bool isOk = false;

    QSqlQuery query;
    query.prepare(checkQuery);
    execSql(query);
    if(query.next()){
        if(AppInfo::DEBUG_CLV_DATA_ACCESSOR) qDebug() << QString("Table '%1' exists.").arg(tableString);
        QString pastCreateQuery = query.value(0).toString();
        isOk = (createQuery == pastCreateQuery);
    }

    return isOk;
}

void ClvDataAccessor::initialize(){
    QList<QString> tableList;
    QList<QString> dropList;
    QList<QString> createList;

    tableList.append(PROJECT_TABLE);
    dropList.append(PROJECT_DROP_TABLE);
    createList.append(PROJECT_CREATE_TABLE);

    tableList.append(COMMAND_TABLE);
    dropList.append(COMMAND_DROP_TABLE);
    createList.append(COMMAND_CREATE_TABLE);

    tableList.append(GROUP_TABLE);
    dropList.append(GROUP_DROP_TABLE);
    createList.append(GROUP_CREATE_TABLE);

    tableList.append(HIGHLIGHT_TABLE);
    dropList.append(HIGHLIGHT_DROP_TABLE);
    createList.append(HIGHLIGHT_CREATE_TABLE);

    tableList.append(LAYER_TABLE);
    dropList.append(LAYER_DROP_TABLE);
    createList.append(LAYER_CREATE_TABLE);

    tableList.append(SEARCH1_TABLE);
    dropList.append(SEARCH1_DROP_TABLE);
    createList.append(SEARCH1_CREATE_TABLE);

    tableList.append(SEARCH2_TABLE);
    dropList.append(SEARCH2_DROP_TABLE);
    createList.append(SEARCH2_CREATE_TABLE);

    tableList.append(BOOKMARK_TABLE);
    dropList.append(BOOKMARK_DROP_TABLE);
    createList.append(BOOKMARK_CREATE_TABLE);

    tableList.append(MEMO_TABLE);
    dropList.append(MEMO_DROP_TABLE);
    createList.append(MEMO_CREATE_TABLE);

    for(int i=0; i<tableList.length(); i++){
        initialize2(tableList.at(i), dropList.at(i), createList.at(i));
    }
}

void ClvDataAccessor::initialize2(QString table, QString dropQuery, QString createQuery){
    if(AppInfo::DEBUG_CLV_DATA_ACCESSOR) qDebug() << "initialize table: " << table;
    QSqlQuery query;
    query.prepare(dropQuery);
    execSql(query);
    query.prepare(createQuery);
    execSql(query);
}

QString ClvDataAccessor::getCurrentDateString(){
    QDateTime time = QDateTime::currentDateTime();
    return time.toString("yyyy-MM-dd hh:mm:ss");
}

/////////////////
///  PROJECT INFORMATION HANDLING
/////////////////

void ClvDataAccessor::writeProjectInfo(QString product){
    QSqlQuery query;
    query.prepare(PROJECT_INSERT_TO_TABLE);
    query.bindValue(BIND_MAJOR_VERSION, AppInfo::MAJOR_VERSION);
    query.bindValue(BIND_MINOR_VERSION, AppInfo::MINOR_VERSION);
    query.bindValue(BIND_PRODUCT, product);
    query.bindValue(BIND_CREATE_DATE, getCurrentDateString());
    query.bindValue(BIND_UPDATE_DATE, getCurrentDateString());
    execSql(query);
}


/////////////////
///  COMMAND TABLE
/////////////////

void ClvDataAccessor::writeCommand(QString name, QString decoratedName, QString scope, QString tag, QString file, QByteArray data){
    QSqlQuery query;
    query.prepare(COMMAND_INSERT_TO_TABLE);
    query.bindValue(BIND_NAME, name);
    query.bindValue(BIND_DECORATED_NAME, decoratedName);
    query.bindValue(BIND_SCOPE, scope);
    query.bindValue(BIND_TAG, tag);
    query.bindValue(BIND_FILE, file);
    query.bindValue(BIND_DATA, data);
    execSql(query);
}

void ClvDataAccessor::updateCommand(QString layer, QString group, QList<int> idList){
    foreach(int id, idList){
        QString sql = QString(COMMAND_UPDATE_GROUP_RAYER).arg(layer, group, QString::number(id));
        QSqlQuery query;
        query.prepare(sql);
        execSql(query);
    }
}

QList<CommandGroupInfo> ClvDataAccessor::getCommandGroupInfoList(){
    QList<CommandGroupInfo> cgiList;

    QSqlQuery query;
    query.prepare(COMMAND_SELECT_COMMAND_LAYER_GROUP);
    query = execSql(query);
    while(query.next()){
        QString command = query.value(0).toString();
        QString layer = query.value(1).toString();
        QString group = query.value(2).toString();
        CommandGroupInfo cgi(command, layer, group);
        cgiList.append(cgi);
    }

    return cgiList;
}

QList<CommandGroupInfo> ClvDataAccessor::getCommandGroupInfoListNone(){
    QList<CommandGroupInfo> cgiList;

    QSqlQuery query;
    query.prepare(COMMAND_SELECT_COMMAND_LAYER_GROUP_NONE);
    query = execSql(query);
    while(query.next()){
        QString command = query.value(0).toString();
        QString layer = query.value(1).toString();
        QString group = query.value(2).toString();
        CommandGroupInfo cgi(command, layer, group);
        cgiList.append(cgi);
    }

    return cgiList;
}

QList<CommandGroupInfo> ClvDataAccessor::getCommandGroupInfoList(QString filter, int limit){
    QList<CommandGroupInfo> cgiList;

    QString likeKeyword = "%" + filter + "%";
    QString sql = QString(COMMAND_SELECT_COMMAND_LAYER_GROUP_WHERE).arg(likeKeyword, QString::number(limit));
    QSqlQuery query;
    query.prepare(sql);
    query = execSql(query);
    while(query.next()){
        QString command = query.value(0).toString();
        QString layer = query.value(1).toString();
        QString group = query.value(2).toString();
        //qDebug() << command << " : " << layer << " : " << group;
        CommandGroupInfo cgi(command, layer, group);
        cgiList.append(cgi);
    }

    return cgiList;
}

QByteArray ClvDataAccessor::getCommandData(QString command){
    QString sql = QString(COMMAND_SELECT_DATA).arg(command);
    QSqlQuery query;
    query.prepare(sql);
    query = execSql(query);
    if(query.next()){
        QByteArray array = query.value(0).toByteArray();
        return array;
    }else{
        return QByteArray();
    }
}

QList<int> ClvDataAccessor::getIdList(QString searchText, DeepCommandSearcher *searcher){
    QList<int> idList;

    QSqlQuery query;
    query.prepare(COMMAND_SELECT_ID_DATA);
    query = execSql(query);
    searcher->setProgressValue(1);
    int size = 0;
    while(query.next()){
        size++;
    }
    searcher->setProgressValue(10);

    int count = 0;
    query.prepare(COMMAND_SELECT_ID_DATA);
    query = execSql(query);
    while(query.next()){
        int id = query.value(0).toInt();
        QByteArray array = query.value(1).toByteArray();
        QString commandText = QString(qUncompress(array));
        if(commandText.contains(searchText)){
            idList.append(id);
        }

        if(count % 10 == 0){
            int value = 10 + 90 * (count/size);
            searcher->setProgressValue(value);
        }
    }

    return idList;
}

//COMMAND_SELECT_DATA
//COMMAND_SELECT_COMMAND_LAYER_GROUP_WHERE;

/////////////////
///  COMMAND GROUP
/////////////////

bool ClvDataAccessor::hasCommand(QString group){
    QList<int> list = getIdListFromGroup(group);
    return list.length() > 0;
}

QList<int> ClvDataAccessor::getIdListFromGroup(QString group){
    QList<int> idList;
    QString sql = QString(GROUP_SELECT_COMMAND_ID_BY_GROUP_NAME).arg(group);
    QSqlQuery query;
    query.prepare(sql);
    execSql(query);
    while(query.next()){
        idList.append(query.value(0).toInt());
    }
    return idList;
}



void ClvDataAccessor::writeGroupDefinition(QString groupName, QList<QString> regexList, QList<QString> highlightList){
    QSet<int> hitIdSet;
    QList<int> hitIdList;

    // make id list
    foreach(QString regex, regexList){
        QSqlQuery query;
        QString sql = QString(COMMAND_SELECT_ID_BY_REGEX).arg(regex);
        query.prepare(sql);
        query = execSql(query);
        while(query.next()){
            int id = query.value(0).toInt();
            if(!hitIdSet.contains(id)){
                hitIdSet.insert(id);
                hitIdList.append(id);
            }
        }
    }

    // register
    foreach(int id, hitIdList){
        QSqlQuery query;
        query.prepare(GROUP_INSERT_TO_TABLE);
        query.bindValue(BIND_NAME, groupName);
        query.bindValue(BIND_COMMAND_ID, id);
        execSql(query);
    }

    // highlight
    foreach(QString regex, highlightList){
        QSqlQuery query;
        query.prepare(HIGHLIGHT_INSERT_TO_TABLE);
        query.bindValue(BIND_GROUP_NAME, groupName);
        query.bindValue(BIND_REGEX, regex);
        query.bindValue(BIND_COLOR, "red");
        execSql(query);
    }
}

void ClvDataAccessor::writeSearchGroupDefinition(QString groupName, QList<int> idList){
    QSqlQuery query;
    QString sql = QString(GROUP_DELETE_GROUP_BY_NAME).arg(groupName);
    query.prepare(sql);
    query = execSql(query);
    int i=0;
    foreach(int id, idList){
        qDebug() << i++;
        query.prepare(GROUP_INSERT_TO_TABLE);
        query.bindValue(BIND_NAME, groupName);
        query.bindValue(BIND_COMMAND_ID, id);
        execSql(query);
    }
}


QList<CommandData> ClvDataAccessor::getCommandDataList(QString group){
    qDebug() << "ClvDataAccessor::getCommandDataList()";
    return getCommandDataList(getIdListFromGroup(group));
}

QList<CommandData> ClvDataAccessor::getCommandDataList(QList<int> idList){
    QList<CommandData> commandList;
    if(idList.length() == 0){
        return commandList;
    }

    QString idRange = "(";
    for(int i=0; i<idList.length(); i++){
        if(i==0){
            idRange.append(QString::number(idList.at(i)));
        }else{
            idRange.append(", ");
            idRange.append(QString::number(idList.at(i)));
        }
    }
    idRange.append(")");

    QString sql = QString(COMMAND_SELECT_COMMAND_DECORATED_DATA_BY_ID).arg(idRange);
    QSqlQuery query;
    query.prepare(sql);
    query = execSql(query);
    while(query.next()){
        commandList.append(CommandData(query.value(0).toString(),
                                       query.value(1).toString(),
                                       query.value(2).toByteArray()));
    }

    return commandList;
}

QList<QString> ClvDataAccessor::getHighlightTextList(QString group){
    QList<QString> highlightTextList;

    QString sql = QString(HIGHLIGHT_SELECT_REGEX_BY_GROUP).arg(group);
    QSqlQuery query;
    query.prepare(sql);
    query = execSql(query);
    while(query.next()){
        highlightTextList.append(query.value(2).toString());
    }

    return highlightTextList;

}

/////////////////
///  LAYER
/////////////////

void ClvDataAccessor::writeLayerDefinition(QString layerName, QList<QString> groupList){
    // register
    foreach(QString group, groupList){
        QSqlQuery query;
        query.prepare(LAYER_INSERT_TO_TABLE);
        query.bindValue(BIND_NAME, layerName);
        query.bindValue(BIND_GROUP_NAME, group);
        execSql(query);
    }
}

QList<QString> ClvDataAccessor::getLayerList(){
    QList<QString> layerList;

    QSqlQuery query;
    query.prepare(LAYER_SELECT_DISTINCT_NAME);
    query = execSql(query);
    while(query.next()){
        layerList.append(query.value(0).toString());
    }

    return layerList;
}

QMap<QString, QList<QString> > ClvDataAccessor::getLayerMap(){
    QMap<QString, QList<QString> > layerMap;

    QSqlQuery query;
    query.prepare(LAYER_SELECT_DISTINCT_GROUP_NAME);
    query = execSql(query);
    while(query.next()){
        QString layer = query.value(0).toString();
        QString group = query.value(1).toString();
        if(!layerMap.contains(layer)){
            QList<QString> list;
            layerMap.insert(layer, list);
        }
        QList<QString> list = layerMap.value(layer);
        list.append(group);
        layerMap.insert(layer, list);
    }

    return layerMap;
}


/////////////////
///  MEMO
/////////////////

void ClvDataAccessor::writeMemo(QString content){
    QSqlQuery query;
    query.prepare(MEMO_INSERT_TO_TABLE);
    query.bindValue(BIND_CONTENT, content);
    query.bindValue(BIND_UPDATE_DATE, getCurrentDateString());
    query = execSql(query);
}

QString ClvDataAccessor::readMemo(){
    QSqlQuery query;
    query.prepare(MEMO_SELECT_LATEST);
    query = execSql(query);
    if(query.next()){
        QString content = query.value(1).toString();
        return content;
    }else{
        return "";
    }
}

/////////////////
///  VAL
/////////////////

// table project
const QString ClvDataAccessor::PROJECT_TABLE = "project";
const QString ClvDataAccessor::PROJECT_CHECK_TABLE = "SELECT sql FROM sqlite_master WHERE type='table' AND name='project'";
const QString ClvDataAccessor::PROJECT_DROP_TABLE = "DROP TABLE project";
const QString ClvDataAccessor::PROJECT_CREATE_TABLE = "CREATE TABLE project (major_version INT, minor_version INT, product TEXT, create_date TEXT, update_date TEXT)";
const QString ClvDataAccessor::PROJECT_INSERT_TO_TABLE = "INSERT INTO project values (:major_version, :minor_version, :product, :create_date, :update_date )";

// table command
const QString ClvDataAccessor::COMMAND_TABLE = "command";
const QString ClvDataAccessor::COMMAND_CHECK_TABLE = "SELECT sql FROM sqlite_master WHERE type='table' AND name='command'";
const QString ClvDataAccessor::COMMAND_CREATE_TABLE = "CREATE TABLE command (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, decorated_name TEXT, layer_name TEXT, group_name TEXT, scope TEXT, tag TEXT, file TEXT, data BLOB)";
const QString ClvDataAccessor::COMMAND_DROP_TABLE = "DROP TABLE command";
const QString ClvDataAccessor::COMMAND_INSERT_TO_TABLE = "INSERT INTO command (name, decorated_name, scope, tag, file, data) values (:name, :decorated_name, :scope, :tag, :file, :data )";
const QString ClvDataAccessor::COMMAND_UPDATE_GROUP_RAYER = "UPDATE command SET layer_name = \"%1\", group_name = \"%2\" WHERE id = %3";
const QString ClvDataAccessor::COMMAND_SELECT_ID_BY_REGEX = "SELECT id FROM command WHERE name LIKE \"%1\"";
const QString ClvDataAccessor::COMMAND_SELECT_COMMAND_LAYER_GROUP = "SELECT name, layer_name, group_name FROM command";
const QString ClvDataAccessor::COMMAND_SELECT_COMMAND_LAYER_GROUP_WHERE = "SELECT name, layer_name, group_name FROM command WHERE name LIKE '%1' LIMIT %2";
const QString ClvDataAccessor::COMMAND_SELECT_COMMAND_LAYER_GROUP_NONE = "SELECT name, layer_name, group_name FROM command WHERE layer_name IS NULL";
const QString ClvDataAccessor::COMMAND_SELECT_COMMAND_DECORATED_DATA_BY_ID = "SELECT name, decorated_name, data FROM command WHERE id IN %1";
const QString ClvDataAccessor::COMMAND_SELECT_DATA = "SELECT data FROM command WHERE name = \"%1\"";
const QString ClvDataAccessor::COMMAND_SELECT_ID_DATA = "SELECT id, data FROM command";

// table command_group
const QString ClvDataAccessor::GROUP_TABLE = "command_group";
const QString ClvDataAccessor::GROUP_DROP_TABLE = "DROP TABLE command_group";
const QString ClvDataAccessor::GROUP_CHECK_TABLE = "SELECT sql FROM sqlite_master WHERE type='table' AND name='command_group'";
const QString ClvDataAccessor::GROUP_CREATE_TABLE = "CREATE TABLE command_group (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, command_id INT)";
const QString ClvDataAccessor::GROUP_INSERT_TO_TABLE = "INSERT INTO command_group (name, command_id) values (:name, :command_id )";
const QString ClvDataAccessor::GROUP_SELECT_COMMAND_ID_BY_GROUP_NAME = "SELECT command_id FROM command_group WHERE name = \"%1\" ORDER BY command_id";
const QString ClvDataAccessor::GROUP_DELETE_GROUP_BY_NAME = "DELETE FROM command_group WHERE name = \"%1\"";

// table highlight
const QString ClvDataAccessor::HIGHLIGHT_TABLE = "highlight";
const QString ClvDataAccessor::HIGHLIGHT_CHECK_TABLE = "SELECT sql FROM sqlite_master WHERE type='table' AND name='highlight'";
const QString ClvDataAccessor::HIGHLIGHT_DROP_TABLE = "DROP TABLE highlight";
const QString ClvDataAccessor::HIGHLIGHT_CREATE_TABLE = "CREATE TABLE highlight (id INTEGER PRIMARY KEY AUTOINCREMENT, group_name TEXT, regex TEXT, color TEXT)";
const QString ClvDataAccessor::HIGHLIGHT_INSERT_TO_TABLE  = "INSERT INTO highlight (group_name, regex, color) values (:group_name, :regex, :color)";
const QString ClvDataAccessor::HIGHLIGHT_SELECT_REGEX_BY_GROUP = "SELECT * FROM highlight WHERE GROUP_NAME = \"%1\"";

// table command layer
const QString ClvDataAccessor::LAYER_TABLE = "layer";
const QString ClvDataAccessor::LAYER_DROP_TABLE = "DROP TABLE layer";
const QString ClvDataAccessor::LAYER_CHECK_TABLE = "SELECT sql FROM sqlite_master WHERE type='table' AND name='layer'";
const QString ClvDataAccessor::LAYER_CREATE_TABLE = "CREATE TABLE layer (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, group_name TEXT)";
const QString ClvDataAccessor::LAYER_INSERT_TO_TABLE = "INSERT INTO layer (name, group_name) values (:name, :group_name )";
const QString ClvDataAccessor::LAYER_SELECT_DISTINCT_NAME = "SELECT DISTINCT name FROM layer";
const QString ClvDataAccessor::LAYER_SELECT_DISTINCT_GROUP_NAME = "SELECT DISTINCT name, group_name FROM layer";

// table search
const QString ClvDataAccessor::SEARCH1_TABLE = "search1";
const QString ClvDataAccessor::SEARCH1_CHECK_TABLE = "SELECT sql FROM sqlite_master WHERE type='table' AND name='search1'";
const QString ClvDataAccessor::SEARCH1_DROP_TABLE = "DROP TABLE search1";
const QString ClvDataAccessor::SEARCH1_CREATE_TABLE = "CREATE TABLE search1 (id INTEGER PRIMARY KEY AUTOINCREMENT, keyword TEXT, open INTEGER)";
const QString ClvDataAccessor::SEARCH1_INSERT_TO_TABLE = "";

const QString ClvDataAccessor::SEARCH2_TABLE = "search2";
const QString ClvDataAccessor::SEARCH2_CHECK_TABLE = "SELECT sql FROM sqlite_master WHERE type='table' AND name='search2'";
const QString ClvDataAccessor::SEARCH2_DROP_TABLE = "DROP TABLE search2";
const QString ClvDataAccessor::SEARCH2_CREATE_TABLE = "CREATE TABLE search2 (search_id INTEGER , command_id INTEGER)";
const QString ClvDataAccessor::SEARCH2_INSERT_TO_TABLE = "";

// table bookmark
const QString ClvDataAccessor::BOOKMARK_TABLE = "bookmark";
const QString ClvDataAccessor::BOOKMARK_CHECK_TABLE = "SELECT sql FROM sqlite_master WHERE type='table' AND name='bookmark'";
const QString ClvDataAccessor::BOOKMARK_DROP_TABLE = "DROP TABLE bookmark";
const QString ClvDataAccessor::BOOKMARK_CREATE_TABLE = "CREATE TABLE bookmark (id INTEGER PRIMARY KEY AUTOINCREMENT, command_id INTEGER, line_number INTEGER)";
const QString ClvDataAccessor::BOOKMARK_INSERT_TO_TABLE = "";

// table memo
const QString ClvDataAccessor::MEMO_TABLE = "memo";
const QString ClvDataAccessor::MEMO_CHECK_TABLE = "SELECT sql FROM sqlite_master WHERE type='table' AND name='memo'";
const QString ClvDataAccessor::MEMO_DROP_TABLE = "DROP TABLE memo";
const QString ClvDataAccessor::MEMO_CREATE_TABLE = "CREATE TABLE memo (id INTEGER PRIMARY KEY AUTOINCREMENT, content TEXT, update_date TEXT)";
const QString ClvDataAccessor::MEMO_INSERT_TO_TABLE = "INSERT INTO memo (content, update_date) values (:content, :update_date)";
const QString ClvDataAccessor::MEMO_SELECT_LATEST = "SELECT * FROM memo ORDER BY update_date DESC LIMIT 1";

// sql bind tag
const QString ClvDataAccessor::BIND_MAJOR_VERSION = ":major_version";
const QString ClvDataAccessor::BIND_MINOR_VERSION = ":minor_version";
const QString ClvDataAccessor::BIND_PRODUCT = ":product";
const QString ClvDataAccessor::BIND_CREATE_DATE = ":create_date";
const QString ClvDataAccessor::BIND_UPDATE_DATE = ":update_date";
const QString ClvDataAccessor::BIND_NAME = ":name";
const QString ClvDataAccessor::BIND_DECORATED_NAME = ":decorated_name";
const QString ClvDataAccessor::BIND_SCOPE = ":scope";
const QString ClvDataAccessor::BIND_TAG = ":tag";
const QString ClvDataAccessor::BIND_FILE = ":file";
const QString ClvDataAccessor::BIND_DATA = ":data";
const QString ClvDataAccessor::BIND_COMMAND_ID = ":command_id";
const QString ClvDataAccessor::BIND_GROUP_NAME = ":group_name";
const QString ClvDataAccessor::BIND_REGEX = ":regex";
const QString ClvDataAccessor::BIND_COLOR = ":color";
const QString ClvDataAccessor::BIND_CONTENT = ":content";
