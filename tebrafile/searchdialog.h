#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H

#include "listFiles.h"
#include "mainwindow.h"

#include <QDialog>

namespace Ui {
class SearchDialog;
}

class SearchDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SearchDialog(MainWindow* mainWindow, QWidget *parent = nullptr);
    ~SearchDialog();

private slots:
    void on_startButton_clicked();
    void searchDone();
    void on_searchWidget_clicked();
    void on_stopButton_clicked();


private:
    Ui::SearchDialog *ui;
    MainWindow* _mainWindow;

    ListFiles* _searchList = nullptr;
    Search* _s = nullptr;
};

#endif // SEARCHDIALOG_H
