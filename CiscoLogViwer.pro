#-------------------------------------------------
#
# Project created by QtCreator 2012-02-25T23:39:38
#
#-------------------------------------------------

QT       += core gui widgets sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CiscoLogViewer
TEMPLATE = app

# Windows
RC_ICONS = appicon.ico

# Mac
ICON = appicon.icns

SOURCES +=\
    core_appinfo.cpp \
    core_main.cpp \
    core_messagebroker.cpp \
    mwc_mainwindow.cpp \
    core_preferencemanager.cpp \
    core_tabmanager.cpp \
    lv_logwindow.cpp \
    lv_commandloader.cpp \
    mwc_layertab.cpp \
    test_componenttester.cpp \
    lv_syntaxhighlighter.cpp \
    lv_logedit.cpp \
    lv_highlightrule.cpp \
    dao_clvdataaccessor.cpp \
    dao_preferencedataaccessor.cpp \
    dao_commanddata.cpp \
    lv_logtreeview.cpp \
    lv_logsearchwidget.cpp \
    lv_logview.cpp \
    core_clvloader.cpp \
    core_wstabmanager.cpp \
    ws_shortcutbutton.cpp \
    ws_searchcommandwidget.cpp \
    ws_shortcutwidget.cpp \
    ws_commandlistwidget.cpp \
    dao_commandgroupinfo.cpp \
    ws_onecommandwidget.cpp \
    ws_onecommandedit.cpp \
    mwc_menubar.cpp \
    mwc_dropzone.cpp \
    pref_hdlistwidget.cpp \
    pref_preferencewidget.cpp \
    pref_highlightdifinitionwidget.cpp \
    ws_deepsearchwidget.cpp \
    ws_deepcommandsearcher.cpp \
    ws_progressdialog.cpp \
    lv_logmodel.cpp \
    window_aboutwidget.cpp

HEADERS  += \
    window_aboutwidget.h \
    core_appinfo.h \
    lv_logwindow.h \
    lv_commandloader.h \
    mwc_mainwindow.h \
    lv_syntaxhighlighter.h \
    core_preferencemanager.h \
    core_tabmanager.h \
    core_messagebroker.h \
    lv_logview.h \
    lv_logedit.h \
    mwc_layertab.h \
    test_componenttester.h \
    lv_highlightrule.h \
    dao_clvdataaccessor.h \
    dao_preferencedataaccessor.h \
    dao_commanddata.h \
    lv_logtreeview.h \
    lv_logsearchwidget.h \
    core_clvloader.h \
    core_wstabmanager.h \
    ws_shortcutbutton.h \
    ws_searchcommandwidget.h \
    ws_shortcutwidget.h \
    ws_commandlistwidget.h \
    dao_commandgroupinfo.h \
    ws_onecommandwidget.h \
    ws_onecommandedit.h \
    mwc_menubar.h \
    mwc_dropzone.h \
    pref_hdlistwidget.h \
    pref_preferencewidget.h \
    pref_highlightdifinitionwidget.h \
    ws_deepsearchwidget.h \
    ws_deepcommandsearcher.h \
    ws_progressdialog.h \
    lv_logmodel.h

RESOURCES += \
    resource.qrc

OTHER_FILES += \
    appicon.ico
