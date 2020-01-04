#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "inputDialog.h"

#include <iostream>

#include <QMainWindow>
#include <QDebug>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>
#include <QFile>
#include <QFileInfo>
#include <QFileDialog>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QFtp>
#include <QHash>
#include <QTreeWidget>



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

signals:
    void done();

public slots:
    void addToList(const QUrlInfo& file);
    void ftpDone(bool error);
    void showLoginDialog(int state);
    void login(InputDialog* diag);
    void afterLogin(int state);
    void listDone(bool error);
    void listFiles(const QString& fileName);
    void cdToFolder(QTreeWidgetItem *widgetItem, int column);
    void leaveFolder();
    void progressBarSlot(qint64 done, qint64 total);
    void uploadFinishHandler(int id, bool error);
    void pwdHandler(int replyCode, const QString& detail);

private slots:
    void on_connectButton_clicked();
    void on_disconnectButton_clicked();

    void on_openButton_clicked();

    void on_uploadButton_clicked();

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager* manager;
    QFtp* ftpClient;



    QString ftpAdrress;
    int ftpPort;
    QString username = "default1";
    QString password = "DEFAULT1";

    QUrl url;

    QNetworkReply* downloadFileListReply;
    QNetworkReply* uploadFileListReply;

    QNetworkReply* downloadFileReply;
    QNetworkReply* uploadFileReply;


    QTreeWidget *fileList;
    QHash<QString, bool> isDir;
    QString currentPath;
    QString uploadFileName;
    QString downloadFIlename;

    bool logged = false;

    void connectToServer();
};
#endif // MAINWINDOW_H
