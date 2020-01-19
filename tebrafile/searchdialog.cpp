#include "searchdialog.h"
#include "ui_searchdialog.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "search.h"

SearchDialog::SearchDialog(MainWindow* mainWindow, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchDialog),
    _mainWindow(mainWindow)
{
    ui->setupUi(this);
    _searchList = new ListFiles(ui->searchWidget);
}

SearchDialog::~SearchDialog()
{
    delete ui;
}

void SearchDialog::on_startButton_clicked()
{
    QString filename = ui->searchFile->text().trimmed();
    if (filename.length() == 0) {
        _mainWindow->getLogger()->consoleLog("File name can't be empty string.");
        return;
    }
    QRegularExpression *re = new QRegularExpression(filename);
    if (!re->isValid()) {
        _mainWindow->getLogger()->consoleLog("Wrong regular expression.");
        return;
    }
    QString path = ui->searchPath->text().trimmed();
    if (path.length() == 0) {
        path = QString("~");
    }
    _mainWindow->getClient() = QSharedPointer<QFtp>(new QFtp(this));
    _mainWindow->getClient()->connectToHost(QUrl(_mainWindow->getUI()->serverNameField->text()).host(), static_cast<quint16>(QUrl(_mainWindow->getUI()->serverNameField->text()).port(21)));
    _mainWindow->getClient()->login(_mainWindow->getConnection()->getUsername(), _mainWindow->getConnection()->getPasswd());


    if (_s == nullptr || !_s->isOngoing()) {
        _s = new Search(QSharedPointer<ListFiles>(_searchList), QSharedPointer<QRegularExpression>(re), path, _mainWindow->getClient());
        QObject::connect(_s, &Search::searchFinished,
                         this, &SearchDialog::searchDone,
                         Qt::QueuedConnection);
        _s->start();
    }

}


void SearchDialog::searchDone()
{
    _mainWindow->getLogger()->consoleLog("Search finished.\n" + QString::number(_s->numOfFoundItems()) + " items found.");
    qDebug() << "done";
}

void SearchDialog::on_stopButton_clicked()
{
    if(_s != nullptr)
        _s->stopSearch();
}




void SearchDialog::on_searchWidget_clicked()
{
    _mainWindow->getUI()->treeWidget->clearSelection();
    const auto filenames = _searchList->getTreeWidget()->selectedItems();
    QStringList filenamesQ;

    // ruzno ali radi
    // fix sa refactorisanjem i std::transform
    QString temp;
    for(auto filename : filenames)
    {
        temp = filename->text(0);
        filenamesQ.push_back(temp);
    }

    _mainWindow->getUI()->downloadFileInput->setText(filenamesQ.join(';'));
}
