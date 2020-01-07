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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initTreeWidget()
{
    fileList->setServerConn(serverConn->getClient());
    fileList->listFiles(QString("~/"));
}

void MainWindow::on_connectButton_clicked()
{
    serverConn = new ServerConnection(this, QUrl(ui->serverNameField->text()), _logger);
    serverConn->connectToServer();
    QObject::connect(serverConn, &ServerConnection::connectionEstablished, this, &MainWindow::initTreeWidget);
}

void MainWindow::on_disconnectButton_clicked()
{
    if (serverConn->isConnected())
        serverConn->~ServerConnection();
    else
        _logger->consoleLog("Not connected.");
    fileList->restartTreeWidget();
    fileList->clearPath();
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
        });
    }
}



void MainWindow::on_downloadButton_clicked()
{

    if (ui->downloadFileInput->text().trimmed().length() == 0)
        QMessageBox::critical(this, "Alert", "Files did not selected.");
    else
    {
        QFile* file;
        fileList->getTreeWidget()->setEnabled(false);
        ui->downloadButton->setEnabled(false);
        const auto downloadList = ui->downloadFileInput->text().split(";");


        //QString fileName = fileList->getTreewidget()->currentItem()->text(0);

        QString downloadsFolder = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation);


        for(auto fileName : downloadList)
        {
            file = new QFile(downloadsFolder + "/" + fileName);

            if (!file->open(QIODevice::WriteOnly)) {
             QMessageBox::information(this, tr("FTP"),
                                      tr("Unable to save the file %1: %2.")
                                      .arg(fileName).arg(file->errorString()));
             delete file;
             return;
            }

            serverConn->getClient()->get(fileName, file);
            QObject::connect(serverConn->getClient().data(), &QFtp::dataTransferProgress,
                             this, &MainWindow::downloadProgressBarSlot);

        }

    }
}

void MainWindow::downloadProgressBarSlot(qint64 done, qint64 total)
{
    ui->downloadProgressBar->setValue(100*done/total);
    if(done == total){
        fileList->getTreeWidget()->setEnabled(true);
        ui->downloadButton->setEnabled(true);
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
        fileList->getTreeWidget()->setEnabled(true);
        for (auto loader : loaders)
            if (loader->isFinished()) {
                loader->exit();
                delete dynamic_cast<Uploader*>(loader);
            }
        uploadData.clear();
        loaders.clear();
    }
    uploadMutex.unlock();
}
