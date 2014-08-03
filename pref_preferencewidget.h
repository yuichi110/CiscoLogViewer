#ifndef WINDOW_PREFERENCEWIDGET_H
#define WINDOW_PREFERENCEWIDGET_H

#include <QtWidgets>
#include "core_preferencemanager.h"
#include "pref_hdlistwidget.h"

class PreferenceWidget : public QWidget
{
    Q_OBJECT
public:
    static PreferenceWidget* getInstance();

private:
    PreferenceManager *preferenceManager_m;
    HdListWidget *hdListWidget_m;

    explicit PreferenceWidget();
    QWidget *getStyleWidget();
    void addColorsToComboBox(QComboBox *comboBox);
    void addFontSizeToComboBox(QComboBox *comboBox);
    void addFontToComboBox(QComboBox *comboBox);
    void load();

    // editor
    QComboBox *fontComboBox_m;
    QComboBox *fontSizeComboBox_m;
    QComboBox *textColorComboBox_m;
    QComboBox *backgroundColorComboBox_m;

signals:

public slots:
    void initializeClicked();
    void cancelClicked();
    void saveClicked();
};

#endif // WINDOW_PREFERENCEWIDGET_H
