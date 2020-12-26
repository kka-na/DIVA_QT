#include "mainwindow.h"
#include "ui_mainwindow.h"

bool wifi_use = true;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    QThread::msleep(1000);
    qRegisterMetaType<pcl::PointCloud<pcl::PointXYZ>::Ptr >("pcl::PointCloud<pcl::PointXYZ>::Ptr");
    gpscnt = 0;
    connect(ui->actionInitializing, SIGNAL(triggered()), this, SLOT(Initializing_for_Live()));  
    connect(ui->actionInitializing_2, SIGNAL(triggered()), this, SLOT(Initializing_for_Playback()));  
}

MainWindow::~MainWindow()
{
    database.close();
    delete ui;
}


void MainWindow::display_gps_info(QString latitude, QString longitude){
    //mpage->setView(mview);
    string latlong = " lat : "+latitude.toStdString()+" long : "+longitude.toStdString();

    if(latitude != "0" && longitude != "0"){
        gpsWidget2->setText(QString::fromLocal8Bit(latlong.c_str()));

        if(wifi_use){
            mpage->runJavaScript(QString("addMarker(%1, %2);").arg(latitude).arg(longitude));  
                    if(gpscnt==0 || gpscnt%10 == 0){
                    mpage->runJavaScript(QString("getAddr();"),[this](const QVariant &v){
                        addr = v.toString();
                        gpsWidget->setText(addr);
                    });
            } 
        }
        gpsWidget2->show();
        gpsWidget->show();
        mview->show();
    }
    mview->show();
    gpscnt++;
}

void MainWindow::gps_view_initialize(){
    if(wifi_use){
        mpage->runJavaScript(QString("resetMarker();"));
        mpage->runJavaScript(QString("initMap();"));
        mview->show();
    } 
    //QCoreApplication::processEvents();
}

void MainWindow::display_cam(QImage image){
    camWidget->setPixmap(QPixmap::fromImage(image).scaled(camWidget->width(),camWidget->height(), Qt::KeepAspectRatio));
    camWidget->show();  
    QCoreApplication::processEvents();
}

void MainWindow::display_handle_data(QString str, QString str2){
    str.prepend("Handle degree : ");
    str.append("\nHandle acceleration : ");
    str.append(str2);
    ui->label_5->setText(str);
    ui->label_5->show();
    QCoreApplication::processEvents();
}

void MainWindow::speedChanged(int value){
    mSpeedNeedle->setCurrentValue(value);
    QCoreApplication::processEvents();
}

void MainWindow::display_gear(int gear){
    if(gear == 0){//P
        redRectLabel->move(57, 295); //p
    }else if(gear == 1){//R
        redRectLabel->move(107, 295); //R
    }else if(gear == 2){//N
        redRectLabel->move(157, 295); //N
    }else if(gear == 3){//D
        redRectLabel->move(207, 295); //D
    }else{
        return;
    }
    QCoreApplication::processEvents();
}

void MainWindow::display_turn_indicator(int turn){
    if(turn == 0){//left
        lArrowLabel->show();
    }else if(turn == 1){//right
        rArrowLabel->show();
    }else if(turn == 2){//none
        lArrowLabel->hide();
        rArrowLabel->hide();
    }
    QCoreApplication::processEvents();
}


