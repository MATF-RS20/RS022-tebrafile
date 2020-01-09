#ifndef LOADER_H
#define LOADER_H

#include "logger.h"

#include <QStringList>
#include <QSharedPointer>
#include <QFtp>
#include <QThread>

class Loader : public QThread
{
    Q_OBJECT

public slots:
    void processProgress(qint64 done, qint64 total);

signals:
    void signalProgress(int id, qint64 done, qint64 total);
    void uploadError();

protected:
    Loader(const QString& file, const QSharedPointer<QFtp>& ftpClient, const QSharedPointer<Logger>& logerPtr)
        :fileName(file), client(ftpClient)
    {
        loger = logerPtr;
    }
    ~Loader() override {

    }


    QString fileName;
    QSharedPointer<QFtp> client;
    int processId;
    QSharedPointer<Logger> loger;
};


class Uploader : public Loader
{
    Q_OBJECT
public:
    Uploader(const QString& file, const QSharedPointer<QFtp>& ftpClient, const QSharedPointer<Logger>& logerptr)
        :Loader(file, ftpClient, logerptr)
    {}

    void run() override;
    ~Uploader() override {

    }

private slots:
    void handleFinish(int id, bool error);
};

class Downloader : public Loader
{
    Q_OBJECT
public:
    Downloader(const QString& file, const QSharedPointer<QFtp>& ftpClient, const QSharedPointer<Logger>& logerptr)
        :Loader(file, ftpClient, logerptr)
    {}

    void run() override;
    ~Downloader() override {

    }
private slots:
    void handleFinish(int id, bool error);
};

#endif // LOADER_H
