#include "test_componenttester.h"

ComponentTester::ComponentTester()
{
}

int ComponentTester::testLogView(int argc, char *argv[]){
    QApplication app(argc, argv);

    LogView *lv = new LogView(NULL, "Hard", "Env", "/Users/yuichi/Desktop/clvtest.clv", "", true, true);
    lv->show();
    lv->loadLogs();

    return app.exec();
}

int ComponentTester::testLogEdit(int argc, char *argv[]){
    QApplication app(argc, argv);
    /*
    MessageBroker *messageBroker = new MessageBroker();
    LogEdit *le = new LogEdit(NULL, messageBroker, "Env");
    QString text = "hello\nqt5\nc++\njava\npython";
    le->setPlainText(text);
    le->show();
    */
    return app.exec();
}

/*
int ComponentTester::testLogView(int argc, char *argv[]){
    QApplication app(argc, argv);



    return app.exec();
}
*/

int ComponentTester::testCommandLoader(int argc, char *argv[]){
    QApplication app(argc, argv);
    QString group = "Env";
    QString path = "/Users/yuichi/Desktop/clp-testDatabase2.clv";
    CommandLoader *loader = new CommandLoader(group, path);
    loader->start();
    return app.exec();
}

int ComponentTester::testSubString(){
    QString test = "helloworld, qt5, c++, java, python";
    int splitSize = 5;
    for(int i=0; i*splitSize<test.length(); i++){
        QString str = test.mid(i*splitSize, splitSize);
        qDebug() << str;
    }

    return 1;
}

int ComponentTester::testLayerTab(int argc, char *argv[]){
    QApplication app(argc, argv);

    MessageBroker *messageBroker = new MessageBroker();
    LayerTabWidget *lt = new LayerTabWidget(NULL, messageBroker);
    for(int i=0; i<10; i++){
        LogView *lv = new LogView(NULL, "Hard", "Env", "/Users/yuichi/Desktop/clp-testDatabase2.clv", "", true, true);
        lv->loadLogs();
        lt->addLogWidget("test", "Env", lv);
    }

    for(int i=0; i<10; i++){
        LogView *lv = new LogView(NULL, "Hard", "Env", "/Users/yuichi/Desktop/clp-testDatabase2.clv", "", true, true);
        lv->loadLogs();
        lt->addLogWidget("test2", "Env", lv);
    }

    lt->show();
    return app.exec();
}

int ComponentTester::testGetLayer(){
    QString filePath = "/Users/yuichi/Desktop/clp-testDatabase2.clv";
    ClvDataAccessor *accessor = new ClvDataAccessor(filePath);
    accessor->open();
    bool syntaxOK = accessor->checkTableSyntax();
    qDebug() << "syntaxOK: " << syntaxOK;
    if(!syntaxOK){
        return 1;
    }

    QList<QString> layerList = accessor->getLayerList();
    QMap<QString, QList<QString> > layerMap = accessor->getLayerMap();
    foreach(QString layer, layerList){
        QList<QString> list = layerMap.value(layer);
        qDebug() << layer << " : " << list;
    }

    return 1;
}

int ComponentTester::testLayerTab2(int argc, char *argv[]){
    QApplication app(argc, argv);

    MessageBroker *messageBroker = new MessageBroker();
    new WsTabManager(NULL, messageBroker);
    new TabManager(NULL, messageBroker);

    LayerTabWidget *tab = new LayerTabWidget(NULL, messageBroker);
    ClvLoader *loader = new ClvLoader(messageBroker);
    loader->loadClvFile("/Users/yuichi/Desktop/clvtest.clv");
    tab->show();

    return app.exec();
}

int ComponentTester::testShortcutWidget(int argc, char *argv[]){
    QApplication app(argc, argv);

    MessageBroker *messageBroker = new MessageBroker();
    ShortcutWidget* w = new ShortcutWidget(NULL, messageBroker);
    w->setFixedHeight(40);
    w->setMinimumWidth(300);
    w->show();

    w->addShortcutButton("hello", "world");
    w->addShortcutButton("hello", "python");
    w->addShortcutButton("hello", "world");
    w->addShortcutButton("hello", "java");
    w->addShortcutButton("hello", "qt");

    return app.exec();
}

