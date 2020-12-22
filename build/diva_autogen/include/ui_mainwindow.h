/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionLive_Streaming;
    QAction *actionGet_Log;
    QAction *actionStreaming_End;
    QAction *actionInitializing;
    QAction *actionIntializing;
    QAction *actionInitializing_2;
    QAction *actionStroing_To_DB;
    QWidget *centralwidget;
    QLabel *label_5;
    QLabel *label_7;
    QSlider *horizontalSlider;
    QPushButton *pushButton;
    QListWidget *label_3;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout_2;
    QMenuBar *menubar;
    QMenu *menuStreaming;
    QMenu *menuPlayback;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1600, 900);
        MainWindow->setStyleSheet(QString::fromUtf8("background : qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(201, 255, 224, 152), stop:0.293532 rgba(190, 255, 254, 155), stop:0.587065 rgba(190, 223, 255, 155), stop:0.840796 rgba(190, 203, 255, 155), stop:0.995025 rgba(193, 190, 255, 155))"));
        actionLive_Streaming = new QAction(MainWindow);
        actionLive_Streaming->setObjectName(QString::fromUtf8("actionLive_Streaming"));
        actionGet_Log = new QAction(MainWindow);
        actionGet_Log->setObjectName(QString::fromUtf8("actionGet_Log"));
        actionStreaming_End = new QAction(MainWindow);
        actionStreaming_End->setObjectName(QString::fromUtf8("actionStreaming_End"));
        actionInitializing = new QAction(MainWindow);
        actionInitializing->setObjectName(QString::fromUtf8("actionInitializing"));
        actionIntializing = new QAction(MainWindow);
        actionIntializing->setObjectName(QString::fromUtf8("actionIntializing"));
        actionInitializing_2 = new QAction(MainWindow);
        actionInitializing_2->setObjectName(QString::fromUtf8("actionInitializing_2"));
        actionStroing_To_DB = new QAction(MainWindow);
        actionStroing_To_DB->setObjectName(QString::fromUtf8("actionStroing_To_DB"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(15, 349, 271, 241));
        label_5->setStyleSheet(QString::fromUtf8("background-color: rgb(238, 238, 236);"));
        label_5->setAlignment(Qt::AlignCenter);
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(1160, 810, 421, 51));
        label_7->setStyleSheet(QString::fromUtf8("background-color: rgb(238, 238, 236);"));
        horizontalSlider = new QSlider(centralwidget);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(300, 810, 851, 51));
        horizontalSlider->setStyleSheet(QString::fromUtf8("color: rgb(238, 238, 236);\n"
"background-color: rgba(238, 238, 236, 180);"));
        horizontalSlider->setOrientation(Qt::Horizontal);
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(100, 830, 89, 25));
        label_3 = new QListWidget(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(15, 600, 271, 221));
        label_3->setStyleSheet(QString::fromUtf8("background-color: rgba(238, 238, 236, 180);"));
        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 140, 271, 201));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        gridLayoutWidget_2 = new QWidget(centralwidget);
        gridLayoutWidget_2->setObjectName(QString::fromUtf8("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(1210, 530, 361, 261));
        gridLayout_2 = new QGridLayout(gridLayoutWidget_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        MainWindow->setCentralWidget(centralwidget);
        label_3->raise();
        label_5->raise();
        label_7->raise();
        horizontalSlider->raise();
        pushButton->raise();
        gridLayoutWidget->raise();
        gridLayoutWidget_2->raise();
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1600, 22));
        menubar->setStyleSheet(QString::fromUtf8("background-color: rgba(238, 238, 236, 200);\n"
"color: rgba(103, 73, 203, 230);"));
        menuStreaming = new QMenu(menubar);
        menuStreaming->setObjectName(QString::fromUtf8("menuStreaming"));
        menuStreaming->setStyleSheet(QString::fromUtf8(""));
        menuPlayback = new QMenu(menubar);
        menuPlayback->setObjectName(QString::fromUtf8("menuPlayback"));
        MainWindow->setMenuBar(menubar);

        menubar->addAction(menuStreaming->menuAction());
        menubar->addAction(menuPlayback->menuAction());
        menuStreaming->addAction(actionInitializing);
        menuStreaming->addAction(actionLive_Streaming);
        menuStreaming->addAction(actionStreaming_End);
        menuStreaming->addAction(actionStroing_To_DB);
        menuPlayback->addAction(actionInitializing_2);
        menuPlayback->addAction(actionGet_Log);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        actionLive_Streaming->setText(QApplication::translate("MainWindow", "Live Streaming", nullptr));
        actionGet_Log->setText(QApplication::translate("MainWindow", "Get Log", nullptr));
        actionStreaming_End->setText(QApplication::translate("MainWindow", "Streaming End", nullptr));
        actionInitializing->setText(QApplication::translate("MainWindow", "Initializing", nullptr));
        actionIntializing->setText(QApplication::translate("MainWindow", "Intializing", nullptr));
        actionInitializing_2->setText(QApplication::translate("MainWindow", "Initializing", nullptr));
        actionStroing_To_DB->setText(QApplication::translate("MainWindow", "Stroing To DB", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "CAN Bus Data", nullptr));
        label_7->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        pushButton->setText(QApplication::translate("MainWindow", "Start Play", nullptr));
        menuStreaming->setTitle(QApplication::translate("MainWindow", "Streaming", nullptr));
        menuPlayback->setTitle(QApplication::translate("MainWindow", "Playback", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
