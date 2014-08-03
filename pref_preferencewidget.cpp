#include "pref_preferencewidget.h"

PreferenceWidget::PreferenceWidget() :
    QWidget(NULL)
{
    preferenceManager_m = PreferenceManager::getInstance();

    // set style
    setWindowIcon(QIcon(AppInfo::APP_ICON));
    setWindowTitle("Preference: " + AppInfo::APP_NAME);
    setFixedSize(AppInfo::PREF_WINDOW_WIDTH, AppInfo::PREF_WINDOW_HEIGHT);

    // create widget
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->setContentsMargins(0,0,0,0);

    QTabWidget *tabWidget = new QTabWidget(this);
    tabWidget->addTab(getStyleWidget(), "Font and Color");
    hdListWidget_m = new HdListWidget(this);
    QList<HighlightRule> ruleList;
    hdListWidget_m->initializeDifinitionWidgetes(ruleList);
    tabWidget->addTab(hdListWidget_m, "Generic Highlight Rule");
    mainLayout->addWidget(tabWidget);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QPushButton *initializeButton = new QPushButton("initialize", this);
    initializeButton->setFixedWidth(100);
    connect(initializeButton, SIGNAL(clicked()), this, SLOT(initializeClicked()));
    buttonLayout->addWidget(initializeButton);
    buttonLayout->addStretch();
    QPushButton *cancelButton = new QPushButton("cancel", this);
    cancelButton->setFixedWidth(100);
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancelClicked()));
    buttonLayout->addWidget(cancelButton);
    QPushButton *saveButton = new QPushButton("save", this);
    saveButton->setFixedWidth(100);
    connect(saveButton, SIGNAL(clicked()), this, SLOT(saveClicked()));
    buttonLayout->addWidget(saveButton);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);

    load();
}

PreferenceWidget* PreferenceWidget::getInstance(){
    static PreferenceWidget w;
    return &w;
}

QWidget *PreferenceWidget::getStyleWidget(){
    QWidget *editerStyleWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    mainLayout->addWidget(new QLabel("Didn't' implemented yet."));

    QHBoxLayout *fontLayout = new QHBoxLayout();
    fontLayout->addWidget(new QLabel("Font: "));
    fontComboBox_m = new QComboBox(this);
    addFontToComboBox(fontComboBox_m);
    fontLayout->addWidget(fontComboBox_m);
    mainLayout->addLayout(fontLayout);

    QHBoxLayout *fontSizeLayout = new QHBoxLayout();
    fontSizeLayout->addWidget(new QLabel("Font size: "));
    fontSizeComboBox_m = new QComboBox(this);
    addFontSizeToComboBox(fontSizeComboBox_m);
    fontSizeLayout->addWidget(fontSizeComboBox_m);
    mainLayout->addLayout(fontSizeLayout);

    QHBoxLayout *textColorLayout = new QHBoxLayout();
    textColorLayout->addWidget(new QLabel("Text Color: "));
    textColorComboBox_m = new QComboBox(this);
    addColorsToComboBox(textColorComboBox_m);
    textColorLayout->addWidget(textColorComboBox_m);
    mainLayout->addLayout(textColorLayout);

    QHBoxLayout *backgroundColorLayout = new QHBoxLayout();
    backgroundColorLayout->addWidget(new QLabel("Background Color: "));
    backgroundColorComboBox_m = new QComboBox(this);
    addColorsToComboBox(backgroundColorComboBox_m);
    backgroundColorLayout->addWidget(backgroundColorComboBox_m);
    mainLayout->addLayout(backgroundColorLayout);

    editerStyleWidget->setLayout(mainLayout);
    return editerStyleWidget;
}

void PreferenceWidget::addColorsToComboBox(QComboBox *comboBox){
    comboBox->addItem("Red", QVariant(QColor(Qt::red)));
    comboBox->addItem("Dark Red", QVariant(QColor(Qt::darkRed)));
    comboBox->addItem("Blue", QVariant(QColor(Qt::blue)));
    comboBox->addItem("Dark Blue", QVariant(QColor(Qt::darkBlue)));
    comboBox->addItem("Green", QVariant(QColor(Qt::green)));
    comboBox->addItem("Dark Green", QVariant(QColor(Qt::darkGreen)));
    comboBox->addItem("Cyan", QVariant(QColor(Qt::cyan)));
    comboBox->addItem("Dark Cyan", QVariant(QColor(Qt::darkCyan)));
    comboBox->addItem("Magenta", QVariant(QColor(Qt::magenta)));
    comboBox->addItem("Dark Magenta", QVariant(QColor(Qt::darkMagenta)));
    comboBox->addItem("Yellow", QVariant(QColor(Qt::yellow)));
    comboBox->addItem("Dark Yellow", QVariant(QColor(Qt::darkYellow)));
    comboBox->addItem("Gray", QVariant(QColor(Qt::gray)));
    comboBox->addItem("Dark Gray", QVariant(QColor(Qt::darkGray)));
    comboBox->addItem("Light Gray", QVariant(QColor(Qt::lightGray)));
    comboBox->addItem("Black", QVariant(QColor(Qt::black)));
    comboBox->addItem("White", QVariant(QColor(Qt::white)));
}

void PreferenceWidget::addFontSizeToComboBox(QComboBox *comboBox){
    comboBox->addItem("8", QVariant(8));
    comboBox->addItem("9", QVariant(9));
    comboBox->addItem("10", QVariant(10));
    comboBox->addItem("11", QVariant(11));
    comboBox->addItem("12", QVariant(12));
    comboBox->addItem("13", QVariant(13));
    comboBox->addItem("14", QVariant(14));
    comboBox->addItem("15", QVariant(15));
    comboBox->addItem("16", QVariant(16));
}

void PreferenceWidget::addFontToComboBox(QComboBox *comboBox){
    comboBox->addItem("Monospace", QVariant("Monospace"));
}

void PreferenceWidget::load(){
    QList<HighlightRule> ruleList = preferenceManager_m->getHighlightRuleList();
    hdListWidget_m->initializeDifinitionWidgetes(ruleList);
}

void PreferenceWidget::initializeClicked(){
    qDebug() << "initialize";

    /*
     *
     *  NEED IMPLEMENTATION HERE
     *
     */

    load();
}

void PreferenceWidget::cancelClicked(){
    qDebug() << "cancel";
    load();
}

void PreferenceWidget::saveClicked(){
    QList<HighlightRule> rules = hdListWidget_m->getHighLightRuleList();
    preferenceManager_m->setHighLightRuleList(rules);
    preferenceManager_m->save();
}
