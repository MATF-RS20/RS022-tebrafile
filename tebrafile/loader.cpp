#include "loader.h"
#include "logger.h"


#include <QFile>
#include <QDebug>

#include <QStandardPaths>

#include <iostream>


void Uploader::uploadProcessProgress(qint64 done, qint64 total)
{
    qDebug() << total;
    emit signalProgress(processId, done, total);
}

void Downloader::downloadProcessProgress(qint64 done, qint64 total)
{
    qDebug() << total;
    emit signalProgress(processId, done, total);
}

void Uploader::run()
{
    const auto nameParts = fileName.split("/");
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        loger->consoleLog(fileName + " can not be uploaded.");
    }
    const auto buffer = file.readAll();
    processId = client->put(buffer, nameParts.last(), QFtp::Binary);

    QObject::connect(client.data(), &QFtp::commandFinished, this, &Uploader::handleFinish);
    QObject::connect(client.data(), &QFtp::dataTransferProgress, this, &Uploader::uploadProcessProgress);
}


void Uploader::handleFinish(int id, bool error)
{
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
    QObject::connect(client.data(), &QFtp::dataTransferProgress, this, &Downloader::downloadProcessProgress);

}

void Downloader::handleFinish(int id, bool error)
{
    if (error && id == processId) {
        loger->consoleLog(client->errorString());
        emit downloadError();
    }
}

QString Loader::getFileName(){ return fileName;}
