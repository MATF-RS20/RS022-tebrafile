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
    void login(InputDialog* diag);

private slots:
    void on_connectButton_clicked();

    void on_disconnectButton_clicked();

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

    QStringList fileList;
    QString uploadFileName;
    QString downloadFIlename;


    void connectToServer();
};
#endif // MAINWINDOW_H
