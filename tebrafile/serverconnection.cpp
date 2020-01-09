#include "serverconnection.h"


#include <QMessageBox>
#include <QDebug>

ServerConnection::ServerConnection(QObject* window, const QUrl& url, const unsigned port, const QSharedPointer<Logger>& logerPtr)
    :_hostURL(url), _port(port)
{
    if (url.isValid())
        _validURL = true;
    else
        Logger::showMessageBox("Alert", "URL is invalid.", QMessageBox::Critical);
    _client = QSharedPointer<QFtp>(new QFtp(window));
    _loger = logerPtr;
    this->_window = static_cast<QWidget*>(window);
}

void ServerConnection::connectToServer()
{
    _connectionId = _client->connectToHost(_hostURL.host(), static_cast<quint16>(_hostURL.port(_port)));
    QObject::connect(_client.data(), &QFtp::commandFinished, this, &ServerConnection::finishedHandler);
}

QSharedPointer<QFtp> ServerConnection::getClient() const
{
    return _client;
}

QSharedPointer<Logger> ServerConnection::getLogger() const
{
    return _loger;
}

bool ServerConnection::isLogged() const { return _logged; }
bool ServerConnection::isConnected() const { return _connected; }


void ServerConnection::showLoginDialog()
{
    if (_client->state() == QFtp::Connected) {
        InputDialog* diag = new InputDialog(_window, QString("username"), QString("password"));
        QObject::connect(diag, &InputDialog::credentialsCaptured, this, &ServerConnection::logIn);
        diag->exec();
    }
}



//Slots



void ServerConnection::finishedHandler(int id, bool error)
{
    if (error and _connectionId == id)
        _loger->consoleLog(_client->errorString());
    else if (!error and _connectionId == id){
        _loger->consoleLog("You are connected");
        _connected = true;
        showLoginDialog();
    }
}

void ServerConnection::logIn(InputDialog* diag)
{
    QStringList credentials = InputDialog::getStrings(diag);
    _loginId = _client->login(credentials.at(0), credentials.at(1));
    QObject::connect(_client.data(), &QFtp::commandFinished, this, &ServerConnection::loginHandler);
}

void ServerConnection::loginHandler(int id, bool error)
{
    if (_client->state() == QFtp::LoggedIn and _loginId == id) {
        _logged = true;
        _loger->consoleLog("You are loggedIn");
        emit connectionEstablished(_client);
    }
}