void MainWindow::Make(){
    ct = new camThread(this);
    gt = new gpsThread(this);
    lt = new lidarThread(this);
    
    lvw = new lidarVTKWidget(this);
    cant = new canThread();
    camWidget = new QLabel(this);
    gpsWidget = new QLabel(this);
    
    

    QPixmap lpix("/home/kanakim/DIVA_QT/resource/leftarrowbefore.png");
    QPixmap rpix("/home/kanakim/DIVA_QT/resource/rightarrowbefore.png");
    ui->label->setPixmap(rpix);
    ui->label_2->setPixmap(lpix);
    
    QPixmap redRectPixm("/home/kanakim/DIVA_QT/resource/square.png");
    redRectLabel = new QLabel(this);
    redRectLabel->setStyleSheet("QLabel { background-color: rgba(255, 255, 255, 0); }");
    redRectLabel->setPixmap(redRectPixm);
    redRectLabel->resize(35,35);
    redRectLabel->move(57, 295); //p
    redRectLabel->show();


    QPixmap lArrowPixm("/home/kanakim/DIVA_QT/resource/leftarrow.png");
    QPixmap rArrowPixm("/home/kanakim/DIVA_QT/resource/rightarrow.png");
    lArrowLabel  = new QLabel(this); lArrowLabel->setStyleSheet("QLabel { background-color: rgba(255, 255, 255, 0); }");
    rArrowLabel = new QLabel(this); rArrowLabel->setStyleSheet("QLabel { background-color: rgba(255, 255, 255, 0); }");
    lArrowLabel->setPixmap(lArrowPixm);
    lArrowLabel->setGeometry(50,360,80,80);
    rArrowLabel->setPixmap(rArrowPixm);
    rArrowLabel->setGeometry(170,360,80,80);
    lArrowLabel->hide(); rArrowLabel->hide();

    ui->gridLayout_2->layout()->addWidget(lvw);
    lvw->setGeometry(300, 40,1280, 780);

    mpage = new QWebEnginePage(this);
    mview = new QWebEngineView(this);
    mview->setGeometry(1250,80,320,462);
    mpage->setUrl(QUrl("http://localhost:8080/map_display.html"));
    mpage->setView(mview);

    gpsWidget2 = new QLabel(this);
    gpsWidget->setGeometry(1250, 50, 320, 32);
    gpsWidget->setStyleSheet("background-color: rgb(255, 255, 255);");
    gpsWidget->setAlignment(Qt::AlignCenter);
    camWidget->setGeometry(320, 50, 352,200);
    camWidget->setStyleSheet("background-color: rgb(255, 255, 255);");
    gpsWidget2->setGeometry(1250, 470, 320, 32);
    gpsWidget2->setStyleSheet("background-color: rgb(255, 255, 255);");
    gpsWidget2->setAlignment(Qt::AlignCenter);
    gpsWidget2->raise();

    mSpeedGauge = new QcGaugeWidget;
    mSpeedGauge->addBackground(99);
    QcBackgroundItem *bkg1 = mSpeedGauge->addBackground(92);
    bkg1->clearrColors();
    bkg1->addColor(0.1,Qt::black);
    bkg1->addColor(1.0,Qt::white);
    QcBackgroundItem *bkg2 = mSpeedGauge->addBackground(88);
    bkg2->clearrColors();
    bkg2->addColor(0.1,Qt::gray);
    bkg2->addColor(1.0,Qt::darkGray);
    mSpeedGauge->addArc(55);
    mSpeedGauge->addDegrees(65)->setValueRange(0,120);
    mSpeedGauge->addColorBand(50);
    mSpeedGauge->addValues(80)->setValueRange(0,120);
    mSpeedGauge->addLabel(70)->setText("Km/h");
    QcLabelItem *lab = mSpeedGauge->addLabel(40);
    lab->setText("0");
    mSpeedNeedle = mSpeedGauge->addNeedle(60);
    mSpeedNeedle->setLabel(lab);
    mSpeedNeedle->setColor(Qt::white);
    mSpeedNeedle->setValueRange(0,120);
    mSpeedGauge->addBackground(15);
    mSpeedGauge->addGlass(88);
    ui->gridLayout->layout()->addWidget(mSpeedGauge);

}


