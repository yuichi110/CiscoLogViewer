#include "ws_deepsearchwidget.h"

const QString DeepSearchWidget::GROUP_SEARCH = "__SEARCH__";

DeepSearchWidget::DeepSearchWidget(QWidget *parent, QString clvFilePath) :
    QWidget(parent)
{
    clvFilePath_m = clvFilePath;

    QVBoxLayout *layout = new QVBoxLayout(this);
    QHBoxLayout *searchLineLayout = new QHBoxLayout();
    searchWordArea_m = new QLineEdit(this);
    searchWordArea_m->installEventFilter(this);
    searchLineLayout->addWidget(searchWordArea_m);
    QPushButton *searchButton = new QPushButton("search", this);
    searchButton->connect(searchButton, SIGNAL(clicked()), this, SLOT(searchButtonClicked()));
    searchLineLayout->addWidget(searchButton);
    layout->addLayout(searchLineLayout);

    searchLogView_m = new LogView(this, "", GROUP_SEARCH, clvFilePath_m, "", true, false);
    layout->addWidget(searchLogView_m);
    setLayout(layout);

    searcher_m = new DeepCommandSearcher(this, clvFilePath_m);
    progressDialog_m = new ProgressDialog(this, searcher_m);
    connect(searcher_m, SIGNAL(signalSearchFinished(QString)), this, SLOT(searchFinished(QString)));
}

bool DeepSearchWidget::eventFilter(QObject *obj, QEvent *e){
    if(obj == searchWordArea_m && e->type() == QEvent::KeyPress){
        QKeyEvent *ke = (QKeyEvent*)e;
        int key = ke->key();
        if(key == Qt::Key_Enter || key == Qt::Key_Return){
                searchButtonClicked();
        }
    }
}

void DeepSearchWidget::searchButtonClicked(){
    searchLogView_m->unLoadLogs();
    QString searchText = searchWordArea_m->text();
    searchText = searchText.trimmed();
    if(searchText == ""){
        return;
    }

    searcher_m->setSearchText(searchText);
    searcher_m->start();
}

void DeepSearchWidget::searchFinished(QString idListString){
    if(idListString == ""){
        return;
    }

    QStringList list = idListString.split(",");
    QList<int> idList;
    foreach(QString idText, list){
        int id = idText.toInt();
        idList.append(id);
    }

    searchLogView_m->loadLogs(idList);
}
