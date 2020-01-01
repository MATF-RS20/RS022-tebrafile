#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    manager = new QNetworkAccessManager(this);
    ftpClient = new QFtp(this);

    //ftpAdrress = "ftp://mi16077@alas.matf.bg.ac.rs/";
    //ftpAdrress = "ftp://localhost/";
    ftpAdrress = "ftp://speedtest.tele2.net/";
    url = QUrl(ftpAdrress);
    username = "anonymous";
    password = "anonymous";
    if (url.isValid()) {
        ftpClient->connectToHost(url.host(), url.port(21));
        ftpClient->login(username, password);
    } else
        qDebug() << "greska ";

    QObject::connect(ftpClient, &QFtp::listInfo, this, &MainWindow::addToList);
    QObject::connect(ftpClient, &QFtp::done, this, &MainWindow::ftpDone);
    ftpClient->list("./");
}


void MainWindow::ftpDone(bool error)
{
    if (error) {
        std::cerr << "Error: " << qPrintable(ftpClient->errorString()) << std::endl;

    }
}


MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::addToList(const QUrlInfo& file)
{
    fileList.push_back(file.name());

}