void MainWindow::Initializing_for_Live(){

    this->Make();

    diva = new QLabel(this);
    diva->setGeometry(15, 622, 274,262);
    diva->setStyleSheet("background-color: rgb(255, 255, 255);");
    diva->setAlignment(Qt::AlignCenter);
    QPixmap temp_jpeg; 
    temp_jpeg.load("/home/kanakim/DIVA_QT/resource/diva_logo.jpg");
    diva->setPixmap(temp_jpeg.scaled(diva->width(), diva->height(),Qt::KeepAspectRatio));
    diva->show();
    mview->show();
    gw = new glwidget();
    ui->gridLayout_3->layout()->addWidget(gw);

    QString live_str = "Data Capturing Date : ";
    live_str.append(QString::fromLocal8Bit(ts.getDate().c_str()));
    ui->label_7->setText(live_str);

    save_data_dir = QFileDialog::getExistingDirectory(this, "Select Driving Directory to Stroing Datas", QDir::currentPath(),QFileDialog::ShowDirsOnly);
    save_data_dir = this->Check_Directory(save_data_dir);
    save_data_str = save_data_dir.toStdString();
    
    connect(this, SIGNAL(send_dir(std::string)), ct, SLOT(get_dir(std::string)));
    connect(this, SIGNAL(send_dir(std::string)), gt, SLOT(get_dir(std::string)));
    connect(this, SIGNAL(send_dir(std::string)), lt, SLOT(get_dir(std::string)));
    connect(this, SIGNAL(send_dir(std::string)), gw, SLOT(get_dir(std::string)));
    connect(this, SIGNAL(send_dir(std::string)), cant, SLOT(get_dir(std::string)));
    emit send_dir(save_data_str);

    connect(ui->actionLive_Streaming, SIGNAL(triggered()), ct, SLOT(start()));
    connect(ui->actionLive_Streaming, SIGNAL(triggered()), gt, SLOT(start()));
    connect(ui->actionLive_Streaming, SIGNAL(triggered()), lt, SLOT(start()));
    connect(ui->actionLive_Streaming, SIGNAL(triggered()), lvw, SLOT(init()));
    connect(ui->actionLive_Streaming, SIGNAL(triggered()), cant, SLOT(start()));
    connect(ui->actionLive_Streaming, SIGNAL(triggered()), gw, SLOT(streaming_start()));

    connect(ct, SIGNAL(send_qimage(QImage)), this, SLOT(display_cam(QImage)));
    connect(lt, SIGNAL(send_lidar(pcl::PointCloud<pcl::PointXYZ>::Ptr)), lvw, SLOT(display_lidar(pcl::PointCloud<pcl::PointXYZ>::Ptr)));
    //connect(lt, SIGNAL(connectedOK()), this, SLOT(initial_map()));
    connect(cant, SIGNAL(send_handle(QString, QString)),this, SLOT(display_handle_data(QString, QString)));
    connect(cant, SIGNAL(send_speed(int)),this, SLOT(speedChanged(int)));
    connect(cant, SIGNAL(send_gear(int)), this, SLOT(display_gear(int)));
    connect(cant, SIGNAL(send_turn(int)), this, SLOT(display_turn_indicator(int)));

    connect(gt, SIGNAL(send_ll(QString, QString)), this, SLOT(display_gps_info(QString, QString)));
   
    
    //conenct to widget for close
    connect(ui->actionStreaming_End, SIGNAL(triggered()), ct, SLOT(stop()));
    connect(ui->actionStreaming_End, SIGNAL(triggered()), gw, SLOT(initialize_glwidget()));
    connect(ui->actionStreaming_End, SIGNAL(triggered()), gt, SLOT(stop()));
    connect(ui->actionStreaming_End, SIGNAL(triggered()), lt, SLOT(stop()));
    connect(gt, SIGNAL(send_end()), this, SLOT(gps_view_initialize()));
    connect(ui->actionStreaming_End, SIGNAL(triggered()), cant, SLOT(stop()));
    
}

