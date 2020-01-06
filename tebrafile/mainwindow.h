#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "serverconnection.h"
#include "loader.h"

#include <iostream>

#include <QMainWindow>
#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QFileDialog>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QFtp>
#include <QHash>
#include <QTreeWidget>
#include <QDir>
#include <QStandardPaths>
#include <QThread>
#include <QUrl>
#include <QMutex>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void getFileList();
    static QMutex uploadMutex;

public slots:
    void addToList(const QUrlInfo& file);
    void initTreeWidget();
    void restartTreeWidget();
    void listDone(bool error);
    void listFiles(const QString& fileName);
    void cdToFolder(QTreeWidgetItem *widgetItem, int column);
    void leaveFolder();


private slots:
    void on_connectButton_clicked();
    void on_disconnectButton_clicked();
    void on_openButton_clicked();
    void on_uploadButton_clicked();
    void on_downloadButton_clicked();
    void on_treeWidget_clicked();
    void on_header_clicked(int logicalIndex);
    void uploadProgressBarSlot(int id, qint64 done, qint64 total);
    void downloadProgressBarSlot(qint64 done, qint64 total);

private:
    Ui::MainWindow *ui;
    ServerConnection* serverConn;


    QVector<Loader*> loaders;
    QHash<int, QPair<qint64, qint64>> uploadData;
    QHash<int, QPair<qint64, qint64>> downloadData;

    QTreeWidget *fileList;
    QHash<QString, bool> isDir;
    QString currentPath;

    QHeaderView *headerView;

    QSharedPointer<Logger> _logger;
};
#endif // MAINWINDOW_H
