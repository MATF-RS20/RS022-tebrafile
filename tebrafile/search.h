#ifndef SEARCH_H
#define SEARCH_H

#include "listFiles.h"

#include <QFtp>
#include <QSharedPointer>
#include <QTreeWidget>
#include <QHeaderView>
#include <QHash>
#include <QDir>
#include <iostream>
#include <QThread>

class Search : public QThread
{
    Q_OBJECT
public:
    Search(QSharedPointer<ListFiles> treeWidget,
           const QSharedPointer<QRegularExpression> filename,
           QString path, const QSharedPointer<QFtp>& client);
    ~Search(){

    }
    void stopSearch();
    void addToList(const QUrlInfo& file);
    bool isOngoing();

private slots:
    void folderFinished(bool error);

signals:
    void searchFinished();

protected:
    void run() override;

private:
    QSharedPointer<ListFiles> _treeWidget;
    QSharedPointer<QRegularExpression> _filename;
    QString _path;
    QSharedPointer<QFtp> _client;
    QVector<QString> _folders;
    bool _stop = false;
    bool _ongoing = false;
};


#endif // SEARCH_H
