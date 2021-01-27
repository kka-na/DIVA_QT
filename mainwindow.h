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
#include <QRect>
#include <QLayout>
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
#include <QDir>
#include <QTextStream>


#include <QCanBus>
#include <QCanBusDevice>
#include <QCanBusDeviceInfo>
#include <QCanBusFrame>

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


#include "imuthread.h"
#include "camthread.h"
#include "gpsthread.h"
#include "lidarthread.h"
#include "lidarvtkwidget.h"
#include "canthread.h"
#include "qcgaugewidget.h"
#include "storingdb.h"
#include "imuwidget.h"
#include "makejson.h"

#include "Timestamp.h"


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

    bool use_gps = true;
    bool use_cam = true;
    bool use_lidar = true;
    bool use_imu = true;
    bool use_can = true;


    QSqlDatabase database;
    struct CurrentLog;
    QVector<CurrentLog> logs;
   
    QVector<QString> scenes_ftoken;
    QVector<int> scenes_nbrframes;
    bool this_is_get_log = false;

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

    QThread *canTTT;

    QString save_data_dir;
    string save_data_str;

    int gpscnt = 0;
    bool display_flag = true;
    QString addr;

    QLabel *redRectLabel;
    QLabel *lArrowLabel;
    QLabel *rArrowLabel;
    void Make();
    QString Check_Directory(QString Path);
    void Display_Scene(QString Text);
    void Setting_Frames(QString Text);
    void Display_Frame_Datas(QString Text);
    void Display_Gps_Data(QString Text);
    void Display_Imu_Data(QString Text);
    void Display_Can_Data(QString Text);

    bool setting_DB();

private:
    Ui::MainWindow *ui;
    QString dir;
    QString file_path;
    int nbr_frames;
    QTimer timer;

    class camThread::camThread *ct;
    class gpsThread::gpsThread *gt;
    class lidarThread::lidarThread *lt;
    class imuThread::imuThread *it;
    class lidarVTKWidget::lidarVTKWidget *lvw;
    class canThread::canThread *cant;
    class storingDB::storingDB *sdb;
    class MakeJson::MakeJson *mj;

    imuWidget *iw;
    Timestamp ts;



public slots:
    void display_gps_info(QString latitude, QString longitude);
    void display_handle_data(QString handle, QString handle_acceleration);
    void display_gear(int);
    void display_turn_indicator(int);
    void Display_Stop();
    void start_can_streaming();
    void gps_view_initialize();
    void display_cam(QImage image);
    void speedChanged(int value);

private slots:
    void Initializing_for_Live();
    void Initializing_for_Playback();
    void initialize_for_slider();
    void initial_map();
    void get_log_token();
    void on_pushButton_clicked();

    void on_label_3_itemClicked(QListWidgetItem *item);

    void on_actionDB_Storing_triggered();
    void on_actionJSON_Parsing_triggered();

    void on_horizontalSlider_sliderMoved(int position);


    void on_cam_cb_stateChanged(int arg1);

    void on_lidar_cb_stateChanged(int arg1);

    void on_imu_cb_stateChanged(int arg1);

    void on_can_cb_stateChanged(int arg1);

    void on_gps_cb_stateChanged(int arg1);

signals:
    void start();
    void send_dir(QString);
    void send_pcd(QString);
    void send_imu(float, float, float);
};
#endif // MAINWINDOW_H
