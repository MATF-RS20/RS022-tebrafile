#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <iostream>

#include <QTreeView>
#include <QHeaderView>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _logger = QSharedPointer<Logger>(new Logger(ui->textEdit));

    fileList = new ListFiles(ui->treeWidget);
    searchList = new ListFiles(ui->searchWidget);
}

MainWindow::~MainWindow()
{
    delete fileList;
    delete ui;
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
        fileList->restartTreeWidget();
        fileList->clearPath();
    }
}

void MainWindow::on_startButton_clicked()
{
    if (nullptr == serverConn){
        _logger->consoleLog("You must be connected.");
        return;
    } else if (!serverConn->isLogged()) {
        _logger->consoleLog("You must be logged in.");
        return;
    }
    QString filename = ui->searchFile->text().trimmed();
    if (filename.length() == 0) {
        _logger->consoleLog("File name can't be empty string.");
        return;
    }
    QRegularExpression *re = new QRegularExpression(filename);
    if (!re->isValid()) {
        _logger->consoleLog("Wrong regular expression.");
        return;
    }
    QString path = ui->searchPath->text().trimmed();
    if (path.length() == 0) {
        path = QString("~");
    }

    client = QSharedPointer<QFtp>(new QFtp(this));
    client->connectToHost(QUrl(ui->serverNameField->text()).host(), static_cast<quint16>(QUrl(ui->serverNameField->text()).port(21)));
    QStringList credentials = InputDialog::getStrings(serverConn->getDiag().data());
    client->login(credentials.at(0), credentials.at(1));

    if (s == nullptr || !s->isOngoing()) {
        s = new Search(QSharedPointer<ListFiles>(searchList), QSharedPointer<QRegularExpression>(re), path, client);
        QObject::connect(s, &Search::searchFinished,
                         this, &MainWindow::searchDone,
                         Qt::QueuedConnection);
        s->start();
    }

}

void MainWindow::searchDone()
{
    qDebug() << "done";
}

void MainWindow::on_stopButton_clicked() {
    if(s != nullptr)
        s->stopSearch();
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


    //negde mora ui->downloadButton->setEnabled(false);



    if (ui->downloadFileInput->text().trimmed().length() == 0)
        Logger::showMessageBox("Alert", "Files did not selected.", QMessageBox::Critical);
    else if (!serverConn->isLogged())
        Logger::showMessageBox("Alert", "You are not logged.", QMessageBox::Critical);
    else if (!serverConn->isConnected())
        Logger::showMessageBox("Alert", "You are not connected.", QMessageBox::Critical);
    else {
        const auto fileNames = ui->downloadFileInput->text().split(";");
        std::for_each(std::begin(fileNames), std::end(fileNames), [&](const auto& fileName){
            auto download = new Downloader(fileName, serverConn->getClient(), _logger);
            loaders.push_back(download);
            download->start();
            QObject::connect(download, &Loader::signalProgress, this, &MainWindow::downloadProgressBarSlot);
            QObject::connect(download, &Loader::downloadError, this, &MainWindow::downloadErrorHandler);
        });
    }

}


void MainWindow::on_treeWidget_clicked()
{
    const auto filenames = fileList->getTreeWidget()->selectedItems();
    QStringList filenamesQ;

    //ruzno ali radi
    // fix sa refactorisanjem i std::transform
    QString temp;
    for(auto filename : filenames)
    {
        temp = filename->text(0);
        filenamesQ.push_back(temp);
    }


    ui->downloadFileInput->setText(filenamesQ.join(';'));

}

QMutex MainWindow::uploadMutex;

void MainWindow::uploadProgressBarSlot(int id, qint64 done, qint64 total)
{
    uploadMutex.lock();
    uploadData[id] = qMakePair(done, total);
    QPair<qint64, qint64> currentProgress = std::accumulate(
                    std::begin(uploadData),
                    std::end(uploadData),
                    qMakePair<qint64, qint64>(0, 0),
                    [](auto acc, auto elem) {
                        return qMakePair<qint64, qint64>(acc.first+elem.first, acc.second+elem.second);
                    });
    ui->uploadProgressBar->setValue(100*currentProgress.first / currentProgress.second);
    if (currentProgress.first == currentProgress.second) {
        ui->uploadProgressBar->setValue(100*done / total);
        fileList->getTreeWidget()->setEnabled(true);
        for (auto loader : loaders)
            if (loader->isFinished()) {
                _logger->consoleLog(loader->getFileName() + " upload is finished.");
                loader->exit();
                delete dynamic_cast<Uploader*>(loader);
            }
        uploadData.clear();
        loaders.clear();
    }
    uploadMutex.unlock();
}

QMutex MainWindow::downloadMutex;

void MainWindow::downloadProgressBarSlot(int id, qint64 done, qint64 total)
{
    ui->downloadProgressBar->setValue(100*done / total);
    if (done == total) {
        fileList->getTreeWidget()->setEnabled(true);
        for (auto loader : loaders)
            if (loader->isFinished()) {
                _logger->consoleLog(loader->getFileName() + " dowload is finished.");
                loader->exit();
                delete dynamic_cast<Downloader*>(loader);
            }
        downloadData.clear();
        loaders.clear();
    }
    downloadMutex.unlock();
}

void MainWindow::uploadErrorHandler()
{
    for (auto loader : loaders)
        if (loader->isFinished()) {
            loader->exit();
            delete dynamic_cast<Uploader*>(loader);
        }
    uploadData.clear();
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
    downloadData.clear();
    loaders.clear();
    fileList->getTreeWidget()->setEnabled(true);
}
