#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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


public slots:
    void addToList(const QUrlInfo& file);

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager* manager;
    QFtp* ftpClient;



    QString ftpAdrress;
    int ftpPort;
    QString username;
    QString password;

    QNetworkReply* downloadFileListReply;
    QNetworkReply* uploadFileListReply;

    QNetworkReply* downloadFileReply;
    QNetworkReply* uploadFileReply;

    QStringList fileList;
    QString uploadFileName;
    QString downloadFIlename;
};
#endif // MAINWINDOW_H
