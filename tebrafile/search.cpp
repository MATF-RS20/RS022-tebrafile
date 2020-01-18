#include "search.h"
#include "listFiles.h"

#include <QRegularExpression>
#include <QDebug>

Search::Search(QSharedPointer<ListFiles> treeWidget, const QSharedPointer<QRegularExpression> filename, QString path, const QSharedPointer<QFtp>& client)
    :_treeWidget(treeWidget), _filename(filename), _path(path), _client(client)
{
    _folders.clear();
    _treeWidget->restartTreeWidget();
    _treeWidget->getTreeWidget()->topLevelItem(0)->setDisabled(true);
    _treeWidget->setServerConn(_client);
    QObject::connect(_client.data(), &QFtp::listInfo, this, &Search::addToList);
    QObject::connect(_client.data(), &QFtp::done, this, &Search::folderFinished);
}

void Search::run()
{
    _ongoing = true;
    _client->list(_path);
}

void Search::folderFinished(bool error)
{
    if (error) {
        std::cerr << "Error: " << qPrintable(_client->errorString()) << std::endl;
    } else if (_stop == false){
        if (_folders.isEmpty()) {
            this->stopSearch();
            this->quit();
        }
        //qDebug() << _path;
        if(!_folders.isEmpty())
            _path = _folders.takeFirst();
        //if(QDir(_path).exists())
            _client->list(_path);
    }
}

void Search::addToList(const QUrlInfo& file)
{
    if (_stop == false) {
        if (!file.isDir()) {
            if (_filename->match(file.name()).hasMatch()){
                QUrlInfo tmp(file);
                tmp.setName(_path + "/" + file.name());
                 _treeWidget->addToList(tmp);
            }
        } else {
            _folders.push_back(_path + "/" + file.name());
        }
    }
}

void Search::stopSearch()
{
    _ongoing = false;
    _stop = true;
    _folders.clear();
    emit searchFinished();
}

bool Search::isOngoing() { return _ongoing; }

int Search::numOfFoundItems() const
{
    return _treeWidget->getTreeWidget()->topLevelItemCount() - 1;
}
