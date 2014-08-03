#include <QtWidgets>
#include <QStyle>
#include <QStyleFactory>
#include "core_appinfo.h"
#include "mwc_mainwindow.h"

int main(int argc, char *argv[])
{
    #ifndef Q_OS_WIN
    // mac and other os style
    QApplication::setStyle(QStyleFactory::create(AppInfo::APP_STYLE_FUSION));
    #else
    // windows style
    // none. use default.
    #endif

    QApplication app(argc, argv);
    (new MainWindow())->show();
    return app.exec();
}
