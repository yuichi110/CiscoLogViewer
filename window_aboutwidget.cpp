
#include "window_aboutwidget.h"

AboutWidget::AboutWidget() :
    QWidget(NULL)
{
    // style
    setWindowIcon(QIcon(AppInfo::APP_ICON));
    setWindowTitle("About " + AppInfo::APP_NAME);
    setFixedSize(AppInfo::ABOUT_WINDOW_WIDTH, AppInfo::ABOUT_WINDOW_HEIGHT);

    // create widget
    QVBoxLayout *vbox = new QVBoxLayout(this);
    vbox->setAlignment(Qt::AlignTop);
    vbox->addWidget(new QLabel("<h3>" + AppInfo::APP_NAME + "</h3>"));

    QString version = QString("%1.%2").arg(QString::number(AppInfo::MAJOR_VERSION), QString::number(AppInfo::MINOR_VERSION));
    vbox->addWidget(new QLabel("Version:\t" + version));
    vbox->addWidget(new QLabel("Auther:\t" + AppInfo::AUTHOR));
    vbox->addWidget(new QLabel("License :\t" + AppInfo::LICENSE));
    vbox->addWidget(new QLabel(""));

    QHBoxLayout *iconLayout = new QHBoxLayout();
    iconLayout->setAlignment(Qt::AlignCenter);

    // tac icon
    QLabel *tacLabel = new QLabel(this);
    QPixmap picTac(AppInfo::ABOUT_ICON_TAC);
    QPixmap scaledTac=picTac.scaled (AppInfo::ABOUT_WINDOW_ICON_WIDTH, AppInfo::ABOUT_WINDOW_ICON_HEIGHT,
                               Qt::IgnoreAspectRatio, Qt::FastTransformation );
    tacLabel->setPixmap(scaledTac);
    iconLayout->addWidget(tacLabel);
    vbox->addLayout(iconLayout);

    // qt icon
    QLabel *qtLabel = new QLabel(this);
    QPixmap picQt(AppInfo::ABOUT_ICON_QT);
    QPixmap scaledQt=picQt.scaled (AppInfo::ABOUT_WINDOW_ICON_WIDTH, AppInfo::ABOUT_WINDOW_ICON_HEIGHT,
                               Qt::IgnoreAspectRatio, Qt::FastTransformation );
    qtLabel->setPixmap(scaledQt);
    iconLayout->addWidget(qtLabel);

    // sqlite icon
    QLabel *sqliteLabel = new QLabel(this);
    QPixmap picSqlite(AppInfo::ABOUT_ICON_SQLITE);
    QPixmap scaledSqlite=picSqlite.scaled (AppInfo::ABOUT_WINDOW_ICON_WIDTH, AppInfo::ABOUT_WINDOW_ICON_HEIGHT,
                               Qt::IgnoreAspectRatio, Qt::FastTransformation );
    sqliteLabel->setPixmap(scaledSqlite);
    iconLayout->addWidget(sqliteLabel);
    vbox->addLayout(iconLayout);

    setLayout(vbox);
}

AboutWidget* AboutWidget::getInstance(){
    static AboutWidget about;
    return &about;
}

