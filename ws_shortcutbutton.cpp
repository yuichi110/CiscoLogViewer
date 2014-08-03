#include "ws_shortcutbutton.h"

ShortcutButton::ShortcutButton(QWidget *parent, QString layer, QString group) :
    QPushButton(parent)
{
    layer_m = layer;
    group_m = group;
}

QString ShortcutButton::getGroup(){
    return group_m;
}

QString ShortcutButton::getLayer(){
    return layer_m;
}
