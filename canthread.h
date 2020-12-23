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
    CANdata(){
        handle_angle = 0;
        handle_accel = 0;
        vehicle_speed = 0;
        gear = 0;
        turn_indicator = 2;
    }
    int handle_angle, handle_accel, vehicle_speed,gear, turn_indicator;
};


class canThread : public QThread
{
	Q_OBJECT
public:
    canThread(QObject *parent = 0);
    Timestamp ts;
    ofstream writeFile;

    bool stop_flag = false;

    QCanBusDevice *device;

    typedef QPair<QCanBusDevice::ConfigurationKey, QVariant> ConfigurationItem;

    struct Settings {
        QString pluginName;
        QString deviceInterfaceName;
        QList<ConfigurationItem> configurations;
        bool useConfigurationEnabled = false;
    };


    std::string path;

    vector<vector<string>> can_frame;

     int frame_data_payload_startidx=16;

     string frame_data;

     string frame_data_timestamp;
     string frame_data_id;
     string frame_data_dlc;
     string frame_data_payload_temp;
     string frame_bin;
     int speed_temp = 0;
     int fuel_temp = 0;
     int battery_temp = 0;
     int wheel_temp = 0;
     vector<string> frame_data_payload;

     QString speed_qstring;
     QString handle_qstring;
     QString handle_qstring2;

     int handle_int;
     int handle_int2;
     int speed_int;

     string result_can;

     fstream fs;
     string frame_id_string;

signals:
	void send_speed(int);
	void send_handle(QString,  QString);
	void send_gear(int);
	void send_turn(int);
	void send_end();


public slots:
	void stop();

private slots:
    string hexToBinary(string, int);

private:
	void run() override;
    qint64 numberFramesWritten = 0;
   
    Settings currentSettings;
    std::unique_ptr<QCanBusDevice> canDevice;
    QLabel *status = nullptr;
    QLabel *written = nullptr;
    QTimer *timer;

};

#endif // CANTHREAD_H
