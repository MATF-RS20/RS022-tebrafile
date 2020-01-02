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

void MainWindow::login(InputDialog* diag)
{
    QStringList credentials = InputDialog::getStrings(diag);
    username = credentials.at(0);
    password = credentials.at(1);
    ftpClient->login(username, password);
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
                InputDialog* diag = new InputDialog(this,
                                                    QString("username"),
                                                    QString("password"));
                QObject::connect(diag, &InputDialog::credentialsCaptured, this, &MainWindow::login);
                diag->exec();
            } else {
                //std::cerr << ftpClient->error() << std::endl;
                QMessageBox errBox;
                errBox.setWindowTitle("Connection error");
                errBox.setText(ftpClient->errorString());
                errBox.setIcon(QMessageBox::Critical);
                errBox.exec();
                ftpClient->close();
            }

        } else
            qDebug() << "greska ";

        QObject::connect(ftpClient, &QFtp::listInfo, this, &MainWindow::addToList);
        QObject::connect(ftpClient, &QFtp::done, this, &MainWindow::ftpDone);
        ftpClient->list("./");
}

void MainWindow::on_disconnectButton_clicked()
{
    ftpClient->close();
}
