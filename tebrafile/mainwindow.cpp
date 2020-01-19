#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "searchdialog.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _logger = QSharedPointer<Logger>(new Logger(ui->textEdit));

    fileList = new ListFiles(ui->treeWidget);
    //searchList = new ListFiles(ui->searchWidget);
}

MainWindow::~MainWindow()
{
    delete fileList;
    delete ui;
}

QSharedPointer<QFtp>& MainWindow::getClient()
{
    return client;
}

QSharedPointer<Logger> MainWindow::getLogger()
{
    return _logger;
}

Ui::MainWindow* MainWindow::getUI()
{
   return ui;
}

ServerConnection* MainWindow::getConnection()
{
    return serverConn;
}

void MainWindow::on_connectButton_clicked()
{
    serverConn = new ServerConnection(this, QUrl(ui->serverNameField->text()), _logger);
    serverConn->connectToServer();
    QObject::connect(serverConn, &ServerConnection::connectionEstablished, this, &MainWindow::initTreeWidget);
}


void MainWindow::initTreeWidget()
{
    fileList->setServerConn(serverConn->getClient());
    fileList->listFiles(QString("~/"));
}

void MainWindow::on_disconnectButton_clicked()
{
    if (nullptr == serverConn)
        _logger->consoleLog("Not connected.");
    else if (!serverConn->isConnected())
        _logger->consoleLog("Not connected.");
    else {
        _logger->consoleLog("You are disconnected.");
        serverConn->setLogged(false);
        fileList->restartTreeWidget();
        //searchList->restartTreeWidget();
        fileList->clearPath();
    }
}

void MainWindow::on_openButton_clicked()
{
    const auto filenames = QFileDialog::getOpenFileNames(
                this,
                "Select files",
                QDir::homePath());
    ui->uploadFileInput->setText(filenames.join(';'));
}

void MainWindow::on_uploadButton_clicked()
{
    if (ui->uploadFileInput->text().trimmed().length() == 0)
        Logger::showMessageBox("Alert", "Files did not selected.", QMessageBox::Critical);
    else if (!serverConn->isLogged())
        Logger::showMessageBox("Alert", "You are not logged.", QMessageBox::Critical);
    else if (!serverConn->isConnected())
        Logger::showMessageBox("Alert", "You are not connected.", QMessageBox::Critical);
    else {
        serverConn->getClient()->rawCommand("PWD");
        QObject::connect(serverConn->getClient().data(), &QFtp::rawCommandReply,
                             this, &MainWindow::pwdHandler);
        fileList->getTreeWidget()->setEnabled(false);
        const auto fileNames = ui->uploadFileInput->text().split(";");
        std::for_each(std::begin(fileNames), std::end(fileNames), [&](const auto& fileName){
            auto upload = new Uploader(fileName, serverConn->getClient(), _logger);
            loaders.push_back(upload);
            upload->start();
            QObject::connect(upload, &Loader::signalProgress, this, &MainWindow::uploadProgressBarSlot);
            QObject::connect(upload, &Loader::uploadError, this, &MainWindow::uploadErrorHandler);
        });
    }
}



void MainWindow::on_downloadButton_clicked()
{
    path = fileList->getPath();
    if (path.isEmpty())
        path = "~";

    //negde mora ui->downloadButton->setEnabled(false);
    ui->downloadCancel->setEnabled(true);


    if (ui->downloadFileInput->text().trimmed().length() == 0)
        Logger::showMessageBox("Alert", "Files did not selected.", QMessageBox::Critical);
    else if (!serverConn->isLogged())
        Logger::showMessageBox("Alert", "You are not logged.", QMessageBox::Critical);
    else if (!serverConn->isConnected())
        Logger::showMessageBox("Alert", "You are not connected.", QMessageBox::Critical);
    else {
        const auto fileNames = ui->downloadFileInput->text().split(";");
        std::for_each(std::begin(fileNames), std::end(fileNames), [&](const auto& fileName){
            auto name = fileName.right(fileName.length() - fileName.lastIndexOf('/'));
            // qDebug() << name;
            auto currentPath = fileName.left(fileName.lastIndexOf('/'));
            // qDebug() << currentPath;
            if (currentPath == fileName) {
                currentPath = path + "/";
            }

            serverConn->getClient()->cd(currentPath);
            auto download = new Downloader(name, serverConn->getClient(), _logger);
            loaders.push_back(download);
            download->start();
            QObject::connect(download, &Loader::signalProgress, this, &MainWindow::downloadProgressBarSlot);
            QObject::connect(download, &Loader::downloadError, this, &MainWindow::downloadErrorHandler);
        });
    }

}


