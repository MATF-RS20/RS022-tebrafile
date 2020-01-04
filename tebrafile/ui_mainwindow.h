/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QLabel *label2;
    QHBoxLayout *hl3;
    QLineEdit *serverNameField;
    QPushButton *connectButton;
    QPushButton *disconnectButton;
    QLabel *label;
    QLineEdit *uploadFileInput;
    QLabel *loginMsg;
    QHBoxLayout *hl1;
    QPushButton *openButton;
    QPushButton *uploadButton;
    QProgressBar *uploadProgressBar;
    QFrame *line;
    QHBoxLayout *hl2;
    QLineEdit *donwloadPath;
    QPushButton *setFolderButton;
    QTreeWidget *treeWidget;
    QLabel *label_2;
    QLineEdit *downloadFileInput;
    QProgressBar *downloadProgressBar;
    QPushButton *downloadButton;
    QSpacerItem *verticalSpacer;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label2 = new QLabel(centralwidget);
        label2->setObjectName(QStringLiteral("label2"));

        verticalLayout->addWidget(label2);

        hl3 = new QHBoxLayout();
        hl3->setObjectName(QStringLiteral("hl3"));
        hl3->setContentsMargins(-1, 1, -1, -1);
        serverNameField = new QLineEdit(centralwidget);
        serverNameField->setObjectName(QStringLiteral("serverNameField"));
        serverNameField->setMinimumSize(QSize(400, 0));

        hl3->addWidget(serverNameField);

        connectButton = new QPushButton(centralwidget);
        connectButton->setObjectName(QStringLiteral("connectButton"));

        hl3->addWidget(connectButton);

        disconnectButton = new QPushButton(centralwidget);
        disconnectButton->setObjectName(QStringLiteral("disconnectButton"));

        hl3->addWidget(disconnectButton);


        verticalLayout->addLayout(hl3);

        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        uploadFileInput = new QLineEdit(centralwidget);
        uploadFileInput->setObjectName(QStringLiteral("uploadFileInput"));

        verticalLayout->addWidget(uploadFileInput);

        loginMsg = new QLabel(centralwidget);
        loginMsg->setObjectName(QStringLiteral("loginMsg"));

        verticalLayout->addWidget(loginMsg);

        hl1 = new QHBoxLayout();
        hl1->setObjectName(QStringLiteral("hl1"));
        openButton = new QPushButton(centralwidget);
        openButton->setObjectName(QStringLiteral("openButton"));

        hl1->addWidget(openButton);

        uploadButton = new QPushButton(centralwidget);
        uploadButton->setObjectName(QStringLiteral("uploadButton"));

        hl1->addWidget(uploadButton);


        verticalLayout->addLayout(hl1);

        uploadProgressBar = new QProgressBar(centralwidget);
        uploadProgressBar->setObjectName(QStringLiteral("uploadProgressBar"));
        uploadProgressBar->setValue(0);

        verticalLayout->addWidget(uploadProgressBar);

        line = new QFrame(centralwidget);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        hl2 = new QHBoxLayout();
        hl2->setObjectName(QStringLiteral("hl2"));
        donwloadPath = new QLineEdit(centralwidget);
        donwloadPath->setObjectName(QStringLiteral("donwloadPath"));

        hl2->addWidget(donwloadPath);

        setFolderButton = new QPushButton(centralwidget);
        setFolderButton->setObjectName(QStringLiteral("setFolderButton"));

        hl2->addWidget(setFolderButton);


        verticalLayout->addLayout(hl2);

        treeWidget = new QTreeWidget(centralwidget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));

        verticalLayout->addWidget(treeWidget);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout->addWidget(label_2);

        downloadFileInput = new QLineEdit(centralwidget);
        downloadFileInput->setObjectName(QStringLiteral("downloadFileInput"));

        verticalLayout->addWidget(downloadFileInput);

        downloadProgressBar = new QProgressBar(centralwidget);
        downloadProgressBar->setObjectName(QStringLiteral("downloadProgressBar"));
        downloadProgressBar->setValue(0);

        verticalLayout->addWidget(downloadProgressBar);

        downloadButton = new QPushButton(centralwidget);
        downloadButton->setObjectName(QStringLiteral("downloadButton"));

        verticalLayout->addWidget(downloadButton);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout->addItem(verticalSpacer);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        label2->setText(QApplication::translate("MainWindow", "ServerName:", Q_NULLPTR));
        connectButton->setText(QApplication::translate("MainWindow", "Connect", Q_NULLPTR));
        disconnectButton->setText(QApplication::translate("MainWindow", "Disconnect", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "Upload file(s):", Q_NULLPTR));
        uploadFileInput->setText(QString());
        loginMsg->setText(QString());
        openButton->setText(QApplication::translate("MainWindow", "Open", Q_NULLPTR));
        uploadButton->setText(QApplication::translate("MainWindow", "Upload", Q_NULLPTR));
        setFolderButton->setText(QApplication::translate("MainWindow", "Set Folder", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "Download file(s):", Q_NULLPTR));
        downloadButton->setText(QApplication::translate("MainWindow", "Download", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
