#ifndef MAKEJSON_H
#define MAKEJSON_H

#include <QDir>
#include <iostream>

#include "indexandtimes.h"
#include "readfiles.h"
#include "jsoncpp/json/json.h"

class MakeJson
{
public:
    MakeJson(string fpath);
    

    string dir;

    IndexAndTimes *iat;

    int gps_idx;

    int gps_start;
    int gps_last;
    int cam_start;
    int lidar_start;
    int imu_start;
    int can_start;

    int gps_csv_size;
    int imu_csv_size;
    int cam_txt_size;
    int lidar_txt_size;
    int can_csv_size;

    int scene_count;
    int cam_sensors;
    int this_frame_start;
    int this_log_start;
    int this_frame_data_start;

    string generate_token();
    string generate_token_2();
    string generate_timestamp();
    bool Log(int car_id);
    bool Sensor(int sensors_num);
    bool Scene();
    bool Frame();
    bool Frame_Data();
    bool Gps_Data();
    bool Imu_Data();
    bool Can_Data();

    bool Check_Directory();

    void Get_LLA(int gps_idx);
    long double Convert_to_dd(long double raw);
    void Get_GAM(int imu_idx);
    void Get_HSGT(int can_idx);

    //~GPS Datum~
    string latitude;
    string longitude;
    string altitude;
    //~IMU Datum~
    string gyro_x;string gyro_y; string gyro_z;
    string accel_x;string accel_y;string accel_z;
    string mag_x; string mag_y; string mag_z;
    //~CAN Datum~
    string handle_angle;
    string handle_accelaration;
    string speed;
    string gear;
    string turn;

    int num_of_scene = 0;

};

#endif // MAKEJSON_H
