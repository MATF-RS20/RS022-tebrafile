#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "messages.h"

#include <iostream>
#include <QTreeView>
#include <QHeaderView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    fileList = ui->treeWidget;
    initTreeWidget();
    currentPath.clear();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initTreeWidget()
{
    fileList->setEnabled(false);
    fileList->setRootIsDecorated(true);
    fileList->header()->setStretchLastSection(true);

    fileList->setColumnCount(5);
    fileList->setHeaderLabels(QStringList() << "Name"
                                    << "Size"
                                    << "Owner"
                                    << "Group"
                                    << "Last modified");
    headerView = fileList->header();
    headerView->setSectionsClickable(true);
    headerView->resizeSection(0, 180);

    restartTreeWidget();
    QObject::connect(headerView, SIGNAL( sectionClicked(int) ), this, SLOT( on_header_cliked(int) ) );
    QObject::connect(fileList, &QTreeWidget::itemDoubleClicked, this, &MainWindow::cdToFolder);
}

void MainWindow::restartTreeWidget()
{
    fileList->clear();
    isDir.clear();

    QTreeWidgetItem *widgetItem = new QTreeWidgetItem();
    widgetItem->setText(0, "..");
    fileList->addTopLevelItem(widgetItem);



    // ctrl+click for multi-select
    fileList->setSelectionMode(QAbstractItemView::ExtendedSelection);


    widgetItem->setDisabled(true);

}

void MainWindow::on_header_cliked(int logicalIndex)
{
    if(logicalIndex == 0) {
        headerView->setSortIndicatorShown(true);
        fileList ->takeTopLevelItem(0);
        fileList ->sortItems(logicalIndex, headerView->sortIndicatorOrder());

        QTreeWidgetItem *widgetItem = new QTreeWidgetItem();
        widgetItem->setText(0, "..");
        fileList->insertTopLevelItem(0, widgetItem);
    } else {
        headerView->setSortIndicatorShown(false);
    }
}


void MainWindow::on_connectButton_clicked()
{
    serverConn = new ServerConnection(this, QUrl(ui->serverNameField->text()));
    serverConn->connectToServer();
}



void MainWindow::on_disconnectButton_clicked()
{
    serverConn->~ServerConnection();
    currentPath.clear();
    restartTreeWidget();
}



void MainWindow::listFiles(const QString& fileName)
{
    QObject::connect(serverConn->getClient(), &QFtp::listInfo, this, &MainWindow::addToList);
    QObject::connect(serverConn->getClient(), &QFtp::done, this, &MainWindow::listDone);
    serverConn->getClient()->list(fileName);
}

void MainWindow::addToList(const QUrlInfo& file)
{
    QTreeWidgetItem *widgetItem = new QTreeWidgetItem();

    widgetItem->setText(0, file.name());
    widgetItem->setText(1, QString::number(file.size()));
    widgetItem->setText(2, file.owner());
    widgetItem->setText(3, file.group());
    widgetItem->setText(4, file.lastModified().toString("dd.MM.yyyy"));

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

            restartTreeWidget();

            serverConn->getClient()->cd(name);
            serverConn->getClient()->list();
        }
    }
    headerView->setSortIndicatorShown(false);
}

void MainWindow::leaveFolder()
{
      restartTreeWidget();
      currentPath = currentPath.left(currentPath.lastIndexOf('/'));
      if(currentPath.isEmpty()) {
          currentPath = "~";
          serverConn->getClient()->cd("~");
      } else {
          serverConn->getClient()->cd(currentPath);
      }
      serverConn->getClient()->list();
      headerView->setSortIndicatorShown(false);
}

void MainWindow::listDone(bool error)
{
    if (error) {
        std::cerr << "Error: " << qPrintable(serverConn->getClient()->errorString()) << std::endl;
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

    if (ui->uploadFileInput->text().trimmed().length() == 0)
        QMessageBox::critical(this, "Alert", "Files did not selected.");
    else if (!logged)
        QMessageBox::critical(this, "Alert", "You are not connected.");
    else {
        const auto listOfFiles = ui->uploadFileInput->text().split(";");
        foreach (const auto file, listOfFiles) {
            const auto namesParts = file.split("/");
            QFile readFile(file);
            readFile.open(QIODevice::ReadOnly);
            const QByteArray buffer = readFile.readAll();
            int putID = serverConn->getClient()->put(buffer, namesParts.last(), QFtp::Binary);
            fileList->setEnabled(false);
            QObject::connect(serverConn->getClient(), &QFtp::dataTransferProgress,
                             this, &MainWindow::progressBarSlot);
            QObject::connect(serverConn->getClient(), &QFtp::commandFinished,
                             this, &MainWindow::uploadFinishHandler);

        }
    }
}



void MainWindow::on_downloadButton_clicked()
{

    if (ui->downloadFileInput->text().trimmed().length() == 0)
        QMessageBox::critical(this, "Alert", "Files did not selected.");
    else
    {

        fileList->setEnabled(false);
        ui->downloadButton->setEnabled(false);
        const auto downloadList = ui->downloadFileInput->text().split(";");


        //QString fileName = fileList->currentItem()->text(0);

        QString downloadsFolder = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation);


        for(auto fileName : downloadList)
        {
            file = new QFile(downloadsFolder + "/" + fileName);

            if (!file->open(QIODevice::WriteOnly)) {
             QMessageBox::information(this, tr("FTP"),
                                      tr("Unable to save the file %1: %2.")
                                      .arg(fileName).arg(file->errorString()));
             delete file;
             return;
            }

            serverConn->getClient()->get(fileName, file);
            QObject::connect(serverConn->getClient(), &QFtp::dataTransferProgress,
                             this, &MainWindow::downloadProgressBarSlot);

        }

    }
}

void MainWindow::downloadProgressBarSlot(qint64 done, qint64 total)
{
    ui->downloadProgressBar->setValue(100*done/total);
    if(done == total){
        fileList->setEnabled(true);
        ui->downloadButton->setEnabled(true);
    }
}


void MainWindow::on_treeWidget_clicked()
{
    const auto filenames = fileList->selectedItems();
    QStringList filenamesQ;

    //ruzno ali radi
    // fix sa refactorisanjem i std::transform
    QString temp;
    for(auto filename : filenames)
    {
        temp = filename->text(0);
        filenamesQ.push_back(temp);
    }




    ui->downloadFileInput->setText(filenamesQ.join(';'));

}

void MainWindow::progressBarSlot(qint64 done, qint64 total)
{
    ui->uploadProgressBar->setValue(100*done/total);
    if(done == total)
        fileList->setEnabled(true);
}

void MainWindow::uploadFinishHandler(int id, bool error)
{
    if (error) {
        fileList->setEnabled(true);
        std::cout << serverConn->getClient()->errorString().toUtf8().data() << std::endl;

    }
}