QString MainWindow::Check_Directory(QString dirpath){
    QDir root(dirpath);
    if(root.exists()){
        dirpath.append("/");
        dirpath.append(QString::fromLocal8Bit(ts.getDate().c_str()));
        QString dirpath1 = dirpath;
        QString dirpath2 = dirpath;
        QString dirpath3 = dirpath;
        QString dirpath4 = dirpath;
        QString dirpath5 = dirpath;
        QString dirpath6 = dirpath;
        QDir camdir(dirpath1.append("/CAM/JPG"));
        QDir lidardir(dirpath2.append("/LiDAR/PCD"));
        QDir gpsdir(dirpath3.append("/GPS"));
        QDir imudir(dirpath4.append("/IMU"));
        QDir candir(dirpath5.append("/CAN"));
        QDir jsondir(dirpath6.append("/JSON"));
        if(!camdir.exists()){
            camdir.mkpath(".");
        }
        if(!lidardir.exists()){
            lidardir.mkpath(".");
        }
        if(!gpsdir.exists()){
            gpsdir.mkpath(".");
        }
        if(!imudir.exists()){
            imudir.mkpath(".");
        }
        if(!candir.exists()){
            candir.mkpath(".");
        }
        if(!jsondir.exists()){
            jsondir.mkpath(".");
        }
    }else{
        cout<<"Incorrect Directory Path"<<endl;
        return NULL;
    }
    return dirpath;
}


void MainWindow::initial_map(){
    mpage->setUrl(QUrl("http://localhost:8080/map_display.html"));
    //mpage->setView(mview);
}



void MainWindow::on_actionJSON_Parsing_triggered(){

    save_data_dir = QFileDialog::getExistingDirectory(this, "Select Driving Directory Raw Data Stored", QDir::currentPath(),QFileDialog::ShowDirsOnly);
    save_data_str = save_data_dir.toStdString();
    mj = new MakeJson(save_data_str);
    
    cout<<save_data_str<<endl;
    mj->Sensor(5);
    mj->Log(0);
    mj->Frame();
    mj->Scene();
    mj->Frame_Data();
    mj->Gps_Data();
    mj->Imu_Data();
    mj->Can_Data();
}

void MainWindow::on_actionDB_Storing_triggered(){
    dir = QFileDialog::getExistingDirectory(this, "Select Driving Directory to Saving JSON files to DB", QDir::currentPath(),QFileDialog::ShowDirsOnly);
    string fpath = dir.toStdString();
    sdb = new storingDB(fpath);
}

void MainWindow::Initializing_for_Playback(){
    this->Make();
    iw = new imuWidget();
    ui->gridLayout_3->layout()->addWidget(iw);
    mview->show();

    if(this->setting_DB()){
        connect(ui->actionGet_Log, SIGNAL(triggered()), this, SLOT(get_log_token()));
        connect(ui->actionGet_Log, SIGNAL(triggered()), lvw, SLOT(init()), Qt::QueuedConnection);
        connect(this, SIGNAL(send_pcd(QString)), lvw, SLOT(display_pcd(QString)));
        connect(this, SIGNAL(send_imu(float, float, float)), iw, SLOT(streaming_start(float,float,float)));
        connect(ui->actionFinish, SIGNAL(triggered()), this, SLOT(Display_Stop()));
    }else{
        std::cout<<"Can't connect to DB"<<std::endl;
    }
}

//psql -h localhost -p 5432 -U diva -d "diva"


void MainWindow::get_log_token(){
    this->log_from_db = new QSqlQuery(this->database);
    this->log_from_db->exec("SELECT * FROM LOG;");
    this->log_from_db->first();
    QString log_token = this->log_from_db->value(0).toString(); //just get the first log token
    QString log_str = "Vehicle : ";
    log_str.append(this->log_from_db->value(2).toString());
    log_str.append(", Captured Date : ");
    log_str.append(this->log_from_db->value(1).toString());
    ui->label_7->setText(log_str);
    this->Display_Scene(log_token);
}

