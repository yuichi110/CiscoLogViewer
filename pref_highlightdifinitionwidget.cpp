#include "pref_highlightdifinitionwidget.h"

const bool HighlightDifinitionWidget::DEBUG = false;

HighlightDifinitionWidget::HighlightDifinitionWidget(QWidget *parent) :
    QWidget(parent)
{
    enableApplyFunc_m = false;

    // Style
    QHBoxLayout *hb = new QHBoxLayout();
    hb->setContentsMargins(5, 5, 5, 5);
    setLayout(hb);

    // Line Edit
    lineEdit_m = new QLineEdit(this);
    connect(lineEdit_m, SIGNAL(textChanged(QString)), this, SLOT(applyHighLight()));
    connect(lineEdit_m, SIGNAL(textChanged(QString)), this, SLOT(saveWidgetSettings()));

    // Case
    QLabel *caseLabel = new QLabel("  case:", this);
    caseSensitiveCheckBox_m = new QCheckBox(this);
    connect(caseSensitiveCheckBox_m, SIGNAL(clicked()), this, SLOT(applyHighLight()));
    connect(caseSensitiveCheckBox_m, SIGNAL(clicked()), this, SLOT(saveWidgetSettings()));

    // Color
    colorComboBox_m = new QComboBox(this);
    colorComboBox_m->addItem("Red", QVariant(QColor(Qt::red)));
    colorComboBox_m->addItem("Dark Red", QVariant(QColor(Qt::darkRed)));
    colorComboBox_m->addItem("Blue", QVariant(QColor(Qt::blue)));
    colorComboBox_m->addItem("Dark Blue", QVariant(QColor(Qt::darkBlue)));
    colorComboBox_m->addItem("Green", QVariant(QColor(Qt::green)));
    colorComboBox_m->addItem("Dark Green", QVariant(QColor(Qt::darkGreen)));
    colorComboBox_m->addItem("Cyan", QVariant(QColor(Qt::cyan)));
    colorComboBox_m->addItem("Dark Cyan", QVariant(QColor(Qt::darkCyan)));
    colorComboBox_m->addItem("Magenta", QVariant(QColor(Qt::magenta)));
    colorComboBox_m->addItem("Dark Magenta", QVariant(QColor(Qt::darkMagenta)));
    colorComboBox_m->addItem("Yellow", QVariant(QColor(Qt::yellow)));
    colorComboBox_m->addItem("Dark Yellow", QVariant(QColor(Qt::darkYellow)));
    colorComboBox_m->addItem("Gray", QVariant(QColor(Qt::gray)));
    colorComboBox_m->addItem("Dark Gray", QVariant(QColor(Qt::darkGray)));
    colorComboBox_m->addItem("Light Gray", QVariant(QColor(Qt::lightGray)));
    colorComboBox_m->addItem("Black", QVariant(QColor(Qt::black)));
    colorComboBox_m->addItem("White", QVariant(QColor(Qt::white)));
    connect(colorComboBox_m, SIGNAL(currentIndexChanged(int)), this, SLOT(applyHighLight()));
    connect(colorComboBox_m, SIGNAL(currentIndexChanged(int)), this, SLOT(saveWidgetSettings()));

    // BOLD
    boldButton_m = new QPushButton(this);
    boldButton_m->setCheckable(true);
    boldButton_m->setText("B");
    boldButton_m->setMaximumWidth(25);
    QFont fontBold;
    fontBold.setBold(true);
    boldButton_m->setFont(fontBold);
    connect(boldButton_m, SIGNAL(clicked()), this, SLOT(applyHighLight()));
    connect(boldButton_m, SIGNAL(clicked()), this, SLOT(saveWidgetSettings()));

    // ITALIC
    italicButton_m = new QPushButton(this);
    italicButton_m->setCheckable(true);
    italicButton_m->setText("I");
    italicButton_m->setMaximumWidth(25);
    QFont fontItalic;
    fontItalic.setItalic(true);
    italicButton_m->setFont(fontItalic);
    connect(italicButton_m, SIGNAL(clicked()), this, SLOT(applyHighLight()));
    connect(italicButton_m, SIGNAL(clicked()), this, SLOT(saveWidgetSettings()));

    // Under Line
    underLineButton_m = new QPushButton(this);
    underLineButton_m->setCheckable(true);
    underLineButton_m->setText("U");
    underLineButton_m->setMaximumWidth(25);
    QFont fontUnderLine;
    fontUnderLine.setUnderline(true);
    underLineButton_m->setFont(fontUnderLine);
    connect(underLineButton_m, SIGNAL(clicked()), this, SLOT(applyHighLight()));
    connect(underLineButton_m, SIGNAL(clicked()), this, SLOT(saveWidgetSettings()));

    // Add
    QPushButton *addButton = new QPushButton(this);
    addButton->setText("+");
    addButton->setMaximumWidth(50);
    connect(addButton, SIGNAL(clicked()), this, SLOT(plusClicked()));

    // Delete
    QPushButton *deleteButton = new QPushButton(this);
    deleteButton->setText("-");
    deleteButton->setMaximumWidth(50);
    connect(deleteButton, SIGNAL(clicked()), this, SLOT(deleteClicked()));

    hb->addWidget(lineEdit_m);
    hb->addWidget(caseLabel);
    hb->addWidget(caseSensitiveCheckBox_m);
    hb->addWidget(colorComboBox_m);
    hb->addWidget(boldButton_m);
    hb->addWidget(italicButton_m);
    hb->addWidget(underLineButton_m);
    hb->addWidget(addButton);
    hb->addWidget(deleteButton);

    enableApplyFunc_m = true;
}

