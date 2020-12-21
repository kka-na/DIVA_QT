#ifndef STORING_TO_DB_H
#define STORING_TO_DB_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QFile>
#include <QString>
#include <QDebug>
#include <QTextStream>

#include "jsoncpp/json/json.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <ctime>

class Storing_To_DB{
public:
	QSqlDatabase database;

	Storing_To_DB(){
		setting_db();
	}

	void setting_db(){
		// *****Set DB Information*****
	    QSqlDatabase database=QSqlDatabase::addDatabase("QPSQL7");
	    database.setDatabaseName("diva");
	    database.setHostName("localhost");
	    database.setUserName("diva");
	    database.setPassword("password");
	    database.setPort(5432);
	    if (database.open())
	        qDebug() << "Connection Successful";
	    else
	        qDebug() << "Connection Failed!";

	    qDebug() << "db connection" << database.open();
	}

	bool json_to_DB_log(string path){

	    QSqlQuery input(database);
	    database.transaction();
	    input.exec("create table LOG(token text,date_captured text,vehicle text );"); // *****Set table and column*****
	    database.commit();
	  
	    Json::Value Logs;
	    ifstream in(path.c_str());
    	if(in.is_open()) in >> Logs;

    	QString temp1;
    	QString temp2;
    	QString temp3;

	    for(int i=1;i<Logs.size();i++)
	    {
	        temp1=QString::fromLocal8Bit((Logs[i]["token"].asString()).c_str());
	        temp2=QString::fromLocal8Bit((Logs[i]["date_captured"].asString()).c_str());
	        temp3=QString::fromLocal8Bit((Logs[i]["vehicle"].asString()).c_str());

	        database.transaction();
	        QString query_string;
	        query_string.append("insert into LOG values('"); // *****Set table*****
	        query_string.append(temp1);
	        query_string.append(",");
	        query_string.append(temp2);
	        query_string.append(",");
	        query_string.append(temp3);
	        query_string.append("');");
	        input.exec(query_string);
	        database.commit();
	    }
	    return 1;
	}



	bool json_to_DB_scene(string path){

	    QSqlQuery input(database);
	    database.transaction();
	    input.exec("create table SCENE(first_frame_token text,log_token text, nbr_frame text);"); // *****Set table and column*****
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
	        temp3=QString::fromLocal8Bit((Scenes[i]["nbr_frame"].asString()).c_str());

	        database.transaction();
	        QString query_string;
	        query_string.append("insert into SCENE values('"); // *****Set table*****
	        query_string.append(temp1);
	        query_string.append(",");
	        query_string.append(temp2);
	        query_string.append(",");
	        query_string.append(temp3);
	        query_string.append("');");
	        input.exec(query_string);
	        database.commit();
	    }
	    return 1;
	}


	bool json_to_DB_frame(string path){

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
	        query_string.append(",");
	        query_string.append(temp2);
	        query_string.append("');");
	        input.exec(query_string);
	        database.commit();
	    }
	    return 1;
	}

	bool json_to_DB_frame_data(string path){

	    QSqlQuery input(database);
	    database.transaction();
	    input.exec("create table FRAME_DATA(frame_token text,frame_data_token text,file_format text, file_name text);"); // *****Set table and column*****
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
	        temp1=QString::fromLocal8Bit((Frame_datas[i]["frame_token"].asString()).c_str());
	        temp2=QString::fromLocal8Bit((Frame_datas[i]["frame_data_token"].asString()).c_str());
	        temp3=QString::fromLocal8Bit((Frame_datas[i]["file_format"].asString()).c_str());
	        temp4=QString::fromLocal8Bit((Frame_datas[i]["file_name"].asString()).c_str());

	        database.transaction();
	        QString query_string;
	        query_string.append("insert into FRAME_DATA values('"); // *****Set table*****
	        query_string.append(temp1);
	        query_string.append(",");
	        query_string.append(temp2);
	        query_string.append(",");
	        query_string.append(temp3);
	        query_string.append(",");
	        query_string.append(temp4);
	        query_string.append("');");
	        input.exec(query_string);
	        database.commit();
	    }
	    return 1;
	}


	bool json_to_DB_gps(string path){

	    QSqlQuery input(database);
	    database.transaction();
	    input.exec("create table GPS_DATA(token text,latitude text, longitude text);"); // *****Set table and column*****
	    database.commit();

	    Json::Value Gps_datas;
	    ifstream scene_in(path.c_str());
    	if(scene_in.is_open()) scene_in>>Gps_datas;

    	QString temp1;
    	QString temp2;
    	QString temp3;

	    for(int i=0; i<Gps_datas.size(); i++)
	    {
	        temp1=QString::fromLocal8Bit((Gps_datas[i]["token"].asString()).c_str());
	        temp2=QString::fromLocal8Bit((Gps_datas[i]["latitude"].asString()).c_str());
	        temp3=QString::fromLocal8Bit((Gps_datas[i]["longitude"].asString()).c_str());

	        database.transaction();
	        QString query_string;
	        query_string.append("insert into GPS_DATA values('"); // *****Set table*****
	        query_string.append(temp1);
	        query_string.append(",");
	        query_string.append(temp2);
	        query_string.append(",");
	        query_string.append(temp3);
	        query_string.append("');");
	        input.exec(query_string);
	        database.commit();
	    }
	    return 1;
	}

	bool json_to_DB_imu(string path){

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
	    	idx_token = QString::fromLocal8Bit((Imu_datas[i]["token"].asString()).c_str());
	        idx_gyx =  QString::fromLocal8Bit((Imu_datas[i]["gyroscope"][0].asString()).c_str());
            idx_gyy =  QString::fromLocal8Bit((Imu_datas[i]["gyroscope"][1].asString()).c_str());
            idx_gyz =  QString::fromLocal8Bit((Imu_datas[i]["gyroscope"][2].asString()).c_str());
            idx_acx =  QString::fromLocal8Bit((Imu_datas[i]["acceleration"][0].asString()).c_str());
            idx_acy =  QString::fromLocal8Bit((Imu_datas[i]["acceleration"][1].asString()).c_str());
            idx_acz =  QString::fromLocal8Bit((Imu_datas[i]["acceleration"][2].asString()).c_str());
            idx_max =  QString::fromLocal8Bit((Imu_datas[i]["magnetic"][0].asString()).c_str());
            idx_may =  QString::fromLocal8Bit((Imu_datas[i]["magnetic"][1].asString()).c_str());
            idx_maz =  QString::fromLocal8Bit((Imu_datas[i]["magnetic"][2].asString()).c_str());

	        database.transaction();
	        QString query_string;
	        query_string.append("insert into IMU_DATA values('"); // *****Set table*****
	        query_string.append(idx_token);
	        query_string.append(",");
	        query_string.append(idx_gyx);
	        query_string.append(",");
	        query_string.append(idx_gyy);
	        query_string.append(",");
	        query_string.append(idx_gyz);
	        query_string.append(",");
	        query_string.append(idx_acx);
	        query_string.append(",");
	        query_string.append(idx_acy);
	        query_string.append(",");
	        query_string.append(idx_acz);
	        query_string.append(",");
	        query_string.append(idx_max);
	        query_string.append(",");
	        query_string.append(idx_may);
	        query_string.append(",");
	        query_string.append(idx_maz);
	        query_string.append("');");
	        input.exec(query_string);
	        database.commit();
	    }
	    return 1;
	}


	

#endif // STORING_TO_DB_H