void MainWindow::on_treeWidget_clicked()
{
    //ui->searchWidget->clearSelection();
    const auto filenames = fileList->getTreeWidget()->selectedItems();
    QStringList filenamesQ;

    //ruzno ali radi
    // fix sa refactorisanjem i std::transform
    QString temp;
    for(auto filename : filenames)
    {
        temp = filename->text(0);
        if (fileList->isSelectedFile(temp)) {
            filenamesQ.push_back(temp);
        }
    }

    ui->downloadFileInput->setText(filenamesQ.join(';'));
}

QMutex MainWindow::uploadMutex;

void MainWindow::uploadProgressBarSlot([[maybe_unused]]int id, qint64 done, qint64 total)
{
    uploadMutex.lock();

    ui->uploadProgressBar->setValue(static_cast<int>(100* done / total));
    if (done == total) {
        ui->uploadProgressBar->setValue(static_cast<int>(100*done / total));
        fileList->getTreeWidget()->setEnabled(true);
        for (auto loader : loaders)
            if (loader->isFinished()) {
                _logger->consoleLog(loader->getFileName() + " upload is finished.");
                loader->exit();
                delete dynamic_cast<Uploader*>(loader);
            }

        loaders.clear();
    }
    uploadMutex.unlock();
}

QMutex MainWindow::downloadMutex;

void MainWindow::downloadProgressBarSlot([[maybe_unused]]int id, qint64 done, qint64 total)
{
    ui->downloadProgressBar->setValue(static_cast<int>(100*done / total));
    if (done == total) {
        serverConn->getClient()->cd(path);
        fileList->getTreeWidget()->setEnabled(true);
        for (auto loader : loaders)
            if (loader->isFinished()) {
                auto name = loader->getFileName();
                if (name.contains("/"))
                    name = name.remove(0, 1);
                _logger->consoleLog(name + " dowload is finished.");
                loader->exit();
                delete dynamic_cast<Downloader*>(loader);
            }
        loaders.clear();
    }
    downloadMutex.unlock();
}

void MainWindow::uploadErrorHandler()
{
    serverConn->getClient()->rawCommand("PWD");
    for (auto loader : loaders)
        if (loader->isFinished()) {
            loader->exit();
            delete dynamic_cast<Uploader*>(loader);
        }

    loaders.clear();
    fileList->getTreeWidget()->setEnabled(true);
}

void MainWindow::downloadErrorHandler()
{
    for (auto loader : loaders)
        if (loader->isFinished()) {
            loader->exit();
            delete dynamic_cast<Downloader*>(loader);
        }
    loaders.clear();
    fileList->getTreeWidget()->setEnabled(true);
}


void MainWindow::on_downloadCancel_clicked()
{
    if(serverConn->getClient()->hasPendingCommands())
        serverConn->getClient()->clearPendingCommands();

    serverConn->getClient()->abort();

    ui->downloadProgressBar->setValue(0);
    loaders.clear();

    QDir dir;
    QString downloadsFolder = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation);
    const auto fileNames = ui->downloadFileInput->text().split(";");

    for(auto fileName : fileNames)
    {
        dir.remove(downloadsFolder + "/" + fileName);
        _logger->consoleLog(fileName + ": Download canceled.");
    }

    serverConn->getClient()->disconnect();
    serverConn->relogIn();

    ui->downloadCancel->setEnabled(false);
}



void MainWindow::on_searchButton_clicked()
{
    if (nullptr == serverConn){
        _logger->consoleLog("You must be connected.");
        return;
    } else if (!serverConn->isLogged()) {
        Logger::showMessageBox("Alert", "You are not logged.", QMessageBox::Critical);
        return;
    }
    SearchDialog s(this);
    s.exec();
}

void MainWindow::pwdHandler([[maybe_unused]]int replyCode, [[maybe_unused]]const QString& detail)
{
    // qDebug() << "-----------------------";
    // qDebug() << detail;
    // qDebug() << "-----------------------";

}
