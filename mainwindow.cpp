#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QThread::msleep(1000);

    ct = new camThread(this);
    gt = new gpsThread(this);

    mpage = new QWebEnginePage(this);
    mview = new QWebEngineView(this);
    mview->setGeometry(850,90,410,350);
    mpage->setUrl(QUrl("http://localhost:8080/map_display.html"));
    mpage->setView(mview);

    connect(ui->actionLive_Streaming, SIGNAL(triggered()), ct, SLOT(start()));
    connect(ui->actionLive_Streaming, SIGNAL(triggered()), gt, SLOT(start()));

    connect(ct, SIGNAL(send_qimage(QImage)), this, SLOT(display_cam(QImage)));
    connect(gt, SIGNAL(send_ll(QString, QString)), this, SLOT(display_gps_info(QString, QString)));

    connect(ui->actionLive_Streaming, SIGNAL(triggered()), ui->imu_label, SLOT(streaming_start()));
    

    //conenct to widget for close
    connect(ui->actionStreaming_End, SIGNAL(triggered()), ct, SLOT(stop()));
    connect(ui->actionStreaming_End, SIGNAL(triggered()), ui->imu_label, SLOT(initialize_glwidget()));
    connect(ui->actionStreaming_End, SIGNAL(triggered()), gt, SLOT(stop()));
    connect(gt, SIGNAL(send_end()), this, SLOT(gps_view_initialize()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::display_gps_info(QString latitude, QString longitude){
    //std::cout<<"display_gps_info"<<std::endl;
    //string latlong = "Now Location => lat : "+latitude.toStdString()+" long : "+longitude.toStdString();
    //ui->gps_label->setText(QString::fromLocal8Bit(latlong.c_str()));

    if(gpscnt==0 || gpscnt%50 == 0){
        mpage->runJavaScript(QString("getAddr();"),[this](const QVariant &v){
            addr = v.toString();
            ui->gps_label->setText(addr);
        });
    }


    mpage->runJavaScript(QString("addMarker(%1, %2);").arg(latitude).arg(longitude));  
    gpscnt++;
}

void MainWindow::gps_view_initialize(){
    mpage->runJavaScript(QString("resetMarker();"));
    mpage->runJavaScript(QString("initMap();"));
    QCoreApplication::processEvents();
}

void MainWindow::display_cam(QImage image){
    //std::cout<<"display_cam"<<std::endl;
    ui->cam_label->setPixmap(QPixmap::fromImage(image).scaled(ui->cam_label->width(),ui->cam_label->height(), Qt::KeepAspectRatio));
    ui->cam_label->setAlignment(Qt::AlignCenter);
    ui->cam_label->show();
}
