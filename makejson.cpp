#include "makejson.h"

MakeJson::MakeJson(string fpath)
{

    dir = fpath;

    iat = new IndexAndTimes(dir);

    gps_csv_size = iat->gps_csv.size();
    cam_txt_size = iat->cam_txt.size();
    lidar_txt_size = iat->lidar_txt.size();
    imu_csv_size = iat->imu_csv.size();
    can_csv_size = iat->can_csv.size();

    gps_start = iat->get_start_indexes()[1];
    cam_start = iat->get_start_indexes()[2];
    lidar_start = iat->get_start_indexes()[3];
    imu_start = iat->get_start_indexes()[4];
    can_start = iat->get_start_indexes()[5];

    cam_sensors = 2; // if 2 -> cam, lidar
    scene_count = iat->number_of_frames() / 200;
    if(iat->number_of_frames() % 200 > 0)
        scene_count++;
    gps_last = iat->gps_last;

    this_frame_start = 0;
    this_log_start = 0;
}



string MakeJson::generate_token(){
    srand((unsigned int)time(NULL));
    char hex_characters[] ="0123456789abcdef";
    char* token_char = new char[16]; //to store values in for loop
    string token_string="";

    for (size_t j = 0; j < 16; j++){
        token_char[j] = hex_characters[rand() % 16];
        token_string = token_string + token_char[j];
    }

    delete[] token_char;
    return token_string;
}

string MakeJson::generate_token_2()
{
    char hex_characters[] ="0123456789abcdef";
    char* token_char = new char[16]; //to store values in for loop
    string token_string="";

    for (size_t j = 0; j < 16; j++){
        token_char[j] = hex_characters[rand() % 16];
        token_string = token_string + token_char[j];
    }

    delete[] token_char;
    return token_string;
}

string MakeJson::generate_timestamp()
{
    time_t system_time;
    struct tm* systime;
    system_time = time(NULL);
    systime = localtime(&system_time);

    string tm_year = to_string(systime->tm_year + 1900);
    string tm_month = to_string(systime->tm_mon+1);
    string tm_date = to_string(systime->tm_mday);
    if(tm_date.size() == 1){
        tm_date = "0"+tm_date;
    }

    string timestamp;
    timestamp = tm_year + tm_month + tm_date;

    return timestamp;
}
Json::Value Logs;
bool MakeJson::Log(int car_id)
{
    string path = dir+"/JSON/log.json";
    ifstream in(path.c_str());
    if(in.is_open()) in >> Logs;

    Json::Value log;

    this_log_start = Logs.size();

    string vehicles[2] = { "i30", "n004" };
    string vehicle = vehicles[car_id]; //i30
    string date = generate_timestamp();

    log["token"] = generate_token();
    log["vehicle"] = vehicle;
    log["date_captured"] = date+"_"+to_string(this_log_start);
    log["location"] = "Incheon, South Korea";

    Logs.append(log);
    log.clear();

    Json::StyledWriter writer;
    ofstream out(path.c_str());
    out << writer.write(Logs);
    out.close();
    return true;
}

Json::Value Sensors;
bool MakeJson::Sensor(int sensors_num)
{
    string path = dir+"/JSON/sensor.json";
    Json::Value sensor;
    string sensor_name;

    for(int i=0; i<=sensors_num; i++){
        string token = generate_token_2();
        if(i ==1)
            sensor_name = "GPS";
        else if(i==2)
            sensor_name = "CAM";
        else if(i==3)
            sensor_name = "LiDAR";
        else if(i==4)
            sensor_name = "IMU";
        else if(i==5)
            sensor_name = "CAN";
        else{
            sensor_name = "NULL";
            token = "NULL";
        }
        sensor["sensor_token"] = token;
        sensor["Sensor"] = sensor_name;

        Sensors.append(sensor);
        sensor.clear();
    }

    Json::StyledWriter writer;
    ofstream out(path.c_str());
    out << writer.write(Sensors);
    out.close();
    return true;
}

