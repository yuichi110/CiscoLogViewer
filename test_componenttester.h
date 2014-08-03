#ifndef TEST_COMPONENTTESTER_H
#define TEST_COMPONENTTESTER_H

#include <QtWidgets>
#include "core_messagebroker.h"
#include "lv_logview.h"
#include "lv_logedit.h"
#include "lv_commandloader.h"
#include "mwc_layertab.h"
#include "dao_clvdataaccessor.h"
#include "core_clvloader.h"
#include "core_wstabmanager.h"
#include "ws_shortcutwidget.h"
#include "ws_searchcommandwidget.h"
#include "ws_onecommandwidget.h"
#include "ws_commandlistwidget.h"
#include "mwc_dropzone.h"
#include "pref_highlightdifinitionwidget.h"
#include "pref_hdlistwidget.h"
#include "pref_preferencewidget.h"
#include "dao_preferencedataaccessor.h"

class ComponentTester
{
public:
    ComponentTester();
    int testLogView(int argc, char *argv[]);
    int testLogEdit(int argc, char *argv[]);
    int testLayerTab(int argc, char *argv[]);
    int testLayerTab2(int argc, char *argv[]);
    int testCommandLoader(int argc, char *argv[]);
    int testShortcutWidget(int argc, char *argv[]);
    int testSearchCommandWidget(int argc, char *argv[]);
    int testCommandListWidget(int argc, char *argv[]);
    int testOneCommandWidget(int argc, char *argv[]);
    int testDropZone(int argc, char *argv[]);
    int testHighlightDefinitionWidget(int argc, char *argv[]);
    int testHdListWidget(int argc, char *argv[]);
    int testPreferenceWidget(int argc, char *argv[]);
    int testPreferenceAccessor(int argc, char *argv[]);
    int testDeepSearchWidget(int argc, char *argv[]);
    int testGetLayer();
    int testSubString();

};

#endif // TEST_COMPONENTTESTER_H
