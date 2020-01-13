#include "listFiles.h"
#include <iostream>


ListFiles::ListFiles(QTreeWidget* treeWidget)
    :_treeWidget(QSharedPointer<QTreeWidget>(treeWidget))
{
    _currentPath.clear();

    _treeWidget->setEnabled(false);
    _treeWidget->setRootIsDecorated(true);
    _treeWidget->header()->setStretchLastSection(true);
    _treeWidget->setColumnCount(5);
    _treeWidget->setHeaderLabels(QStringList() << "Name"
                                    << "Size"
                                    << "Owner"
                                    << "Group"
                                    << "Last modified");

    _headerView = QSharedPointer<QHeaderView>(_treeWidget->header());
    _headerView->setSectionsClickable(true);
    _headerView->resizeSection(0, 180);

    ListFiles::restartTreeWidget();
}

void ListFiles::setServerConn(const QSharedPointer<QFtp>& serverConn){
    _serverConn = serverConn;
}

void ListFiles::listFiles(const QString& fileName)
{
    QObject::connect(_treeWidget.data(), &QTreeWidget::itemDoubleClicked, this, &ListFiles::cdToFolder);
    QObject::connect(_headerView.data(), &QHeaderView::sectionClicked, this, &ListFiles::on_header_clicked);
    QObject::connect(_serverConn.data(), &QFtp::listInfo, this, &ListFiles::addToList);
    QObject::connect(_serverConn.data(), &QFtp::done, this, &ListFiles::listDone);
    _serverConn->list(fileName);
}

void ListFiles::addToList(const QUrlInfo& file)
{
    QTreeWidgetItem* widgetItem = new QTreeWidgetItem();

    widgetItem->setText(0, file.name());
    if(file.isDir())
        widgetItem->setText(1, QString("\\"));
    else
        widgetItem->setText(1, QString::number(file.size()));
    widgetItem->setText(2, file.owner());
    widgetItem->setText(3, file.group());
    widgetItem->setText(4, file.lastModified().toString("dd.MM.yyyy"));

    QIcon* folderIcon = new QIcon("../icons/directory.png");
    QIcon* fileIcon = new QIcon("../icons/file.png");
    QIcon* icon(file.isDir() ? folderIcon : fileIcon);
    widgetItem->setIcon(0, *icon);

    _isDir.insert(file.name(), file.isDir());

    _treeWidget->addTopLevelItem(widgetItem);

    // ako je item prvi postavi ga za trenutno selektovani
    if (!_treeWidget->currentItem()) {
        _treeWidget->setCurrentItem(_treeWidget->topLevelItem(1));
        _treeWidget->setEnabled(true);
    }
}
void ListFiles::cdToFolder(QTreeWidgetItem *widgetItem, int column)
{
    // ako je korisnik izabrao da ide nazad
    if(widgetItem == _treeWidget->topLevelItem(0) && !(_treeWidget->topLevelItem(0)->isDisabled())) {
        leaveFolder();
    } else {
        QString name = widgetItem->text(0);
        if(_isDir.value(name)) {
            _currentPath += '/';
            _currentPath += name;

            ListFiles::restartTreeWidget();
            _treeWidget->topLevelItem(0)->setDisabled(false);

            _serverConn->cd(name);
            _serverConn->list();
        }
    }
    _headerView->setSortIndicatorShown(false);
}
void ListFiles::leaveFolder()
{
    ListFiles::restartTreeWidget();
    _currentPath = _currentPath.left(_currentPath.lastIndexOf('/'));
    if(_currentPath.isEmpty()) {
        _currentPath = "~";
        _serverConn->cd("~");
    } else {
        _serverConn->cd(_currentPath);
    }
    ListFiles::restartTreeWidget();

    if (_currentPath == "~")
        _treeWidget->topLevelItem(0)->setDisabled(true);
    else
        _treeWidget->topLevelItem(0)->setDisabled(false);

    _serverConn->list();
    _headerView->setSortIndicatorShown(false);
}

void ListFiles::clearPath() { _currentPath.clear(); }

void ListFiles::restartTreeWidget()
{
    _treeWidget->clear();
    _isDir.clear();

    QTreeWidgetItem* widgetItem = new QTreeWidgetItem();
    widgetItem->setText(0, "..");
    _treeWidget.data()->addTopLevelItem(widgetItem);
    _treeWidget->topLevelItem(0)->setDisabled(true);

    // ctrl+click for multi-select
    _treeWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);

    widgetItem->setDisabled(true);
}

void ListFiles::listDone(bool error)
{
    if (error) {
        std::cerr << "Error: " << qPrintable(_serverConn->errorString()) << std::endl;
    }
}

void ListFiles::on_header_clicked(int logicalIndex)
{
    if(logicalIndex == 0) {
        _headerView->setSortIndicatorShown(true);
        _treeWidget->takeTopLevelItem(0);
        _treeWidget->sortItems(logicalIndex, _headerView->sortIndicatorOrder());

        QTreeWidgetItem* widgetItem = new QTreeWidgetItem();
        widgetItem->setText(0, "..");
        _treeWidget->insertTopLevelItem(0, widgetItem);
        if (_currentPath == "~")
            _treeWidget->topLevelItem(0)->setDisabled(true);
        else
            _treeWidget->topLevelItem(0)->setDisabled(false);
    } else {
        _headerView->setSortIndicatorShown(false);
    }
}

QSharedPointer<QTreeWidget> ListFiles::getTreeWidget() const
{
    return _treeWidget;
}

QSharedPointer<QHeaderView> ListFiles::getHeaderView() const{
    return _headerView;
}
