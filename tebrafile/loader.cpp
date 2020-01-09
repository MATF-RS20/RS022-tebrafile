#include "loader.h"
#include "logger.h"

#include <QFile>
#include <QDebug>
#include <iostream>

void Loader::processProgress(qint64 done, qint64 total)
{
    emit signalProgress(processId, done, total, fileName);
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
    QObject::connect(client.data(), &QFtp::dataTransferProgress, this, &Loader::processProgress);
}


void Uploader::handleFinish(int id, bool error)
{
    if (error && id == processId) {
        loger->consoleLog(client->errorString());
        emit uploadError();
    }
}
