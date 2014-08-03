#ifndef APPINFO_H
#define APPINFO_H

#include <QObject>
#include <QtGui>

class AppInfo
{

public:
    // icon
    static const QString APP_ICON;
    static const QString ABOUT_ICON_TAC;
    static const QString ABOUT_ICON_QT;
    static const QString ABOUT_ICON_SQLITE;
    static const QString SEARCH_ICON_WINDOW;
    static const QString SEARCH_ICON_LEFT;
    static const QString SEARCH_ICON_RIGHT;
    static const QString DZ_ICON;
    static const QString SEARCH_ICON;

    // app
    static const QString APP_NAME;
    static const QString APP_STYLE_FUSION;
    static const QString APP_DESCRIPTION;
    static const QString LICENSE;
    static const int MAJOR_VERSION;
    static const int MINOR_VERSION;

    //preference
    static const QString PREF_DBFILE_PATH;
    static const QString SERVER_DEFAULT_DOMAIN;
    static const int SERVER_DEFAULT_PORT;

    // authour
    static const QString AUTHOR;
    static const QString MY_TITLE;
    static const QString MAIL_ADDRESS;
    static const QString WEB_PAGE_URL;
    static const QString AUTHOR_PAGE_URL;
    static const QString CONTACT_URL;
    static const QString REPORT_BUG_URL;
    static const QString GIT_PAGE_URL;

    // main window size
    static const int WINDOW_WIDTH;
    static const int WINDOW_HEIGHT;
    static const int WINDOW_MARGIN;
    static const int WINDOW_SPACING;
    static const int WINDOW_WS_HEIGHT;
    static const int WINDOW_SEARCH_BOX_WIDTH;
    static const int WINDOW_DZ_WIDTH;
    static const int WINDOW_DZ_HEIGHT;

    // preference window size
    static const int PREF_WINDOW_WIDTH;
    static const int PREF_WINDOW_HEIGHT;

    // about window size
    static const int ABOUT_WINDOW_WIDTH;
    static const int ABOUT_WINDOW_HEIGHT;
    static const int ABOUT_WINDOW_ICON_WIDTH;
    static const int ABOUT_WINDOW_ICON_HEIGHT;

    // debug
    static const bool DEBUG_MESSAGE_BROKER;
    static const bool DEBUG_CLV_DATA_ACCESSOR;
    static const bool DEBUG_MAIN_WINDOW;
    static const bool DEBUG_MENUBAR;
    static const bool DEBUG_PROGRESS_DIALOG;
    static const bool DEBUG_LOG_EDIT;
    static const bool DEBUG_LOG_VIEW;
    static const bool DEBUG_LOG_LOADER;
    static const bool DEBUG_SYNTAX_HIGHLIGHTER;

private:
    explicit AppInfo();
    
};

#endif // APPINFO_H
