#include "storingdb.h"

storingDB::storingDB(string fpath){
    folder_path = fpath;
    string logPath = fpath+"/JSON/log.json";
    string scenePath = fpath+"/JSON/scene.json";
    string framePath = fpath+"/JSON/frame.json";
    string frameDataPath = fpath+"/JSON/frame_data.json";
    string gpsDataPath = fpath+"/JSON/gps_data.json";
    string imuDataPath = fpath+"/JSON/imu_data.json";
    string canDataPath = fpath+"/JSON/can_data.json";

    if(this->settingDB()){
        this->toLogDB(logPath);
        this->toSceneDB(scenePath);
        this->toFrameDB(framePath);
        this->toFrameDataDB(frameDataPath);
        this->toGPSDataDB(gpsDataPath);
        this->toIMUDataDB(imuDataPath);
        this->toCANDataDB(canDataPath);
    }else{
        std::cout<<"Can't connect to DB"<<std::endl;
    }

}


bool storingDB::settingDB(){
        database=QSqlDatabase::addDatabase("QPSQL7");
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

void  storingDB::toLogDB(string path){

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

    }



    void storingDB::toSceneDB(string path){

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

    }


    void  storingDB::toFrameDB(string path){

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

    }

  void storingDB::toFrameDataDB(string path){

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

    }


void  storingDB::toGPSDataDB(string path){

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

    }

    void  storingDB::toIMUDataDB(string path){

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

    }


void  storingDB::toCANDataDB(string path){

        QSqlQuery input(database);
        database.transaction();
        input.exec("create table CAN_DATA(token text,handle_angle text,handle_acc text,speed text, gear text, turn_indicator text);"); // *****Set table and column*****
        database.commit();

        Json::Value Can_datas;
        ifstream scene_in(path.c_str());
        if(scene_in.is_open()) scene_in>>Can_datas;

        QString temp1;
        QString temp2;
        QString temp3;
        QString temp4;
        QString temp5;
        QString temp6;

        for(int i=0; i<Can_datas.size(); i++)
        {
            temp1=QString::fromLocal8Bit((Can_datas[i]["Gear"].asString()).c_str());
            temp2=QString::fromLocal8Bit((Can_datas[i]["Handle_Angle"].asString()).c_str());
            temp3=QString::fromLocal8Bit((Can_datas[i]["Handle_accelaration"].asString()).c_str());
            temp4=QString::fromLocal8Bit((Can_datas[i]["Speed"].asString()).c_str());
            temp5=QString::fromLocal8Bit((Can_datas[i]["token"].asString()).c_str());
            temp6=QString::fromLocal8Bit((Can_datas[i]["Turn"].asString()).c_str());

            database.transaction();
            QString query_string;
            query_string.append("insert into CAN_DATA values('"); // *****Set table*****
            query_string.append(temp5);
            query_string.append("','");
            query_string.append(temp2);
            query_string.append("','");
            query_string.append(temp3);
            query_string.append("','");
            query_string.append(temp4);
            query_string.append("','");
            query_string.append(temp1);
            query_string.append("','");
            query_string.append(temp6);
            query_string.append("');");
            input.exec(query_string);
            database.commit();
        }

    }
