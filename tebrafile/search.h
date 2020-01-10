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
    Search(QSharedPointer<ListFiles> treeWidget, QString filename, QString path);
    ~Search(){

    }

private:
    QSharedPointer<ListFiles> _treeWidget;
    QString _filename;
    QString _path;
};


#endif // SEARCH_H
