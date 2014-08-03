#include "core_appinfo.h"

// ICON
const QString AppInfo::APP_ICON = ":/icon/appicon.png";
const QString AppInfo::ABOUT_ICON_TAC = ":/icon/tac_icon.png";
const QString AppInfo::ABOUT_ICON_QT = ":/icon/qt_icon.png";
const QString AppInfo::ABOUT_ICON_SQLITE = ":/icon/sqlite_icon.png";
const QString AppInfo::SEARCH_ICON_WINDOW = ":/icon/website_32.png";
const QString AppInfo::SEARCH_ICON_LEFT = ":/icon/arrow_sans_left_32.png";
const QString AppInfo::SEARCH_ICON_RIGHT = ":/icon/arrow_sans_right_32.png";
const QString AppInfo::DZ_ICON = ":/icon/dropimage.png";
const QString AppInfo::SEARCH_ICON = ":/icon/search_32.png";

// App Info
const QString AppInfo::APP_NAME = "Cisco Log Viewer";
const QString AppInfo::APP_STYLE_FUSION = "fusion";
const QString AppInfo::APP_DESCRIPTION = "CLV(Cisco Log Viewer) shows logs which are stored in CLV file. Another application CLP(Cisco Log Parser) create CLV file.\nCLV and CLP will help your troubleshooting task.";
const QString AppInfo::LICENSE = "LGPL (Inherits Qt5)";
const int AppInfo::MAJOR_VERSION = 1;
const int AppInfo::MINOR_VERSION = 1;

// Preference
const QString AppInfo::PREF_DBFILE_PATH = "./settings.db";
const QString AppInfo::SERVER_DEFAULT_DOMAIN = "clv.cisco.com";
const int AppInfo::SERVER_DEFAULT_PORT = 80;

// Author
const QString AppInfo::AUTHOR = "Yuichi Ito";
const QString AppInfo::MY_TITLE = "Cisco Systems. Japan TAC DataCenter Team";
const QString AppInfo::MAIL_ADDRESS = "yuiito@cisco.com";
const QString AppInfo::WEB_PAGE_URL = "http://clv.yuichi.com/";
const QString AppInfo::AUTHOR_PAGE_URL = "http://www.yuichi.com/";
const QString AppInfo::CONTACT_URL = "mailto:%1";
const QString AppInfo::REPORT_BUG_URL = "mailto:%1?Subject=[BUG CLV v%2.%3] TITLE_HERE";
const QString AppInfo::GIT_PAGE_URL = "http://xxxx";


////////////////
//// SIZE
////////////////

// Main Window
const int AppInfo::WINDOW_WIDTH = 500;
const int AppInfo::WINDOW_HEIGHT = 560;
const int AppInfo::WINDOW_MARGIN = 5;
const int AppInfo::WINDOW_SPACING = 5;
const int AppInfo::WINDOW_WS_HEIGHT = 30;
const int AppInfo::WINDOW_SEARCH_BOX_WIDTH = 200;
const int AppInfo::WINDOW_DZ_WIDTH = 200;
const int AppInfo::WINDOW_DZ_HEIGHT = 200;

// preference window
#ifdef Q_OS_WIN
const int AppInfo::PREF_WINDOW_WIDTH = 600;
const int AppInfo::PREF_WINDOW_HEIGHT = 400;
#else
const int AppInfo::PREF_WINDOW_WIDTH = 600;
const int AppInfo::PREF_WINDOW_HEIGHT = 400;
#endif


// ABOUT
#ifdef Q_OS_WIN
const int AppInfo::ABOUT_WINDOW_WIDTH = 250;
const int AppInfo::ABOUT_WINDOW_HEIGHT = 250;
#else
const int AppInfo::ABOUT_WINDOW_WIDTH = 250;
const int AppInfo::ABOUT_WINDOW_HEIGHT = 250;
#endif
const int AppInfo::ABOUT_WINDOW_ICON_WIDTH = 60;
const int AppInfo::ABOUT_WINDOW_ICON_HEIGHT = 80;


///////////
///  DUBUG
///////////

const bool AppInfo::DEBUG_MESSAGE_BROKER = false;
const bool AppInfo::DEBUG_CLV_DATA_ACCESSOR = false;
const bool AppInfo::DEBUG_MAIN_WINDOW = false;
const bool AppInfo::DEBUG_MENUBAR = false;
const bool AppInfo::DEBUG_PROGRESS_DIALOG = false;
const bool AppInfo::DEBUG_LOG_EDIT = false;
const bool AppInfo::DEBUG_LOG_VIEW = false;
const bool AppInfo::DEBUG_LOG_LOADER = false;
const bool AppInfo::DEBUG_SYNTAX_HIGHLIGHTER = false;

AppInfo::AppInfo()
{
}
