#include "loader.h"
#include "logger.h"

#include <QFile>
#include <QDebug>

#include <QStandardPaths>

#include <iostream>


void Loader::processProgress(qint64 done, qint64 total)
{
    emit signalProgress(processId, done, total);
    if(done == total)
        loger->consoleLog(fileName + " upload zavrsen.");

}

void Uploader::run()
{
    const auto nameParts = fileName.split("/");
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        loger->consoleLog(fileName + " can not be uploaded.");
    }
    const auto buffer = file.readAll();
    //pwdId = client->rawCommand("PWD");
    processId = client->put(buffer, nameParts.last(), QFtp::Binary);
    QObject::connect(client.data(), &QFtp::commandFinished, this, &Uploader::handleFinish);
    QObject::connect(client.data(), &QFtp::dataTransferProgress, this, &Loader::processProgress);
}


void Uploader::handleFinish(int id, bool error)
{
    //std::cout << client->currentCommand() << ":" << std::endl;
    //std::cout << id << "==" << pwdId << "-" <<error<< std::endl;
    if (error && id == processId) {
        loger->consoleLog(client->errorString());
        emit uploadError();
    }
}


void Downloader::run()
{
    QFile* file;

    QString downloadsFolder = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation);

    file = new QFile(downloadsFolder + "/" + fileName);

    if(!file->open(QIODevice::WriteOnly)) {
        loger->consoleLog("Unable to save the file "+ fileName + ": " + file->errorString());
        delete file;
        return;
    }

    processId = client->get(fileName, file);
    QObject::connect(client.data(), &QFtp::commandFinished, this, &Downloader::handleFinish);
    QObject::connect(client.data(), &QFtp::dataTransferProgress, this, &Loader::processProgress);

}

void Downloader::handleFinish(int id, bool error)
{
    if (error)
        loger->consoleLog(client->errorString());
    else
        loger->consoleLog(fileName + " Download zavrsen.");
}