Json::Value Frames;
bool MakeJson::Frame()
{
    string path = dir+"/JSON/frame.json";
    ifstream in(path.c_str());
    if(in.is_open()) in >> Frames;

    int frame_start = gps_start;

    gps_idx = gps_start;

    this_frame_start = Frames.size(); //for frame_data's frame_token

    int frame_idx = frame_start;

    Json::Value a_frame;

    for(int i=0; i<scene_count; i++){
        string token_prev = "";
        string token_curr = generate_token_2();

        while(1){

            if(frame_idx > frame_start+199){
                frame_start = frame_idx;
                break;
            }else if(frame_idx > gps_last){
                break;
            }

            string timestamp = iat->get_gps_timestamp(gps_idx);
            string token_next = generate_token_2();

            a_frame["frame index = "]=frame_idx;
            a_frame["frame_token"] = token_curr;
            a_frame["timestamp"] = timestamp;
            a_frame["token_prev"] = token_prev;


            if(frame_idx < gps_last+1 && frame_idx == frame_start+199)
                a_frame["token_next"] = "";
            else if(frame_idx < gps_last+1 && frame_idx == gps_last)
                a_frame["token_next"] = "";
            else
                a_frame["token_next"] = token_next;

            Frames.append(a_frame);
            a_frame.clear();

            token_prev = token_curr;
            token_curr = token_next;

            gps_idx++;
            frame_idx++;
        }

    }

    Json::StyledWriter writer;
    ofstream out(path.c_str());
    out << writer.write(Frames);
    out.close();
    return true;
}

Json::Value Scenes;
bool MakeJson::Scene()
{
    string path = dir+"/JSON/scene.json";
    ifstream in(path.c_str());
    if(in.is_open()) in >> Scenes;

    Json::Value a_scene;
    int scene_idx = this_frame_start;
    int frames = 200;

    for(int i=0; i<scene_count; i++){
        a_scene["scene_token"] = generate_token_2();
        a_scene["log_token"] = Logs[this_log_start]["token"];

        if(((this_frame_start+iat->number_of_frames()+1) - (scene_idx)) < 200)
            frames = (this_frame_start+iat->number_of_frames()+1)-(scene_idx);


        a_scene["nbr_frames"] = frames;
        a_scene["first_frame_token"] = Frames[scene_idx]["frame_token"];
        a_scene["last_frame_token"] = Frames[scene_idx+(frames-1)]["frame_token"];

        Scenes.append(a_scene);
        a_scene.clear();
        scene_idx+=200;
    }

    Json::StyledWriter writer;
    ofstream out(path.c_str()); //ios::app append
    out <<  writer.write(Scenes);
    out.close();
    return true;
}



