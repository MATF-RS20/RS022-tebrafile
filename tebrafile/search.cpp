#include "search.h"
#include "listFiles.h"

#include <QDebug>

Search::Search(QSharedPointer<ListFiles> treeWidget, QString filename, QString path, const QSharedPointer<QFtp>& client)
    :_treeWidget(treeWidget), _filename(filename), _path(path), _client(client)
{
    _treeWidget->setServerConn(_client);
    _treeWidget->getTreeWidget()->setEnabled(true);
    QObject::connect(_client.data(), &QFtp::listInfo, this, &Search::addToList);
    QObject::connect(_client.data(), &QFtp::done, this, &Search::folderFinnished);
}

void Search::search()
{
    _client->list(_path);
}

void Search::folderFinnished(bool error)
{
    if (error) {
        std::cerr << "Error: " << qPrintable(_client->errorString()) << std::endl;
    } else {
        _path = _folders.takeFirst();
        _client->list(_path);
    }
}

void Search::addToList(const QUrlInfo& file)
{
    if (!file.isDir()) {
        if (_filename == file.name())
             _treeWidget->addToList(file);
    } else {
        _folders.push_back(_path + "/" + file.name());
    }
}
