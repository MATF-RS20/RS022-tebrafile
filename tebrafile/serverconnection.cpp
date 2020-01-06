#include "serverconnection.h"


#include <QMessageBox>
#include <QDebug>

ServerConnection::ServerConnection(QObject* window, const QUrl& url)
    :hostURL(url)
{
    if (url.isValid())
        validURL = true;
    else
        showMessageBox("Alert", "URL is invalid.", QMessageBox::Critical);
    client = QSharedPointer<QFtp>(new QFtp(window));
    this->window = static_cast<QWidget*>(window);
}

void ServerConnection::connectToServer()
{
    connectionId = client->connectToHost(hostURL.host(), static_cast<quint16>(hostURL.port(21)));
    QObject::connect(client.get(), &QFtp::commandFinished, this, &ServerConnection::finishedHandler);
}

QFtp* ServerConnection::getClient() const
{
    return client.get();
}


void ServerConnection::showLoginDialog()
{
    if (client->state() == QFtp::Connected) {
        InputDialog* diag = new InputDialog(window, QString("username"), QString("password"));
        diag->exec();
    }
}



//Slots

void ServerConnection::finishedHandler(int id, bool error)
{
    if (error and connectionId == id)
        qDebug() << client->errorString();
    else
        showLoginDialog();
}

void ServerConnection::logIn(InputDialog* diag)
{
    QStringList credentials = InputDialog::getStrings(diag);
    loginId = client->login(credentials.at(0), credentials.at(1));
    QObject::connect(client.get(), &QFtp::commandFinished, this, &ServerConnection::loginHandler);
}

void ServerConnection::loginHandler(int id, bool error)
{
    if (client->state() == QFtp::LoggedIn and loginId == id) {

    }
}
