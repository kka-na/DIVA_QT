#include "gpsthread.h"

struct termios stOldState;
struct termios stNewState;

gpsThread::gpsThread(QObject *parent) : QThread(parent)
{
    
}

void gpsThread::run(){
    std::cout<<"GPS streaming_start"<<std::endl;
    
    path = dir+"/GPS/i30_GPS_"+ts.getMilliTime()+".csv";
    writeFile.open(path.c_str());
    std::cout<<"The GPS.csv file saved to ["<<path<<"]\n";

    iDev = open(GPSDEVICE, O_RDWR | O_NOCTTY);
    if(0>iDev){
        std::cout<<"error on open device"<<std::endl;
        exit(-1);
    }
    cs.init_serial(iDev, BAUDRATE);

    while(!stop_flag){
        const char *nmea[100];
        char nnnmea[256];

        iRet = read(iDev, cBuff, 526);
        cBuff[iRet] = 0;

        char *ptr = stm.strtok_f(cBuff, ',');
        int cnt = 0;
        if(ptr != NULL && strcmp(ptr,"$GNGGA") == 0 ){
            while(ptr != NULL){
                 if(cnt == 1){
                    nmea[1] = ts.p_time();
                }else{
                    nmea[cnt] = ptr;
                }
                cnt++;
                ptr = stm.strtok_f(NULL, ',');
            }
            sprintf(nnnmea,"%s,%s,%s,%s,%s,%s,%s\n", nmea[1], nmea[2], nmea[3], nmea[4], nmea[5], nmea[9], nmea[10]);
            writeFile.write(nnnmea, strlen(nnnmea));
            if(strlen(nmea[2]) < 1 || strlen(nmea[4]) < 1){
                latitude = "0"; longitude="0";
            }else{
                latitude = to_string(Convert_to_dd(stold(nmea[2])));
                longitude = to_string(Convert_to_dd(stold(nmea[4])));
            }
            
            emit send_ll(QString::fromLocal8Bit(latitude.c_str()), QString::fromLocal8Bit(longitude.c_str()));
        }
        //QCoreApplication::processEvents();
    }
}

void gpsThread::stop(){
    stop_flag = true;
    emit send_end();
    writeFile.close();
    cs.close_serial(iDev);
}

void gpsThread::get_dir(QString dir_str){
    dir = dir_str.toStdString();
}

long double gpsThread::Convert_to_dd(long double raw){
    int dd = (int)(raw/100);
    long double ddddd = raw - (long double)(dd*100);
    ddddd /= 60;

    return (long double)dd+ddddd;
}
