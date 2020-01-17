#ifndef SERVERCONNECTION_H
#define SERVERCONNECTION_H

#include "logger.h"
#include "inputDialog.h"

#include <QFtp>
#include <QSharedPointer>
#include <QUrl>
#include <QDebug>

class ServerConnection : public QObject
{
    Q_OBJECT
public:
    ServerConnection(QObject* parent, const QUrl& url, const QSharedPointer<Logger>& logerPtr);
    ~ServerConnection() {
        _client->disconnect();
        _client->close();
        _loger->consoleLog("You are disconnected from " + _hostURL.host());
    }
    void connectToServer();
    QSharedPointer<QFtp> getClient() const;
    QSharedPointer<Logger> getLogger() const;
    QSharedPointer<InputDialog> getDiag() const;

    bool isLogged() const;
    bool isConnected() const;

private slots:
    void finishedHandler(int id, bool error);
    void loginHandler(int id, bool error);
    void logIn(InputDialog* diag);


signals:
    void connectionEstablished(QSharedPointer<QFtp> client);

private:
    void showLoginDialog();

    QSharedPointer<QFtp> _client;

    int _connectionId;
    int _loginId;

    QUrl _hostURL;

    bool _validURL = false;
    bool _connected = false;
    bool _logged = false;

    QWidget* _window;

    QSharedPointer<Logger> _loger;
    QSharedPointer<InputDialog> _diag;
};

#endif // SERVERCONNECTION_H
