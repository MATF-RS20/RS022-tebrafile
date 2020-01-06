#ifndef SERVERCONNECTION_H
#define SERVERCONNECTION_H

#include "messages.h"
#include "inputDialog.h"

#include <QFtp>
#include <QSharedPointer>
#include <QUrl>
#include <QDebug>

class ServerConnection : public QObject
{
    Q_OBJECT
public:
    ServerConnection(QObject* parent, const QUrl& url);
    ~ServerConnection() {
        client->disconnect();
        client->close();
        qDebug() << "Server disconnection";
    }
    void connectToServer();
    QFtp* getClient() const;

private slots:
    void finishedHandler(int id, bool error);
    void loginHandler(int id, bool error);
    void logIn(InputDialog* diag);

private:
    void showLoginDialog();


    QSharedPointer<QFtp> client;
    int connectionId;
    int loginId;
    QUrl hostURL;
    bool validURL = true;
    QWidget* window;



};

#endif // SERVERCONNECTION_H