Json::Value Frame_data;
bool MakeJson::Frame_Data()
{
    string path =dir+"/JSON/frame_data.json";
    ifstream in(path.c_str());
    if(in.is_open()) in >> Frame_data;
    Json::Value frame_datum;

    int frame_start = gps_start;
    int frame_idx = frame_start;
    int frame_data_idx = frame_start;

    this_frame_data_start = Frame_data.size();

    int cam_idx = cam_start;
    int lidar_idx = lidar_start;


    string ts_of_cam_by_idx;
    string ts_of_lidar_by_idx;

    string cam_path =  dir+"/CAM/JPG/i30_CAM_";
    string lidar_path = dir+"/LiDAR/PCD/i30_LiDAR_";


    for(int i=0; i<scene_count; i++){
        string token_prev1 = "";
        string token_prev2 = "";
        string token_curr1 = generate_token_2();
        string token_curr2 = generate_token_2();


        while(1){
            if(frame_data_idx > frame_start+199){
                frame_start = frame_data_idx;
                break;
            }else if(frame_data_idx > gps_last){
                break;
            }

            string gps_ts = iat->get_gps_timestamp(frame_data_idx);

            string token_next;

            for(int j=0; j<cam_sensors; j++){
                if(j==0){//cam
                    cam_idx = iat->find_cam_idx_by_ts(cam_idx, gps_ts);
                    if(cam_idx > cam_txt_size-1) continue;
                    ts_of_cam_by_idx = iat->get_cam_timestamp(cam_idx);
                    token_next = generate_token_2();
                    frame_datum["frame_data_idx"] =frame_data_idx;
                    frame_datum["frame_data_token"] = token_curr1;
                    frame_datum["frame_token"] = Frames[this_frame_start]["frame_token"];
                    frame_datum["gps_token"] = token_curr1;
                    frame_datum["imu_token"] = token_curr1;
                    frame_datum["can_token"] = token_curr1;
                    frame_datum["sensor_token"] = Sensors[2]["sensor_token"];
                    ts_of_cam_by_idx = iat->get_cam_timestamp(cam_idx);
                    frame_datum["filename"] = cam_path+ts_of_cam_by_idx+".jpg";
                    frame_datum["fileformat"] = "jpeg";
                    frame_datum["timestamp"] = ts_of_cam_by_idx;
                    frame_datum["is_key_frame"] = iat->txt_sensor_is_key_frame(2,cam_idx,frame_data_idx);
                    frame_datum["prev"] = token_prev1;
                    if(frame_data_idx < gps_csv_size &&frame_data_idx ==frame_start+199)
                        frame_datum["next"] = "";
                    else if(frame_data_idx < gps_csv_size && frame_data_idx == gps_csv_size-1)
                        frame_datum["next"] = "";
                    else
                        frame_datum["next"] = token_next;

                    Frame_data.append(frame_datum);
                    frame_datum.clear();
                    //token_prev1 = token_curr1;
                    //token_curr1 = token_next;
                }


                else{//lidar
                    lidar_idx = iat->find_lidar_idx_by_ts(lidar_idx, gps_ts);
                    if(lidar_idx > lidar_txt_size-1) continue;
                    ts_of_lidar_by_idx = iat->get_lidar_timestamp(lidar_idx);
                    //token_next = generate_token_2();
                    frame_datum["frame_data_token"] = token_curr1;
                    frame_datum["frame_token"] = Frames[this_frame_start]["frame_token"];
                    frame_datum["gps_token"] = token_curr1;
                    frame_datum["imu_token"] = token_curr1;
                    frame_datum["can_token"] = token_curr1;
                    frame_datum["sensor_token"] = Sensors[3]["sensor_token"];
                    ts_of_lidar_by_idx = iat->get_lidar_timestamp(lidar_idx);
                    frame_datum["filename"] = lidar_path+ts_of_lidar_by_idx+".pcd";
                    frame_datum["fileformat"] = "pcd";

                    frame_datum["timestamp"] = ts_of_lidar_by_idx;
                    if (frame_datum["timestamp"] == Frames[i]["timestamp"])
                        frame_datum["is_key_frame"] = true;
                    else
                        frame_datum["is_key_frame"] = false;

                    frame_datum["prev"] = token_prev1;
                    if(frame_data_idx < gps_csv_size && frame_data_idx == frame_start+199)
                        frame_datum["next"] = "";
                    else if(frame_data_idx < gps_csv_size && frame_data_idx == gps_csv_size-1)
                        frame_datum["next"] = "";
                    else
                        frame_datum["next"] = token_next;

                    Frame_data.append(frame_datum);
                    frame_datum.clear();
                    token_prev1 = token_curr1;
                    token_curr1 = token_next;
                }

            }

            frame_data_idx++;
            this_frame_start++;

        }

    }

    Json::StyledWriter writer;
    ofstream out(path.c_str());
    out << writer.write(Frame_data);
    out.close();
    return true;
}

Json::Value Gps_data;
bool MakeJson::Gps_Data()
{
    string path = dir+"/JSON/gps_data.json";
    ifstream in(path.c_str());
    if(in.is_open()) in >> Gps_data;
    Json::Value gpses;

    int gps_data_start = gps_start;
    int gps_data_idx = gps_data_start;
    int where_frame_started = this_frame_data_start;

    for(int i=0; i<scene_count; i++){
        while(1){

            if(gps_data_idx > gps_data_start+199){
                gps_data_start = gps_data_idx;
                break;
            }else if(gps_data_idx > gps_last){
                break;
            }
            gpses["token"] = Frame_data[where_frame_started]["frame_data_token"];
            gpses["sensor_token"] = Sensors[1]["sensor_token"];
            gpses["timestamp"] = iat->get_gps_timestamp(gps_data_idx);
            Get_LLA(gps_data_idx);
            gpses["latitude"] = latitude;
            gpses["longitude"] = longitude;
            gpses["altitude"] = altitude;

            Gps_data.append(gpses);
            gpses.clear();

            gps_data_idx++;
            where_frame_started += 2;
        }
    }

    Json::StyledWriter writer;
    ofstream out(path.c_str());
    out<<writer.write(Gps_data);
    //cout<<"gps write success"<<endl;
    out.close();
    return true;
}