int ComponentTester::testSearchCommandWidget(int argc, char *argv[]){
    QApplication app(argc, argv);
    MessageBroker *mb = new MessageBroker();
    SearchCommandWidget *w = new SearchCommandWidget(NULL, mb);
    w->setFixedSize(200, 50);
    w->show();
    return app.exec();
}

int ComponentTester::testOneCommandWidget(int argc, char *argv[]){
    QApplication app(argc, argv);
    OneCommandWidget *w = new OneCommandWidget(NULL, "hello", "hello\nworld");
    w->show();
    return app.exec();
}

int ComponentTester::testCommandListWidget(int argc, char *argv[]){
    QApplication app(argc, argv);

    QList<CommandGroupInfo> list;
    list.append(CommandGroupInfo("Hello world", "test1", "test11"));
    list.append(CommandGroupInfo("Hello world", "test2", "test33"));
    list.append(CommandGroupInfo("Hello world", "test3", "test44"));
    list.append(CommandGroupInfo("Hello world", "test4", "test55"));
    //w->loadCommandList(list);
    CommandListWidget *w = new CommandListWidget(NULL, list, "/Users/yuichi/Desktop/clvtest.clv", true);
    w->show();
    return app.exec();
}

int ComponentTester::testDropZone(int argc, char *argv[]){
    QApplication app(argc, argv);
    MessageBroker *messageBroker = new MessageBroker();
    new ClvLoader(messageBroker);
    DropZone *dz = new DropZone(NULL, messageBroker);
    dz->show();

    return app.exec();
}

int ComponentTester::testHighlightDefinitionWidget(int argc, char *argv[]){
    QApplication app(argc, argv);
    HighlightDifinitionWidget *hdw = new HighlightDifinitionWidget(NULL);
    hdw->show();
    return app.exec();
}

int ComponentTester::testHdListWidget(int argc, char *argv[]){
    QApplication app(argc, argv);
    HdListWidget *hlw = new HdListWidget(NULL);
    QList<HighlightRule> ruleList;
    hlw->initializeDifinitionWidgetes(ruleList);
    hlw->show();

    return app.exec();
}

int ComponentTester::testPreferenceWidget(int argc, char *argv[]){
    QApplication app(argc, argv);
    PreferenceWidget *pw = PreferenceWidget::getInstance();
    pw->show();
    return app.exec();
}

int ComponentTester::testPreferenceAccessor(int argc, char *argv[]){
    QApplication app(argc, argv);
    PreferenceDataAccessor *accessor = new PreferenceDataAccessor("/Users/yuichi/Desktop/preftest.db");
    accessor->updateEditorSettings("font2", 11, "red", "blue");
    qDebug() << accessor->getEditorFont();
    qDebug() << accessor->getEditorFontSize();
    qDebug() << accessor->getEditorTextColor();
    qDebug() << accessor->getEditorBackgroundColor();

    QTextCharFormat format;
    QColor color("red");
    format.setForeground(color);
    format.setFontWeight(QFont::Bold);
    format.setFontItalic(true);
    format.setFontUnderline(false);
    HighlightRule rule("test regex string", format, true);

    QTextCharFormat format2;
    QColor color2("blue");
    format2.setForeground(color2);
    format2.setFontItalic(false);
    format2.setFontUnderline(true);
    HighlightRule rule2("test regex string2", format2, false);

    QList<HighlightRule> ruleList;
    ruleList.append(rule);
    ruleList.append(rule2);
    accessor->updateHighlightRuleSettings(ruleList);

    QList<HighlightRule> ruleList2 = accessor->getHighlightRuleList();
    qDebug() << ruleList2.length();

    return app.exec();
}

int ComponentTester::testDeepSearchWidget(int argc, char *argv[]){
    QApplication app(argc, argv);
    /*
    ClvDataAccessor *accessor = new ClvDataAccessor("/Users/yuichi/Desktop/clvtest.clv");
    accessor->open();
    QList<int> list = accessor->getIdList("Interface");
    accessor->close();
    qDebug() << list;
    */
    (new DeepSearchWidget(NULL, "/Users/yuichi/Desktop/clvtest.clv"))->show();
    return app.exec();
}
