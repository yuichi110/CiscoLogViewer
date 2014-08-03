#ifndef SHORTCUTBUTTON_H
#define SHORTCUTBUTTON_H

#include <QPushButton>

class ShortcutButton : public QPushButton
{
    Q_OBJECT
public:
    explicit ShortcutButton(QWidget *parent, QString layer, QString group);
    QString getGroup();
    QString getLayer();

private:
    QString group_m;
    QString layer_m;

protected:

signals:
    
public slots:
    
};

#endif // SHORTCUTBUTTON_H
