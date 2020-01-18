#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "serverconnection.h"
#include "loader.h"
#include "listFiles.h"
#include "search.h"
#include "inputDialog.h"

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
#include <QDebug>
#include <QHeaderView>
#include <QString>

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
    static QMutex downloadMutex;

public slots:
    void initTreeWidget();

private slots:
    void on_connectButton_clicked();
    void on_disconnectButton_clicked();
    void on_openButton_clicked();
    void on_uploadButton_clicked();
    void on_downloadButton_clicked();
    void on_treeWidget_clicked();
    void on_startButton_clicked();
    void on_stopButton_clicked();
    void on_searchWidget_clicked();
    void uploadProgressBarSlot(int id, qint64 done, qint64 total);
    void downloadProgressBarSlot(int id, qint64 done, qint64 total);

    void searchDone();

    void uploadErrorHandler();
    void downloadErrorHandler();


private:
    Ui::MainWindow *ui;
    ServerConnection* serverConn = nullptr;

    QVector<Loader*> loaders;
    QHash<int, QPair<qint64, qint64>> uploadData;
    QHash<int, QPair<qint64, qint64>> downloadData;

    QSharedPointer<Logger> _logger;
    QString path;

    ListFiles *fileList = nullptr;
    ListFiles *searchList = nullptr;

    Search *s = nullptr;
    QSharedPointer<QFtp> client;
};
#endif // MAINWINDOW_H
