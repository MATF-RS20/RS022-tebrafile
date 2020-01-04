#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QTreeView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    fileList = ui->treeWidget;
    fileList->setEnabled(false);
    fileList->setRootIsDecorated(true);
    fileList->header()->setStretchLastSection(true);

    fileList->setColumnCount(5);
    fileList->setHeaderLabels(QStringList() << "Name"
                                    << "Size"
                                    << "Owner"
                                    << "Group"
                                    << "Last modified");
    QObject::connect(fileList, &QTreeWidget::itemDoubleClicked, this, &MainWindow::cdToFolder);
    fileList->clear();
    isDir.clear();
    currentPath.clear();

    QTreeWidgetItem *widgetItem = new QTreeWidgetItem();
    widgetItem->setText(0, "..");
    widgetItem->setDisabled(true);
    fileList->addTopLevelItem(widgetItem);

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

    fileList->clear();
    isDir.clear();
    currentPath.clear();

    QTreeWidgetItem *widgetItem = new QTreeWidgetItem();
    widgetItem->setText(0, "..");
    fileList->addTopLevelItem(widgetItem);
    fileList->setEnabled(false);

    ui->loginMsg->setText("You are disconnected");
}

void MainWindow::showLoginDialog(int state)
{
    if (state == QFtp::Connected and ftpClient->error() == QFtp::NoError) {
        InputDialog* diag = new InputDialog(this,
                                            QString("username"),
                                            QString("password")
                                            );
        QObject::connect(diag, &InputDialog::credentialsCaptured, this, &MainWindow::login);
        diag->exec();
    } else if (state == QFtp::Unconnected and ftpClient->currentCommand() != QFtp::Close){
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
    currentPath = QString("~");
    if (state == QFtp::LoggedIn and ftpClient->currentCommand() == QFtp::Login) {
        listFiles(currentPath);
        ui->loginMsg->clear();
    }
}

void MainWindow::listFiles(const QString& fileName)
{
    QObject::connect(ftpClient, &QFtp::listInfo, this, &MainWindow::addToList);
    QObject::connect(ftpClient, &QFtp::done, this, &MainWindow::listDone);
    ftpClient->list(fileName);
}

void MainWindow::addToList(const QUrlInfo& file)
{
    QTreeWidgetItem *widgetItem = new QTreeWidgetItem();

    widgetItem->setText(0, file.name());
    widgetItem->setText(1, QString::number(file.size()));
    widgetItem->setText(2, file.owner());
    widgetItem->setText(3, file.group());
    widgetItem->setText(4, file.lastModified().toString("dd/mm/yyyy"));

    QIcon* folderIcon = new QIcon("../icons/directory.png");
    QIcon* fileIcon = new QIcon("../icons/file.png");
    QIcon* icon(file.isDir() ? folderIcon : fileIcon);
    widgetItem->setIcon(0, *icon);

    isDir.insert(file.name(), file.isDir());

    fileList->addTopLevelItem(widgetItem);

    // ako je item prvi postavi ga za trenutno selektovani
    if (!fileList->currentItem()) {
        fileList->setCurrentItem(fileList->topLevelItem(1));
        fileList->setEnabled(true);
    }
}

void MainWindow::cdToFolder(QTreeWidgetItem *widgetItem, int column)
{
    // ako je korisnik izabrao da ide nazad
    if(widgetItem == fileList->topLevelItem(0)) {
        leaveFolder();
    } else {
        QString name = widgetItem->text(0);
        if(isDir.value(name)) {
            currentPath += '/';
            currentPath += name;

            std::cout << currentPath.toStdString() << std::endl;

            fileList->clear();
            isDir.clear();

            QTreeWidgetItem *widgetItem = new QTreeWidgetItem();
            widgetItem->setText(0, "..");
            fileList->addTopLevelItem(widgetItem);

            ftpClient->cd(name);
            ftpClient->list();
        }
    }
}

void MainWindow::leaveFolder()
{
      fileList->clear();
      isDir.clear();

      QTreeWidgetItem *widgetItem = new QTreeWidgetItem();
      widgetItem->setText(0, "..");
      fileList->addTopLevelItem(widgetItem);

      currentPath = currentPath.left(currentPath.lastIndexOf('/'));
      std::cout << currentPath.toStdString() << std::endl;
      if(currentPath.isEmpty()) {
          currentPath = "~";
          ftpClient->cd("~");
          fileList->topLevelItem(0)->setDisabled(true);
      } else {
          ftpClient->cd(currentPath);
      }
      ftpClient->list();

}

void MainWindow::listDone(bool error)
{
    if (error) {
        std::cerr << "Error: " << qPrintable(ftpClient->errorString()) << std::endl;
    }
}

void MainWindow::uploadProgressBarSlot(qint64 done, qint64 total)
{
    ui->uploadProgressBar->setValue(100*done/total);
    if(done == total){
        fileList->setEnabled(true);
        ui->uploadButton->setEnabled(true);
    }
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
    fileList->setEnabled(false);
    ui->uploadButton->setEnabled(false);

    if (ui->uploadFileInput->text().trimmed().length() == 0)
        QMessageBox::critical(this, "Alert", "Files did not selected.");
    else {
        const auto listOfFiles = ui->uploadFileInput->text().split(";");
        foreach (const auto file, listOfFiles) {
            const auto namesParts = file.split("/");
            QFile readFile(file);
            readFile.open(QIODevice::ReadOnly);
            const QByteArray buffer = readFile.readAll();
            ftpClient->put(buffer, namesParts.last(), QFtp::Binary);
            QObject::connect(ftpClient, &QFtp::dataTransferProgress,
                             this, &MainWindow::uploadProgressBarSlot);
        }
    }
}

void MainWindow::on_downloadButton_clicked()
{
    fileList->setEnabled(false);
    ui->downloadButton->setEnabled(false);

    QString fileName = fileList->currentItem()->text(0);
    QString downloadsFolder = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation);
    qDebug()<< downloadsFolder;

    file = new QFile(downloadsFolder + "/" + fileName);

    if (!file->open(QIODevice::WriteOnly)) {
     QMessageBox::information(this, tr("FTP"),
                              tr("Unable to save the file %1: %2.")
                              .arg(fileName).arg(file->errorString()));
     delete file;
     return;
    }

    ftpClient->get(fileName, file);
    QObject::connect(ftpClient, &QFtp::dataTransferProgress,
                     this, &MainWindow::downloadProgressBarSlot);

}

void MainWindow::downloadProgressBarSlot(qint64 done, qint64 total)
{
    ui->downloadProgressBar->setValue(100*done/total);
    if(done == total){
        fileList->setEnabled(true);
        ui->downloadButton->setEnabled(true);
    }
}




