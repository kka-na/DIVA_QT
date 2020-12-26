#ifndef CANTHREAD_H
#define CANTHREAD_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QThread>
#include <QDebug>
#include <QCoreApplication>
#include <QCanBus>
#include <QCanBusDevice>
#include <QCanBusDeviceInfo>
#include <QCanBusFrame>

#include <iostream>
#include <cstring>


#include "Timestamp.h"

class CANdata {
public:
    CANdata(QObject *parent = 0){
        handle_angle = 0;
        handle_accel = 0;
        vehicle_speed = 0;
        gear = 0;
        turn_indicator = 2;
    }
    int handle_angle, handle_accel, vehicle_speed,gear, turn_indicator;
};


class canThread : public QObject
{
	Q_OBJECT

public:
    canThread();
    Timestamp ts;
    ofstream writeFile;

    bool stop_flag = false;

    QCanBusDevice *device;

    std::string dir;
    std::string path;

    vector<vector<string>> can_frame;

     int frame_data_payload_startidx=16;

     string frame_data;

     string frame_data_timestamp;
     string frame_data_id;
     string frame_data_dlc;
     string frame_data_payload_temp;
     string frame_bin;
    
     QString speed_qstring;
     QString handle_qstring;
     QString handle_qstring2;

     int handle_int;
     int handle_int2;
     int speed_int;

     string result_can;
     QTimer timer;
     fstream fs;
     string frame_id_string;

signals:
	void send_speed(int);
	void send_handle(QString,  QString);
	void send_gear(int);
	void send_turn(int);
	void send_end();


public slots:
    void get_dir(std::string);
	void event();
	void stop();
	void start();

private slots:
    string hexToBinary(string, int);

private:

};

#endif // CANTHREAD_H
