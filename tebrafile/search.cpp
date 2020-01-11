#include "search.h"
#include "listFiles.h"

#include <QRegularExpression>
#include <QDebug>

Search::Search(QSharedPointer<ListFiles> treeWidget, const QSharedPointer<QRegularExpression> filename, QString path, const QSharedPointer<QFtp>& client)
    :_treeWidget(treeWidget), _filename(filename), _path(path), _client(client)
{
    _folders.clear();
    _treeWidget->restartTreeWidget();
    _treeWidget->getTreeWidget()->takeTopLevelItem(0);
    _treeWidget->setServerConn(_client);
    _treeWidget->getTreeWidget()->setEnabled(true);
    QObject::connect(_client.data(), &QFtp::listInfo, this, &Search::addToList);
    QObject::connect(_client.data(), &QFtp::done, this, &Search::folderFinished);
}

void Search::search()
{
    _client->list(_path);
}

void Search::folderFinished(bool error)
{
    if (error) {
        std::cerr << "Error: " << qPrintable(_client->errorString()) << std::endl;
    } else if (_stop == false){
        if (_folders.isEmpty()) {
            emit searchFinished();
        }
        _path = _folders.takeFirst();
        _client->list(_path);
    }
}

void Search::addToList(const QUrlInfo& file)
{
    if (_stop == false) {
        if (!file.isDir()) {
            if (_filename->match(file.name()).hasMatch())
                 _treeWidget->addToList(file);
        } else {
            _folders.push_back(_path + "/" + file.name());
        }
    }
}

void Search::stopSearch()
{
    _stop = true;
    _folders.clear();
    emit searchFinished();
}
