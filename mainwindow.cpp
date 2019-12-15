#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    manager = new QNetworkAccessManager(this);
    ftpClient = new QFtp();

    //ftpAdrress = "ftp://speedtest.tele2.net/1KB.zip";
    ftpAdrress = "ftp://mi16077@alas.matf.bg.ac.rs/";
    ftpPort = 20;

    //ftpAdrress = "ftp://localhost/ftp/files/";

    ftpClient->connectToHost(ftpAdrress);
    ftpClient->login(username, password);

    ftpClient->list();

    QObject::connect(ftpClient, &QFtp::listInfo, this, &MainWindow::addToList);
}


MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::addToList(const QUrlInfo& file)
{
    std::cout << file.name().toStdString() << std::endl;

}
