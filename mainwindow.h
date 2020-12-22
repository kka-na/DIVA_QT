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
#include <QMetaType>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QFile>
#include <QString>
#include <QDebug>
#include <QTextStream>


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
#include <vtkSmartPointer.h>
#include <vtkRenderWindowInteractor.h>

#include <pcl/point_cloud.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/common/transforms.h>
#include <pcl/console/parse.h>


#include "glwidget.h"
#include "camthread.h"
#include "gpsthread.h"
#include "lidarthread.h"
#include "lidarvtkwidget.h"
#include "canthread.h"
#include "qcgaugewidget.h"


#include "imuwidget.h"


typedef pcl::PointXYZ PointT;
typedef pcl::PointCloud<PointT> PointCloudT;

Q_DECLARE_METATYPE(pcl::PointCloud<pcl::PointXYZ>::Ptr)

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QSqlDatabase database;
    QVector<QString> scenes_ftoken;
    QVector<int> scenes_nbrframes;

    QSqlQuery* log_from_db;
    QSqlQuery* scene_from_db;
    QSqlQuery* frame_from_db;
    QSqlQuery* frame_data_jpg_from_db;
    QSqlQuery* frame_data_pcd_from_db;
    QSqlQuery* imu_from_db;
    QSqlQuery* gps_from_db;
    QSqlQuery* can_from_db;

    QWebEngineView *mview;
    QWebEnginePage *mpage;

    QLabel *camWidget;
    QLabel *gpsWidget;
    QLabel *gpsWidget2;
    QLabel *diva;
    QcGaugeWidget * mSpeedGauge;
    QcNeedleItem *mSpeedNeedle;

    int gpscnt = 0;
    QString addr;

    void Make();
    void Display_Scene(QString Text);
    void Setting_Frames(QString Text);
    void Display_Frame_Datas(QString Text);
    void Display_Gps_Data(QString Text);
    void Display_Imu_Data(QString Text);
    void Display_Can_Data(QString Text);

    bool setting_db();
    bool json_to_DB_log(string log_json_path);
    bool json_to_DB_scene(string scene_json_path);
    bool json_to_DB_frame(string frame_json_path);
    bool json_to_DB_frame_data(string frame_data_json_path);
    bool json_to_DB_gps(string gps_json_path);
    bool json_to_DB_imu(string imu_json_path);
    bool json_to_DB_can(string can_json_path);

private:
    Ui::MainWindow *ui;
    QString dir;
    QString file_path;
    int nbr_frames;
    QTimer timer;

    class camThread::camThread *ct;
    class gpsThread::gpsThread *gt;
    class lidarThread::lidarThread *lt;
    class lidarVTKWidget::lidarVTKWidget *lvw;
    class canThread::canThread *cant;

    glwidget *gw;
    QThread *workerThread_gl;
    imuWidget *iw;
    QThread *workerThread_imu;


public slots:


    void display_gps_info(QString latitude, QString longitude);
    void display_can_info(QString handle, QString handle_acceleration);
    void gps_view_initialize();
    void display_cam(QImage image);
    void speedChanged(int value);

private slots:

    void Initializing_for_Live();
    void Initializing_for_Playback();
    void initial_map();
    void get_log_token();
    
    void on_pushButton_clicked();

    void on_label_3_itemClicked(QListWidgetItem *item);

    void on_actionStroing_To_DB_triggered();

signals:
    void send_pcd(QString);
    void send_imu(float, float, float);
};
#endif // MAINWINDOW_H
