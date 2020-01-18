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
#include <QtWidgets/QTextEdit>
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
    QHBoxLayout *hl1;
    QPushButton *openButton;
    QPushButton *uploadButton;
    QProgressBar *uploadProgressBar;
    QFrame *line;
    QHBoxLayout *hl2;
    QLineEdit *donwloadPath;
    QPushButton *setFolderButton;
    QHBoxLayout *hl4;
    QTreeWidget *treeWidget;
    QVBoxLayout *vl;
    QLabel *label_3;
    QTextEdit *textEdit;
    QLabel *label_2;
    QLineEdit *downloadFileInput;
    QProgressBar *downloadProgressBar;
    QPushButton *downloadButton;
    QPushButton *downloadCancel;
    QSpacerItem *verticalSpacer;
    QFrame *line_2;
    QVBoxLayout *vl2;
    QHBoxLayout *hl7;
    QLabel *label_4;
    QLineEdit *searchFile;
    QHBoxLayout *hl5;
    QLabel *label_5;
    QLineEdit *searchPath;
    QHBoxLayout *hl6;
    QPushButton *startButton;
    QPushButton *stopButton;
    QTreeWidget *searchWidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(854, 791);
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

        hl4 = new QHBoxLayout();
        hl4->setObjectName(QStringLiteral("hl4"));
        treeWidget = new QTreeWidget(centralwidget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        treeWidget->setMaximumSize(QSize(16777215, 16777215));

        hl4->addWidget(treeWidget);

        vl = new QVBoxLayout();
        vl->setObjectName(QStringLiteral("vl"));
        vl->setContentsMargins(10, -1, -1, -1);
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        vl->addWidget(label_3);

        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));

        vl->addWidget(textEdit);


        hl4->addLayout(vl);


        verticalLayout->addLayout(hl4);

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

        downloadCancel = new QPushButton(centralwidget);
        downloadCancel->setObjectName(QStringLiteral("downloadCancel"));

        verticalLayout->addWidget(downloadCancel);

        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout->addItem(verticalSpacer);

        line_2 = new QFrame(centralwidget);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_2);

        vl2 = new QVBoxLayout();
        vl2->setObjectName(QStringLiteral("vl2"));
        vl2->setSizeConstraint(QLayout::SetMaximumSize);
        vl2->setContentsMargins(5, 5, 5, 5);
        hl7 = new QHBoxLayout();
        hl7->setObjectName(QStringLiteral("hl7"));
        hl7->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        QFont font;
        font.setFamily(QStringLiteral("Ubuntu"));
        font.setPointSize(11);
        font.setBold(false);
        font.setWeight(50);
        label_4->setFont(font);

        hl7->addWidget(label_4);

        searchFile = new QLineEdit(centralwidget);
        searchFile->setObjectName(QStringLiteral("searchFile"));

        hl7->addWidget(searchFile);


        vl2->addLayout(hl7);

        hl5 = new QHBoxLayout();
        hl5->setObjectName(QStringLiteral("hl5"));
        hl5->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        QFont font1;
        font1.setPointSize(11);
        label_5->setFont(font1);

        hl5->addWidget(label_5);

        searchPath = new QLineEdit(centralwidget);
        searchPath->setObjectName(QStringLiteral("searchPath"));

        hl5->addWidget(searchPath);


        vl2->addLayout(hl5);

        hl6 = new QHBoxLayout();
        hl6->setObjectName(QStringLiteral("hl6"));
        hl6->setContentsMargins(0, 0, -1, -1);
        startButton = new QPushButton(centralwidget);
        startButton->setObjectName(QStringLiteral("startButton"));

        hl6->addWidget(startButton);

        stopButton = new QPushButton(centralwidget);
        stopButton->setObjectName(QStringLiteral("stopButton"));

        hl6->addWidget(stopButton);


        vl2->addLayout(hl6);

        searchWidget = new QTreeWidget(centralwidget);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem();
        __qtreewidgetitem1->setText(0, QStringLiteral("1"));
        searchWidget->setHeaderItem(__qtreewidgetitem1);
        searchWidget->setObjectName(QStringLiteral("searchWidget"));

        vl2->addWidget(searchWidget);


        verticalLayout->addLayout(vl2);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 854, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "tebraFile", Q_NULLPTR));
        label2->setText(QApplication::translate("MainWindow", "ServerName:", Q_NULLPTR));
        connectButton->setText(QApplication::translate("MainWindow", "Connect", Q_NULLPTR));
        disconnectButton->setText(QApplication::translate("MainWindow", "Disconnect", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "Upload file(s):", Q_NULLPTR));
        uploadFileInput->setText(QString());
        openButton->setText(QApplication::translate("MainWindow", "Open", Q_NULLPTR));
        uploadButton->setText(QApplication::translate("MainWindow", "Upload", Q_NULLPTR));
        setFolderButton->setText(QApplication::translate("MainWindow", "Set Folder", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "Status:", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "Download file(s):", Q_NULLPTR));
        downloadButton->setText(QApplication::translate("MainWindow", "Download", Q_NULLPTR));
        downloadCancel->setText(QApplication::translate("MainWindow", "Cancel", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "File name or regular expression:", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", "Search in:", Q_NULLPTR));
        startButton->setText(QApplication::translate("MainWindow", "Start", Q_NULLPTR));
        stopButton->setText(QApplication::translate("MainWindow", "Stop", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