Json::Value Imu_data;
bool MakeJson::Imu_Data()
{
    string path = dir+"/JSON/imu_data.json";
    ifstream in(path.c_str());
    if(in.is_open()) in >> Imu_data;

    Json::Value imus;
    Json::Value gyroscope;
    Json::Value acceleration;
    Json::Value magnetic;

    int imu_data_start = gps_start;
    int imu_data_idx = imu_data_start;
    int where_frame_started = this_frame_data_start;

    for(int i=0; i<scene_count; i++){

        while(1){
            if(imu_data_idx > imu_data_start+199){
                imu_data_start = imu_data_idx;
                break;
            }else if(imu_data_idx > gps_last){
                break;
            }

            imus["token"] = Frame_data[where_frame_started]["frame_data_token"];
            imus["sensor_token"] = Sensors[4]["sensor_token"];
            imus["timestamp"] = iat->get_imu_timestamp(imu_data_idx);
            Get_GAM(imu_data_idx);
            gyroscope.append(gyro_x); gyroscope.append(gyro_y); gyroscope.append(gyro_z);
            imus["gyroscope"] = gyroscope;
            acceleration.append(accel_x); acceleration.append(accel_y); acceleration.append(accel_z);
            imus["acceleration"] = acceleration;
            magnetic.append(mag_x); magnetic.append(mag_y); magnetic.append(mag_z);
            imus["magnetic"] = magnetic;

            Imu_data.append(imus);
            gyroscope.clear();
            acceleration.clear();
            magnetic.clear();
            imus.clear();

            imu_data_idx++;
            where_frame_started+=2;

        }

    }

    Json::StyledWriter writer;
    ofstream out(path.c_str());
    out<<writer.write(Imu_data);
    out.close();
    return true;
}

Json::Value Can_data;
bool MakeJson::Can_Data()
{
    string path = dir+"/JSON/can_data.json";
    ifstream in(path.c_str());
    if(in.is_open()) in >> Can_data;
    Json::Value cans;

    int gps_data_start = gps_start;
    int gps_data_idx = gps_data_start;

    int can_data_start = can_start;
    int can_data_idx = can_data_start;
    int can_data_real_idx = can_data_start;

    int where_frame_started = this_frame_data_start;

    for(int i=0; i<scene_count; i++){
        while(1){
            if(can_data_idx > can_data_start+199){
                can_data_start = can_data_idx;
                break;
            }else if(can_data_idx > gps_last){
                break;
            }

            cans["token"] = Frame_data[where_frame_started]["frame_data_token"];
            cans["sensor_token"] = Sensors[5]["sensor_token"];
            cans["timestamp"] = iat->get_can_timestamp(can_data_idx);
            Get_HSGT(can_data_idx);
            cans["Handle_Angle"] = handle_angle;
            cans["Handle_accelaration"] = handle_accelaration;
            cans["Speed"] = speed;
            cans["Gear"] = gear;
            cans["Turn"] = turn;
            Can_data.append(cans);
            cans.clear();

            gps_data_idx++;
            can_data_idx++;
            where_frame_started += 2;
        }
    }

    Json::StyledWriter writer;
    ofstream out(path.c_str());
    out<<writer.write(Can_data);
    out.close();
    return true;
}

bool MakeJson::Check_Directory()
{
    QDir root((QString::fromLocal8Bit(dir.c_str())).append("/JSON"));
    if(root.exists()) return true;
    return false;
}

void MakeJson::Get_LLA(int gps_idx){

    long double raw_latitude = stold(iat->gps_csv[gps_idx][1]); // latitude
    latitude = to_string(Convert_to_dd(raw_latitude));

    long double raw_longitude = stold(iat->gps_csv[gps_idx][3]); // longitude
    longitude = to_string(Convert_to_dd(raw_longitude));

    altitude = iat->gps_csv[gps_idx][5];

}

long double MakeJson::Convert_to_dd(long double raw){

    int dd = (int)(raw/100);
    long double ddddd = raw - (long double)(dd*100);
    ddddd /= 60;

    return (long double)dd+ddddd;
}

void MakeJson::Get_GAM(int imu_idx){ //get Zyro, Acceleration, Magnetic by index

    gyro_x = iat->imu_csv[imu_idx][1];
    gyro_y = iat->imu_csv[imu_idx][2];
    gyro_z = iat->imu_csv[imu_idx][3];
    accel_x = iat->imu_csv[imu_idx][4];
    accel_y = iat->imu_csv[imu_idx][5];
    accel_z = iat->imu_csv[imu_idx][6];
    mag_x = iat->imu_csv[imu_idx][7];
    mag_y = iat->imu_csv[imu_idx][8];
    mag_z = iat->imu_csv[imu_idx][9];

}

void MakeJson::Get_HSGT(int can_idx){

    handle_angle = iat->can_csv[can_idx][1];
    handle_accelaration = iat->can_csv[can_idx][2];
    speed = iat->can_csv[can_idx][3];
    gear = iat->can_csv[can_idx][4];
    turn = iat->can_csv[can_idx][5];
}