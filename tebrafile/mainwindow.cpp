#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "inputDialog.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    manager = new QNetworkAccessManager(this);
    ftpClient = new QFtp(this);
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
    qDebug() << file.name();
}



void MainWindow::on_connectButton_clicked()
{
    ftpAdrress = "ftp://" + ui->serverNameField->text();
    connectToServer();
}


void MainWindow::connectToServer()
{
        url = QUrl(ftpAdrress);
        if (url.isValid()) {
            ftpClient->connectToHost(url.host(), url.port(21));
            std::cerr << ftpClient->error() << std::endl;
            if (ftpClient->error() == QFtp::NoError) {
                std::cout << "Unknown error: " << QFtp::UnknownError << std::endl;
                std::cout << "NoError: " << QFtp::NoError << std::endl;
                std::cout << "FTP MY ERROR: " << ftpClient->error() << std::endl;
                InputDialog* loginDialog = new InputDialog(this, QString("username"), QString("password"));
                QStringList credentials = loginDialog->getStrings();
                username = credentials.takeAt(0);
                password = credentials.takeAt(1);
                std::cout << username.toUtf8().data() << " " << password.toUtf8().data() << std::endl;
                //ftpClient->login(username, password);

            } else {
                //std::cerr << ftpClient->error() << std::endl;
                QMessageBox errBox;
                errBox.setWindowTitle("Connection error");
                errBox.setText(ftpClient->errorString());
                errBox.setIcon(QMessageBox::Critical);
                errBox.exec();
                ftpClient->disconnect();
            }

        } else
            qDebug() << "greska ";

        QObject::connect(ftpClient, &QFtp::listInfo, this, &MainWindow::addToList);
        QObject::connect(ftpClient, &QFtp::done, this, &MainWindow::ftpDone);
        ftpClient->list("./");
}