void HighlightDifinitionWidget::setValues(QString regexString, QTextCharFormat format, bool isCaseSensitive){
    enableApplyFunc_m = false;
    lineEdit_m->setText(regexString);
    caseSensitiveCheckBox_m->setChecked(isCaseSensitive);

    QColor color = format.foreground().color();
    colorComboBox_m->setCurrentIndex(0);
    for(int i=0; i<colorComboBox_m->count(); i++){
        QVariant v = colorComboBox_m->itemData(i);
        QColor c = v.value<QColor>();
        if(c == color){
            colorComboBox_m->setCurrentIndex(i);
        }
    }

    QFont font = format.font();
    boldButton_m->setChecked(font.bold());
    italicButton_m->setChecked(font.italic());
    underLineButton_m->setChecked(font.italic());

    enableApplyFunc_m = true;
}

void HighlightDifinitionWidget::applyHighLight(){
    if(!enableApplyFunc_m) return;

    if(DEBUG) qDebug() << "applyHighLight";
    QTextCharFormat format = getCharFormat();
    QPalette palette = lineEdit_m->palette();
    palette.setColor(QPalette::Text, format.foreground().color());
    lineEdit_m->setPalette(palette);
    lineEdit_m->setFont(format.font());
}

void HighlightDifinitionWidget::saveWidgetSettings(){
    if(!enableApplyFunc_m) return;
}

void HighlightDifinitionWidget::plusClicked(){
    emit insertHighlight(this);
}

void HighlightDifinitionWidget::deleteClicked(){
    emit removeHighlight(this);
}

QString HighlightDifinitionWidget::getRegexString(){
    return lineEdit_m->text();
}

QTextCharFormat HighlightDifinitionWidget::getCharFormat(){
    QTextCharFormat format;
    int index = colorComboBox_m->currentIndex();
    QVariant v = colorComboBox_m->itemData(index);
    QColor c = v.value<QColor>();
    format.setForeground(c);

    if(boldButton_m->isChecked()) format.setFontWeight(QFont::Bold);
    if(italicButton_m->isChecked()) format.setFontItalic(true);
    if(underLineButton_m->isChecked()) format.setFontUnderline(true);

    return format;
}

bool HighlightDifinitionWidget::getIsCaseSensitive(){
    return caseSensitiveCheckBox_m->isChecked();
}
