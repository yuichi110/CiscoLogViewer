#ifndef HIGHLIGHTDIFINITIONWIDGET_H
#define HIGHLIGHTDIFINITIONWIDGET_H

#include <QWidget>
#include <QtGui>
#include <QtWidgets>

class HDManager;
class HighlightDifinitionWidget : public QWidget
{
    Q_OBJECT
private:
    static const bool DEBUG;
    QLineEdit *lineEdit_m;
    QCheckBox *caseSensitiveCheckBox_m;
    QComboBox *colorComboBox_m;
    QPushButton *boldButton_m;
    QPushButton *italicButton_m;
    QPushButton *underLineButton_m;
    bool enableApplyFunc_m;

public:
    explicit HighlightDifinitionWidget(QWidget *parent);
    QString getRegexString();
    QTextCharFormat getCharFormat();
    bool getIsCaseSensitive();
    void setValues(QString regexString, QTextCharFormat format, bool isCaseSensitive);

protected:

signals:
    void insertHighlight(HighlightDifinitionWidget *self);
    void removeHighlight(HighlightDifinitionWidget *self);

public slots:
    void applyHighLight();
    void plusClicked();
    void deleteClicked();
    void saveWidgetSettings();

};

#endif // HIGHLIGHTDIFINITIONWIDGET_H
