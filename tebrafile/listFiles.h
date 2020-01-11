#ifndef LISTFILES_H
#define LISTFILES_H

#include <QFtp>
#include <QSharedPointer>
#include <QTreeWidget>
#include <QHeaderView>
#include <QHash>
#include <iostream>

class ListFiles : public QObject
{
    Q_OBJECT
public:
    ListFiles(QTreeWidget* treeWidget);
    ~ListFiles(){

    }

    void listFiles(const QString& fileName);
    void addToList(const QUrlInfo& file);
    void cdToFolder(QTreeWidgetItem *widgetItem, int column);
    void leaveFolder();
    void restartTreeWidget();
    void clearPath();
    QSharedPointer<QTreeWidget> getTreeWidget() const;
    QSharedPointer<QHeaderView> getHeaderView() const;
    void setServerConn(const QSharedPointer<QFtp>& serverConn);

private slots:
    void listDone(bool error);
    void on_header_clicked(int logicalIndex);

private:
    QSharedPointer<QTreeWidget> _treeWidget;
    QSharedPointer<QFtp> _serverConn;
    QSharedPointer<QHeaderView> _headerView;
    QHash<QString, bool> _isDir;
    QString _currentPath;
};

#endif // LISTFILES_H
