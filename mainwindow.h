#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QListWidgetItem>
#include <QRadioButton>
#include <QDebug>
#include <QMessageBox>
#include <QObject>
#include <QThread>
#include <QLabel>
#include <QMap>
#include <QUrl>
#include <QTimer>
#include <QtWebEngineWidgets/QtWebEngineWidgets>

#include "jsoncpp/json/json.h"

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <ctime>

#include <vtkRenderWindow.h>

#include <pcl/point_cloud.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/common/transforms.h>
#include <pcl/console/parse.h>

#include "glwidget.h"
#include "camthread.h"
#include "gpsthread.h"

typedef pcl::PointXYZ PointT;
typedef pcl::PointCloud<PointT> PointCloudT;


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QWebEngineView *mview;
    QWebEnginePage *mpage;

    int gpscnt = 0;
    QString addr;

private:
    Ui::MainWindow *ui;
    QString dir;
    QString file_path;
    int nbr_frames;
    QTimer timer;

    class camThread::camThread *ct;
    class gpsThread::gpsThread *gt;

public slots:
    void display_gps_info(QString latitude, QString longitude);
    void gps_view_initialize();
    void display_cam(QImage image);

private slots:

};
#endif // MAINWINDOW_H
