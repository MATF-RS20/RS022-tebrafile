#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->treeWidget->setColumnCount(5);
    ui->treeWidget->setHeaderLabels(QStringList() << "Name"
                                    << "Size"
                                    << "Owner"
                                    << "Group"
                                    << "Last modified");

    manager = new QNetworkAccessManager(this);
}


void MainWindow::ftpDone(bool error)
{
    if (error) {
        std::cerr << "Error: " << qPrintable(ftpClient->errorString()) << std::endl;
        ui->loginMsg->setText(ftpClient->errorString());
        ui->loginMsg->setStyleSheet("QLabel {color : red}");
        ftpClient->disconnect();
    }
}



MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::addToList(const QUrlInfo& file)
{
    QString name = currentFile + file.name();
    qDebug() << name;

    if(!file.isDir()) {
        fileList.insert(name, file);
    }else{
        const QString& tmp = currentFile;
        currentFile = name + "/";
        fileList.insert(currentFile, file);
        ftpClient->list(currentFile);
        currentFile = tmp;
    }
}

void MainWindow::on_connectButton_clicked()
{

    ftpAdrress = ui->serverNameField->text();
    connectToServer();
}

void MainWindow::login(InputDialog* diag)
{
    QStringList credentials = InputDialog::getStrings(diag);
    username = credentials.at(0);
    password = credentials.at(1);
    ftpClient->login(username, password);
    QObject::connect(ftpClient, &QFtp::stateChanged, this, &MainWindow::afterLogin);
}

void MainWindow::connectToServer()
{
        ftpClient = new QFtp(this);
        url = QUrl(ftpAdrress);
        if (url.isValid()) {
            ftpClient->connectToHost(url.host(), url.port(21));
            QObject::connect(ftpClient, &QFtp::done, this, &MainWindow::ftpDone);
        } else
            qDebug() << "greska ";

       QObject::connect(ftpClient, &QFtp::stateChanged, this, &MainWindow::showLoginDialog);
}

void MainWindow::on_disconnectButton_clicked()
{
    ftpClient->close();
    ftpClient->abort();
    ui->loginMsg->setText("You are disconnected");
}

void MainWindow::showLoginDialog(int state)
{
    if (state == QFtp::Connected and ftpClient->error() == QFtp::NoError) {
        InputDialog* diag = new InputDialog(this,
                                            QString("username"),
                                            QString("password"));
        QObject::connect(diag, &InputDialog::credentialsCaptured, this, &MainWindow::login);
        diag->exec();
    } else if (state == QFtp::Unconnected and ftpClient->currentCommand() != QFtp::Close){
        std::cerr << "ELSE ERROR: " << ftpClient->error() << std::endl;
        QMessageBox errBox;
        errBox.setWindowTitle("Connection error");
        errBox.setText(ftpClient->errorString());
        errBox.setIcon(QMessageBox::Critical);
        errBox.exec();
        ftpClient->close();
        ftpClient->disconnect();
    }

}

void MainWindow::afterLogin(int state)
{
    currentFile = QString("./");
    if (state == QFtp::LoggedIn and ftpClient->currentCommand() == QFtp::Login) {
        listFiles(currentFile);
        ui->loginMsg->clear();
    }
}

void MainWindow::listFiles(const QString& fileName)
{
    QObject::connect(ftpClient, &QFtp::listInfo, this, &MainWindow::addToList);
    QObject::connect(ftpClient, &QFtp::done, this, &MainWindow::listDone);
    ftpClient->list(fileName);
}

void MainWindow::listDone(bool error)
{
    if (error) {
        std::cerr << "Error: " << qPrintable(ftpClient->errorString()) << std::endl;
    }
    fileSystem(fileList);
}

void MainWindow::fileSystem(QHash<QString, QUrlInfo> files)
{
    QTreeWidgetItem *topLevelItem = nullptr;
    QHash<QString, QUrlInfo>::const_iterator iter = files.constBegin();

    while (iter != files.constEnd()) {
        QString fileName = iter.key();
        QList<QString> splitFileName;
        splitFileName.append(fileName.split("/"));

        if(ui->treeWidget->findItems(splitFileName[0], Qt::MatchFixedString).isEmpty())
        {
            topLevelItem = new QTreeWidgetItem();
            topLevelItem->setText(0, splitFileName[0]);
            ui->treeWidget->addTopLevelItem(topLevelItem);
        }

        QTreeWidgetItem *parentItem = topLevelItem;
        for(int i=1; i<splitFileName.size() - 1; ++i)
        {
            bool exists = false;
            for(int j=0; j< parentItem->childCount(); ++j){
                if(splitFileName[i] == parentItem->child(j)->text(0)){
                    exists = true;
                    parentItem = parentItem->child(j);
                    break;
                }
            }
            if(!exists)
            {
                parentItem = new QTreeWidgetItem(parentItem);
                parentItem->setText(0, splitFileName[i]);
            }
        }

        if(splitFileName.last() != ""){
            QTreeWidgetItem *childItem = new QTreeWidgetItem(parentItem);
            childItem->setText(0, splitFileName.last());
        }

        iter++;
    }
}
