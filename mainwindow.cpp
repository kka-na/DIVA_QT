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
    mpage->setView(mview);
    string latlong = " lat : "+latitude.toStdString()+" long : "+longitude.toStdString();

    if(latitude != "0" && longitude != "0"){
        gpsWidget2->setText(QString::fromLocal8Bit(latlong.c_str()));

        if(wifi_use){
            mpage->runJavaScript(QString("addMarker(%1, %2);").arg(latitude).arg(longitude));  
                    if(gpscnt==0 || gpscnt%50 == 0){
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
    gpscnt++;
}

void MainWindow::gps_view_initialize(){

    if(wifi_use){
        mpage->runJavaScript(QString("resetMarker();"));
        mpage->runJavaScript(QString("initMap();"));
        mview->show();
    } 
    QCoreApplication::processEvents();
}

void MainWindow::display_cam(QImage image){
    //std::cout<<"display_cam"<<std::endl;
    camWidget->setPixmap(QPixmap::fromImage(image).scaled(camWidget->width(),camWidget->height(), Qt::KeepAspectRatio));
    camWidget->show();
    
    QCoreApplication::processEvents();
}

void MainWindow::display_can_info(QString str, QString str2){
    //std::cout<<"display_cam"<<std::endl;
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

void MainWindow::Make(){


    ct = new camThread(this);
    gt = new gpsThread(this);
    lt = new lidarThread(this);
    
    lvw = new lidarVTKWidget(this);
    cant = new canThread(this);
    
    camWidget = new QLabel(this);
    gpsWidget = new QLabel(this);
    gpsWidget2 = new QLabel(this);
    mpage = new QWebEnginePage(this);
    mview = new QWebEngineView(this);
    
    layout()->addWidget(lvw);
    lvw->setGeometry(300, 40, 928, 780);
    mview->setGeometry(1240,80,352,462);
    mpage->setUrl(QUrl("http://localhost:8080/map_display.html"));
    mpage->setView(mview);
    

    gpsWidget->setGeometry(1240, 50, 352, 32);
    gpsWidget->setStyleSheet("background-color: rgb(255, 255, 255);");
    gpsWidget->setAlignment(Qt::AlignCenter);
    camWidget->setGeometry(310, 50, 352,200);
    camWidget->setStyleSheet("background-color: rgb(255, 255, 255);");
    gpsWidget2->setGeometry(1240, 470, 352, 32);
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
    temp_jpeg.load("/home/kanakim/DIVA_QT/diva_logo.jpg");
    diva->setPixmap(temp_jpeg.scaled(diva->width(), diva->height(),Qt::KeepAspectRatio));
    diva->show();

    
    connect(ui->actionLive_Streaming, SIGNAL(triggered()), ct, SLOT(start()));
    connect(ui->actionLive_Streaming, SIGNAL(triggered()), gt, SLOT(start()));
    connect(ui->actionLive_Streaming, SIGNAL(triggered()), lt, SLOT(start()), Qt::QueuedConnection);
    connect(ui->actionLive_Streaming, SIGNAL(triggered()), lvw, SLOT(init()), Qt::QueuedConnection);
    connect(ui->actionLive_Streaming, SIGNAL(triggered()), cant, SLOT(start()));
    
    connect(ct, SIGNAL(send_qimage(QImage)), this, SLOT(display_cam(QImage)));
    connect(lt, SIGNAL(send_lidar(pcl::PointCloud<pcl::PointXYZ>::Ptr)), lvw, SLOT(display_lidar(pcl::PointCloud<pcl::PointXYZ>::Ptr)), Qt::QueuedConnection);

    connect(lt, SIGNAL(connectedOK()), this, SLOT(initial_map()));
    connect(gt, SIGNAL(send_ll(QString, QString)), this, SLOT(display_gps_info(QString, QString)));

    connect(cant, SIGNAL(send_handle(QString, QString)),this, SLOT(display_can_info(QString, QString)));
    //connect(cant, SIGNAL(send_handle(QString)),this, SLOT(display_can_info(QString)));
    connect(cant, SIGNAL(send_speed(int)),this, SLOT(speedChanged(int)));

    connect(ui->actionLive_Streaming, SIGNAL(triggered()), ui->imu_label, SLOT(streaming_start()));


    //conenct to widget for close
    connect(ui->actionStreaming_End, SIGNAL(triggered()), ct, SLOT(stop()));
    connect(ui->actionStreaming_End, SIGNAL(triggered()), ui->imu_label, SLOT(initialize_glwidget()));
    connect(ui->actionStreaming_End, SIGNAL(triggered()), gt, SLOT(stop()));
    connect(ui->actionStreaming_End, SIGNAL(triggered()), lt, SLOT(stop()));
    connect(gt, SIGNAL(send_end()), this, SLOT(gps_view_initialize()));

    connect(ui->actionStreaming_End, SIGNAL(triggered()), cant, SLOT(stop()));
    
}


void MainWindow::initial_map(){

    mpage->setUrl(QUrl("http://localhost:8080/map_display.html"));
    mpage->setView(mview);
}



void MainWindow::on_actionStroing_To_DB_triggered(){

    if(this->setting_db()){
        dir = QFileDialog::getExistingDirectory(this, "Select Driving Directory to Stroing JSON to DB", QDir::currentPath(),QFileDialog::ShowDirsOnly);
        string log_json_path =dir.toStdString()+"/JSON/log.json";
        string scene_json_path =dir.toStdString()+"/JSON/scene.json";
        string frame_json_path =dir.toStdString()+"/JSON/frame.json";
        string frame_data_json_path =dir.toStdString()+"/JSON/frame_data.json";
        string gps_json_path =dir.toStdString()+"/JSON/gps_data.json";
        string imu_json_path =dir.toStdString()+"/JSON/imu_data.json";
        string can_json_path = dir.toStdString()+"/JSON/can_data.json";

        json_to_DB_log(log_json_path);
        json_to_DB_scene(scene_json_path);
        json_to_DB_frame(frame_json_path);
        json_to_DB_frame_data(frame_data_json_path);
        json_to_DB_gps(gps_json_path);
        json_to_DB_imu(imu_json_path);
        json_to_DB_can(can_json_path);

    }else{
        std::cout<<"Can't connect to DB"<<std::endl;
    } 

}

void MainWindow::Initializing_for_Playback(){

    this->Make();

    iw = new imuWidget();
    ui->gridLayout_2->layout()->addWidget(iw);

    if(this->setting_db()){
        connect(ui->actionGet_Log, SIGNAL(triggered()), this, SLOT(get_log_token()));
        connect(ui->actionGet_Log, SIGNAL(triggered()), lvw, SLOT(init()), Qt::QueuedConnection);
        connect(this, SIGNAL(send_pcd(QString)), lvw, SLOT(display_pcd(QString)));
        connect(this, SIGNAL(send_imu(float, float, float)), iw, SLOT(streaming_start(float,float,float)));
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
void MainWindow::on_pushButton_clicked()
{
    QString index = ui->label_3->currentItem()->text();
    index.remove(0,6);
    QString fftoken=scenes_ftoken.at(index.toInt());
    nbr_frames = scenes_nbrframes.at(index.toInt());
    counted_frames = 0;
    this->Setting_Frames(fftoken);
}

void MainWindow::Setting_Frames(QString Text){
    QString current_frame_token = Text;
    this->frame_from_db = new QSqlQuery(this->database);
    QString selectq = "SELECT * FROM FRAME;";
    this->frame_from_db -> exec(selectq);

    while(1){
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
                counted_frames++;
                QThread::msleep(100);
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

    QCoreApplication::processEvents();

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

    this->can_from_db = new QSqlQuery(this->database);
    QString selectq = "SELECT * FROM CAN_DATA WHERE token = '";
    selectq.append(Text);
    selectq.append("';");
    this->can_from_db -> exec(selectq);

    this->can_from_db->first();
    handle = this->can_from_db->value(2).toString();
    handle_ac =this->can_from_db->value(3).toString();
    speed =this->can_from_db->value(4).toS tring(); //speed 
    
    this->display_can_info(handle, handle_ac);
    this->speedChanged(speed.toInt());
    QCoreApplication::processEvents();

}

void MainWindow::on_label_3_itemClicked(QListWidgetItem *item)
{
    camWidget->clear();
    this->gps_view_initialize();
    saved_idx_for_cnt_frames = new int[200];
    saved_token_for_cnt_frames = new QString[200];
    ui->horizontalSlider->setRange(0, 200);
    ui->horizontalSlider->setValue(0);
    idx_for_cnt_frames = 0;
}



bool MainWindow::setting_db(){
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








// - - - - - - - - -- -- - --storing to db - - - - - - - -  - - -  - -- //

bool  MainWindow::json_to_DB_log(string path){

        QSqlQuery input(database);
        database.transaction();
        input.exec("create table LOG(token text,date_captured text,vehicle text);"); // *****Set table and column*****
        database.commit();
      
        Json::Value Logs;
        ifstream in(path.c_str());
        if(in.is_open()) in >> Logs;

        QString temp1;
        QString temp2;
        QString temp3;

        for(int i=0;i<Logs.size();i++)
        {   
            temp2=QString::fromLocal8Bit((Logs[i]["date_captured"].asString()).c_str());
            temp1=QString::fromLocal8Bit((Logs[i]["token"].asString()).c_str());
            temp3=QString::fromLocal8Bit((Logs[i]["vehicle"].asString()).c_str());

            database.transaction();
            QString query_string;
            query_string.append("insert into LOG values('"); // *****Set table*****
            query_string.append(temp1);
            query_string.append("','");
            query_string.append(temp2);
            query_string.append("','");
            query_string.append(temp3);
            query_string.append("');");
            input.exec(query_string);
            database.commit();
        }
        return 1;
    }



    bool  MainWindow::json_to_DB_scene(string path){

        QSqlQuery input(database);
        database.transaction();
        input.exec("create table SCENE(first_frame_token text,log_token text, nbr_frames text);"); // *****Set table and column*****
        database.commit();

        Json::Value Scenes;
        ifstream scene_in(path.c_str());
        if(scene_in.is_open()) scene_in>>Scenes;

        QString temp1;
        QString temp2;
        QString temp3;

        for(int i=0; i<Scenes.size(); i++)
        {
            temp1=QString::fromLocal8Bit((Scenes[i]["first_frame_token"].asString()).c_str());
            temp2=QString::fromLocal8Bit((Scenes[i]["log_token"].asString()).c_str());
            temp3=QString::fromLocal8Bit((Scenes[i]["nbr_frames"].asString()).c_str());

            database.transaction();
            QString query_string;
            query_string.append("insert into SCENE values('"); // *****Set table*****
            query_string.append(temp1);
            query_string.append("','");
            query_string.append(temp2);
            query_string.append("','");
            query_string.append(temp3);
            query_string.append("');");
            input.exec(query_string);
            database.commit();
        }
        return 1;
    }


    bool  MainWindow::json_to_DB_frame(string path){

        QSqlQuery input(database);
        database.transaction();
        input.exec("create table FRAME(frame_token text,token_next text);"); // *****Set table and column*****
        database.commit();

        Json::Value Frames;
        ifstream scene_in(path.c_str());
        if(scene_in.is_open()) scene_in>>Frames;

        QString temp1;
        QString temp2;

        for(int i=0; i<Frames.size(); i++)
        {
            temp1=QString::fromLocal8Bit((Frames[i]["frame_token"].asString()).c_str());
            temp2=QString::fromLocal8Bit((Frames[i]["token_next"].asString()).c_str());

            database.transaction();
            QString query_string;
            query_string.append("insert into FRAME values('"); // *****Set table*****
            query_string.append(temp1);
            query_string.append("','");
            query_string.append(temp2);
            query_string.append("');");
            input.exec(query_string);
            database.commit();
        }
        return 1;
    }

    bool  MainWindow::json_to_DB_frame_data(string path){

        QSqlQuery input(database);
        database.transaction();
        input.exec("create table FRAME_DATA(frame_token text,frame_data_token text,fileformat text, filename text);"); // *****Set table and column*****
        database.commit();

        Json::Value Frame_datas;
        ifstream scene_in(path.c_str());
        if(scene_in.is_open()) scene_in>>Frame_datas;

        QString temp1;
        QString temp2;
        QString temp3;
        QString temp4;

        for(int i=0; i<Frame_datas.size(); i++)
        {
            temp3=QString::fromLocal8Bit((Frame_datas[i]["fileformat"].asString()).c_str());
            temp4=QString::fromLocal8Bit((Frame_datas[i]["filename"].asString()).c_str());
            temp1=QString::fromLocal8Bit((Frame_datas[i]["frame_token"].asString()).c_str());
            temp2=QString::fromLocal8Bit((Frame_datas[i]["frame_data_token"].asString()).c_str());
            

            database.transaction();
            QString query_string;
            query_string.append("insert into FRAME_DATA values('"); // *****Set table*****
            query_string.append(temp1);
            query_string.append("','");
            query_string.append(temp2);
            query_string.append("','");
            query_string.append(temp3);
            query_string.append("','");
            query_string.append(temp4);
            query_string.append("');");
            input.exec(query_string);
            database.commit();
        }
        return 1;
    }


    bool  MainWindow::json_to_DB_gps(string path){

        QSqlQuery input(database);
        database.transaction();
        input.exec("create table GPS_DATA(token text,latitude text,longitude text);"); // *****Set table and column*****
        database.commit();

        Json::Value Gps_datas;
        ifstream scene_in(path.c_str());
        if(scene_in.is_open()) scene_in>>Gps_datas;

        QString temp1;
        QString temp2;
        QString temp3;

        for(int i=0; i<Gps_datas.size(); i++)
        {
            
            temp2=QString::fromLocal8Bit((Gps_datas[i]["latitude"].asString()).c_str());
            temp3=QString::fromLocal8Bit((Gps_datas[i]["longitude"].asString()).c_str());
            temp1=QString::fromLocal8Bit((Gps_datas[i]["token"].asString()).c_str());

            database.transaction();
            QString query_string;
            query_string.append("insert into GPS_DATA values('"); // *****Set table*****
            query_string.append(temp1);
            query_string.append("','");
            query_string.append(temp2);
            query_string.append("','");
            query_string.append(temp3);
            query_string.append("');");
            input.exec(query_string);
            database.commit();
        }
        return 1;
    }

    bool  MainWindow::json_to_DB_imu(string path){

        QSqlQuery input(database);
        database.transaction();
        input.exec("create table IMU_DATA(token text,gyx text, gyy text,gyz text, acx text, acy text,acz text, max text, may text,maz text);"); // *****Set table and column*****
        database.commit();

        Json::Value Imu_datas;
        ifstream scene_in(path.c_str());
        if(scene_in.is_open()) scene_in>>Imu_datas;

        QString idx_gyx;QString idx_gyy;QString idx_gyz;
        QString idx_acx;QString idx_acy;QString idx_acz;
        QString idx_max;QString idx_may;QString idx_maz;
        QString idx_token;

        for(int i=0; i<Imu_datas.size(); i++)
        {   
            
            idx_gyx =  QString::fromLocal8Bit((Imu_datas[i]["gyroscope"][0].asString()).c_str());
            idx_gyy =  QString::fromLocal8Bit((Imu_datas[i]["gyroscope"][1].asString()).c_str());
            idx_gyz =  QString::fromLocal8Bit((Imu_datas[i]["gyroscope"][2].asString()).c_str());
            idx_acx =  QString::fromLocal8Bit((Imu_datas[i]["acceleration"][0].asString()).c_str());
            idx_acy =  QString::fromLocal8Bit((Imu_datas[i]["acceleration"][1].asString()).c_str());
            idx_acz =  QString::fromLocal8Bit((Imu_datas[i]["acceleration"][2].asString()).c_str());
            idx_max =  QString::fromLocal8Bit((Imu_datas[i]["magnetic"][0].asString()).c_str());
            idx_may =  QString::fromLocal8Bit((Imu_datas[i]["magnetic"][1].asString()).c_str());
            idx_maz =  QString::fromLocal8Bit((Imu_datas[i]["magnetic"][2].asString()).c_str());
            idx_token = QString::fromLocal8Bit((Imu_datas[i]["token"].asString()).c_str());

            database.transaction();
            QString query_string;
            query_string.append("insert into IMU_DATA values('"); // *****Set table*****
            query_string.append(idx_token);
            query_string.append("','");
            query_string.append(idx_gyx);
            query_string.append("','");
            query_string.append(idx_gyy);
            query_string.append("','");
            query_string.append(idx_gyz);
            query_string.append("','");
            query_string.append(idx_acx);
            query_string.append("','");
            query_string.append(idx_acy);
            query_string.append("','");
            query_string.append(idx_acz);
            query_string.append("','");
            query_string.append(idx_max);
            query_string.append("','");
            query_string.append(idx_may);
            query_string.append("','");
            query_string.append(idx_maz);
            query_string.append("');");
            input.exec(query_string);
            database.commit();
        }
        return 1;
    }


    bool  MainWindow::json_to_DB_can(string path){

        QSqlQuery input(database);
        database.transaction();
        input.exec("create table CAN_DATA(token text,handle text,handle_ac text,speed text);"); // *****Set table and column*****
        database.commit();

        Json::Value Can_datas;
        ifstream scene_in(path.c_str());
        if(scene_in.is_open()) scene_in>>Can_datas;

        QString temp1;
        QString temp2;
        QString temp3;

        for(int i=0; i<Can_datas.size(); i++)
        {
            
            temp1=QString::fromLocal8Bit((Can_datas[i]["Handle_Angle"].asString()).c_str());
            temp2=QString::fromLocal8Bit((Can_datas[i]["Handle_accelaration"].asString()).c_str());
            temp3=QString::fromLocal8Bit((Can_datas[i]["Speed"].asString()).c_str());

            database.transaction();
            QString query_string;
            query_string.append("insert into CAN_DATA values('"); // *****Set table*****
            query_string.append(temp1);
            query_string.append("','");
            query_string.append(temp2);
            query_string.append("','");
            query_string.append(temp3);
            query_string.append("');");
            input.exec(query_string);
            database.commit();
        }
        return 1;
    }

