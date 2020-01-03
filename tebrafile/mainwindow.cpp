#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QTreeView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    manager = new QNetworkAccessManager(this);
}



MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::connectToServer()
{
        ftpClient = new QFtp(this);
        url = QUrl(ftpAdrress);
        if (url.isValid()) {
            ftpClient->connectToHost(url.host(), url.port(21));
            QObject::connect(ftpClient, &QFtp::done, this, &MainWindow::ftpDone);
        } else
            qDebug() << "greska ";

       QObject::connect(ftpClient, &QFtp::stateChanged, this, &MainWindow::showLoginDialog);
}






/***
 *
 * IMPLEMENTACIJE SLOTOVA DOLE
 *
 ***/


void MainWindow::addToList(const QUrlInfo& file)
{
    fileList.push_back(file.name());
    qDebug() << file.name();
}



void MainWindow::ftpDone(bool error)
{
    if (error) {
        std::cerr << "Error: " << qPrintable(ftpClient->errorString()) << std::endl;
        ui->loginMsg->setText(ftpClient->errorString());
        ui->loginMsg->setStyleSheet("QLabel {color : red}");
        ftpClient->disconnect();
    }
}

void MainWindow::showLoginDialog(int state)
{
    if (state == QFtp::Connected and ftpClient->error() == QFtp::NoError) {
        InputDialog* diag = new InputDialog(this,
                                            QString("username"),
                                            QString("password"));
        QObject::connect(diag, &InputDialog::credentialsCaptured, this, &MainWindow::login);
        diag->exec();
    } else if (state == QFtp::Unconnected and ftpClient->currentCommand() != QFtp::Close){
        std::cerr << "ELSE ERROR: " << ftpClient->error() << std::endl;
        QMessageBox errBox;
        errBox.setWindowTitle("Connection error");
        errBox.setText(ftpClient->errorString());
        errBox.setIcon(QMessageBox::Critical);
        errBox.exec();
        ftpClient->close();
        ftpClient->disconnect();
    }

}

void MainWindow::login(InputDialog* diag)
{
    QStringList credentials = InputDialog::getStrings(diag);
    username = credentials.at(0);
    password = credentials.at(1);
    ftpClient->login(username, password);
    QObject::connect(ftpClient, &QFtp::stateChanged, this, &MainWindow::afterLogin);
}




void MainWindow::on_connectButton_clicked()
{

    ftpAdrress = ui->serverNameField->text();
    connectToServer();
}

void MainWindow::afterLogin(int state)
{
    if (state == QFtp::LoggedIn and ftpClient->currentCommand() == QFtp::Login) {
        QObject::connect(ftpClient, &QFtp::listInfo, this, &MainWindow::addToList);
        ftpClient->list("./");
        ftpClient->cd("upload");
        ui->loginMsg->clear();
    }
}




void MainWindow::on_disconnectButton_clicked()
{
    ftpClient->close();
    ftpClient->abort();
    ui->loginMsg->setText("You are disconnected");
}


void MainWindow::progressBarSlot(qint64 done, qint64 total)
{
    ui->uploadProgressBar->setValue(100*done/total);
    qDebug() << done << " " << total;
}



void MainWindow::on_openButton_clicked()
{

    //Poruka za Jola, ovako nesto moze
//    QFileDialog fileDialog;
//    fileDialog.setFileMode(QFileDialog::DirectoryOnly);
//    fileDialog.setOption(QFileDialog::DontUseNativeDialog, true);
//    QListView *l = fileDialog.findChild<QListView*>("listView");
//    if (l) {
//         l->setSelectionMode(QAbstractItemView::MultiSelection);
//     }
//    QTreeView *t = fileDialog.findChild<QTreeView*>();
//     if (t) {
//       t->setSelectionMode(QAbstractItemView::MultiSelection);
//    }
//    int node_m = fileDialog.exec();
//    const auto filenames = fileDialog.selectedFiles();

    const auto filenames = QFileDialog::getOpenFileNames(
                this,
                "Select files",
                "/");
    ui->uploadFileInput->setText(filenames.join(';'));
}

void MainWindow::on_uploadButton_clicked()
{
    if (ui->uploadFileInput->text().trimmed().length() == 0)
        QMessageBox::critical(this, "Alert", "Files did not selected.");

    const auto listOfFiles = ui->uploadFileInput->text().split(";");
    foreach (const auto file, listOfFiles) {
        const auto namesParts = file.split("/");
        QFile readFile(file);
        readFile.open(QIODevice::ReadOnly);
        const QByteArray buffer = readFile.readAll();
        ftpClient->put(buffer, namesParts.last(), QFtp::Binary);
        QObject::connect(ftpClient, &QFtp::dataTransferProgress,
                         this, &MainWindow::progressBarSlot);
    }
}
