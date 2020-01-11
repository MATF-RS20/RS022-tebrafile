#ifndef SEARCH_H
#define SEARCH_H

#include "listFiles.h"

#include <QFtp>
#include <QSharedPointer>
#include <QTreeWidget>
#include <QHeaderView>
#include <QHash>
#include <iostream>

class Search : public QObject
{
    Q_OBJECT
public:
    Search(QSharedPointer<ListFiles> treeWidget, QString filename, QString path, const QSharedPointer<QFtp>& client);
    ~Search(){

    }
    void search();
    void addToList(const QUrlInfo& file);

private slots:
    void folderFinnished(bool error);

private:
    QSharedPointer<ListFiles> _treeWidget;
    QString _filename;
    QString _path;
    QSharedPointer<QFtp> _client;
    QVector<QString> _folders;
};


#endif // SEARCH_H