void MainWindow::Display_Scene(QString Text){
    this->scene_from_db = new QSqlQuery(this->database);
    QString selectq = "SELECT * FROM SCENE WHERE log_token = '";
    selectq.append(Text);
    selectq.append("';");
    this->scene_from_db->exec(selectq);
    scenes_ftoken.clear();
    scenes_nbrframes.clear();

    int idx = 0;
    while(1){
        if(this->scene_from_db->next()){
            scenes_ftoken.push_back(this->scene_from_db->value(0).toString());
            scenes_nbrframes.push_back(this->scene_from_db->value(2).toInt());
            QString Scene_temp = QString::number(idx, 10);
            Scene_temp.prepend("scene_");
            ui->label_3->addItem(Scene_temp);
            idx++;
        }else break;        
    }

}

int counted_frames;
int idx_for_cnt_frames;
int *saved_idx_for_cnt_frames;
QString *saved_token_for_cnt_frames;
void MainWindow::on_pushButton_clicked(){
    QString index = ui->label_3->currentItem()->text();
    index.remove(0,6);
    QString fftoken=scenes_ftoken.at(index.toInt());
    nbr_frames = scenes_nbrframes.at(index.toInt());
    counted_frames = 0;
    this->Setting_Frames(fftoken);
}


void MainWindow::on_label_3_itemClicked(QListWidgetItem *item){
    camWidget->clear();
    this->display_flag = true;
    this->gps_view_initialize();
    //iw->clear();
    saved_idx_for_cnt_frames = new int[200];
    saved_token_for_cnt_frames = new QString[200];
    ui->horizontalSlider->setRange(0, 200);
    ui->horizontalSlider->setValue(0);
    idx_for_cnt_frames = 0;
}



void MainWindow::Setting_Frames(QString Text){
    QString current_frame_token = Text;
    this->frame_from_db = new QSqlQuery(this->database);
    QString selectq = "SELECT * FROM FRAME;";
    this->frame_from_db -> exec(selectq);

    while(display_flag){
        if(counted_frames > nbr_frames-1){
            break;
        }
        if(this->frame_from_db->next()){
            QString idx_frame_token = this->frame_from_db->value(0).toString(); //temp token
            if(idx_frame_token == current_frame_token){
                saved_idx_for_cnt_frames[counted_frames] = idx_for_cnt_frames;
                saved_token_for_cnt_frames[counted_frames] = idx_frame_token;

                ui->horizontalSlider->setValue(counted_frames);

                this->Display_Frame_Datas(current_frame_token);
                QCoreApplication::processEvents();

                current_frame_token =this->frame_from_db->value(1).toString(); //next token
                if(current_frame_token == ""){
                    display_flag=false;
                }
                counted_frames++;
            }
            idx_for_cnt_frames++;
        }
    }
    
}
void MainWindow::Display_Frame_Datas(QString Text){
    QString idx_file_format;
    QString idx_frame_data_token;

    this->frame_data_jpg_from_db = new QSqlQuery(this->database);
    this->frame_data_pcd_from_db = new QSqlQuery(this->database);
    QString selectq1 = "SELECT * FROM FRAME_DATA WHERE fileformat='jpeg' and frame_token = '";
    selectq1.append(Text);
    selectq1.append("';");
    this->frame_data_jpg_from_db -> exec(selectq1);
    QString selectq2 = "SELECT * FROM FRAME_DATA WHERE fileformat='pcd' and frame_token = '";
    selectq2.append(Text);
    selectq2.append("';");
    this->frame_data_pcd_from_db -> exec(selectq2);

    this->frame_data_pcd_from_db->first();
    QString idx_lidar_filename = this->frame_data_pcd_from_db->value(3).toString();
    emit send_pcd(idx_lidar_filename);
    QCoreApplication::processEvents();

    this->frame_data_jpg_from_db->first();
    QPixmap temp_jpeg;
    QString idx_jpg_filename =  this->frame_data_jpg_from_db->value(3).toString();
    temp_jpeg.load(idx_jpg_filename);
    camWidget->setPixmap(temp_jpeg.scaled(camWidget->width(),camWidget->height(), Qt::KeepAspectRatio));

    this->Display_Gps_Data(this->frame_data_jpg_from_db->value(1).toString());
    this->Display_Imu_Data(this->frame_data_jpg_from_db->value(1).toString());
    this->Display_Can_Data(this->frame_data_jpg_from_db->value(1).toString());

    camWidget->show();
    QCoreApplication::processEvents();
}


