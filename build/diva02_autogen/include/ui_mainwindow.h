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
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include <glwidget.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionLive_Streaming;
    QAction *actionGet_Log;
    QAction *actionStreaming_End;
    QWidget *centralwidget;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *gps_label;
    glwidget *imu_label;
    QLabel *label_7;
    QSlider *horizontalSlider;
    QLabel *cam_label;
    QLabel *label;
    QLabel *test_label;
    QStatusBar *statusbar;
    QMenuBar *menubar;
    QMenu *menuStreaming;
    QMenu *menuPlayback;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1280, 875);
        MainWindow->setStyleSheet(QString::fromUtf8("background : qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(201, 255, 224, 152), stop:0.293532 rgba(190, 255, 254, 155), stop:0.587065 rgba(190, 223, 255, 155), stop:0.840796 rgba(190, 203, 255, 155), stop:0.995025 rgba(193, 190, 255, 155))"));
        actionLive_Streaming = new QAction(MainWindow);
        actionLive_Streaming->setObjectName(QString::fromUtf8("actionLive_Streaming"));
        actionGet_Log = new QAction(MainWindow);
        actionGet_Log->setObjectName(QString::fromUtf8("actionGet_Log"));
        actionStreaming_End = new QAction(MainWindow);
        actionStreaming_End->setObjectName(QString::fromUtf8("actionStreaming_End"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 20, 170, 180));
        label_3->setStyleSheet(QString::fromUtf8("background-color: rgb(238, 238, 236);"));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(20, 210, 170, 180));
        label_4->setStyleSheet(QString::fromUtf8("background-color: rgb(238, 238, 236);"));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(20, 400, 170, 180));
        label_5->setStyleSheet(QString::fromUtf8("background-color: rgb(238, 238, 236);"));
        gps_label = new QLabel(centralwidget);
        gps_label->setObjectName(QString::fromUtf8("gps_label"));
        gps_label->setGeometry(QRect(850, 20, 411, 41));
        gps_label->setStyleSheet(QString::fromUtf8("background-color: rgba(238, 238, 236, 180);"));
        gps_label->setAlignment(Qt::AlignCenter);
        imu_label = new glwidget(centralwidget);
        imu_label->setObjectName(QString::fromUtf8("imu_label"));
        imu_label->setGeometry(QRect(850, 430, 410, 240));
        imu_label->setStyleSheet(QString::fromUtf8("background-color: rgba(238, 238, 236, 180);"));
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(850, 680, 411, 131));
        label_7->setStyleSheet(QString::fromUtf8("background-color: rgb(238, 238, 236);"));
        horizontalSlider = new QSlider(centralwidget);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(200, 760, 641, 51));
        horizontalSlider->setStyleSheet(QString::fromUtf8("color: rgb(238, 238, 236);\n"
"background-color: rgba(238, 238, 236, 180);"));
        horizontalSlider->setOrientation(Qt::Horizontal);
        cam_label = new QLabel(centralwidget);
        cam_label->setObjectName(QString::fromUtf8("cam_label"));
        cam_label->setGeometry(QRect(200, 20, 640, 360));
        cam_label->setStyleSheet(QString::fromUtf8("background-color: rgba(238, 238, 236, 180);"));
        cam_label->setAlignment(Qt::AlignCenter);
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(200, 390, 640, 360));
        test_label = new QLabel(centralwidget);
        test_label->setObjectName(QString::fromUtf8("test_label"));
        test_label->setGeometry(QRect(850, 70, 410, 350));
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        statusbar->setStyleSheet(QString::fromUtf8("background-color: rgb(238, 238, 236);"));
        MainWindow->setStatusBar(statusbar);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1280, 22));
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
        menuStreaming->addAction(actionLive_Streaming);
        menuStreaming->addAction(actionStreaming_End);
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
        label_3->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        gps_label->setText(QApplication::translate("MainWindow", "GPS DATA", nullptr));
        label_7->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        cam_label->setText(QApplication::translate("MainWindow", "CAM DATA", nullptr));
        label->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        test_label->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        menuStreaming->setTitle(QApplication::translate("MainWindow", "Streaming", nullptr));
        menuPlayback->setTitle(QApplication::translate("MainWindow", "Playback", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