void MainWindow::Display_Gps_Data(QString Text){
    QString idx_lat;
    QString idx_lng;
    QString idx_token;

    this->gps_from_db = new QSqlQuery(this->database);
    QString selectq = "SELECT * FROM GPS_DATA WHERE token = '";
    selectq.append(Text);
    selectq.append("';");
    this->gps_from_db -> exec(selectq);
    this->gps_from_db->first();
    idx_lat = this->gps_from_db->value(1).toString();
    idx_lng =this->gps_from_db->value(2).toString();

    this->display_gps_info(idx_lat, idx_lng);
    QCoreApplication::processEvents();
}

void MainWindow::Display_Imu_Data(QString Text){
    QString idx_ax;
    QString idx_ay;
    QString idx_az;

    this->imu_from_db = new QSqlQuery(this->database);
    QString selectq = "SELECT * FROM IMU_DATA WHERE token = '";
    selectq.append(Text);
    selectq.append("';");
    this->imu_from_db -> exec(selectq);

    this->imu_from_db->first();
    idx_ax = this->imu_from_db->value(4).toString();
    idx_ay =this->imu_from_db->value(5).toString();
    idx_az =this->imu_from_db->value(6).toString();
    
    emit send_imu(idx_ax.toFloat(), idx_ay.toFloat(), idx_az.toFloat());
    QCoreApplication::processEvents();   
}


void MainWindow::Display_Can_Data(QString Text){
    QString handle;
    QString handle_ac;
    QString speed;
    QString gear;
    QString turn;

    this->can_from_db = new QSqlQuery(this->database);
    QString selectq = "SELECT * FROM CAN_DATA WHERE token = '";
    selectq.append(Text);
    selectq.append("';");
    this->can_from_db -> exec(selectq);

    this->can_from_db->first();
    handle = this->can_from_db->value(1).toString();
    handle_ac =this->can_from_db->value(2).toString();
    speed =this->can_from_db->value(3).toString(); //speed 
    gear=this->can_from_db->value(4).toString();
    turn=this->can_from_db->value(5).toString();
    
    this->display_handle_data(handle, handle_ac);
    this->display_gear(gear.toInt());
    this->display_turn_indicator(turn.toInt());
    this->speedChanged(speed.toInt());
    QCoreApplication::processEvents();
}


bool MainWindow::setting_DB(){
        // *****Set DB Information*****
        QSqlDatabase database=QSqlDatabase::addDatabase("QPSQL7");
        database.setDatabaseName("diva");
        database.setHostName("localhost");
        database.setUserName("diva");
        database.setPassword("password");
        database.setPort(5432);
        bool con = false;
        if (database.open()){
            qDebug() << "Connection Successful";
            con = true;
        }
        else
            qDebug() << "Connection Failed!";

        qDebug() << "db connection" << database.open();
        return con;
}


void MainWindow::Display_Stop(){
    this->display_flag=false;
}

void MainWindow::on_horizontalSlider_sliderMoved(int position){
    initialize_for_slider();
    idx_for_cnt_frames = saved_idx_for_cnt_frames[position];
    counted_frames = position;
    this->Setting_Frames(saved_token_for_cnt_frames[position]);
}

void MainWindow::initialize_for_slider(){
    camWidget->clear();
    this->display_flag = true;
    this->gps_view_initialize();
    iw->clear();
}
