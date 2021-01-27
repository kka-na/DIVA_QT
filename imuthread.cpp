#include "imuthread.h"

imuThread::imuThread(QObject *parent) : QThread(parent)
{	


}

class IMUdata {
public:
    float gyrox, gyroy, gyroz, magx, magy, magz, accelx, accely, accelz;
};


void imuThread::run(){
	path = dir+"/IMU/i30_IMU_"+ts.getMilliTime()+".csv";
    writeFile.open(path.c_str());
    std::cout<<"The IMU.csv file saved to ["<<path<<"]\n";

    mscl::Connection connection = mscl::Connection::Serial("/dev/ttyACM1", 115200);
    mscl::InertialNode node =  mscl::InertialNode(connection);

    while(!stop_flag){

        mscl::MipDataPackets packets = node.getDataPackets(500);
        IMUdata temp;

    	for(mscl::MipDataPacket packet : packets){ //

            int count = 0;
            packet.descriptorSet();
            mscl::MipDataPoints points = packet.data();

            for(mscl::MipDataPoint dataPoint : points)
            {
                const char* cName = dataPoint.channelName().c_str();
                
                if(strcmp("scaledAccelX", cName) == 0) {
                    count = 9;
                    temp.accelx = dataPoint.as_float();
                    accel_x = temp.accelx;
                }

                if(count == 8) {
                    temp.accely = dataPoint.as_float();
                    accel_y = temp.accely;
                }
                if(count == 7) {
                    temp.accelz = dataPoint.as_float();
                    accel_z = temp.accelz;
                }
                if(count == 6) temp.gyrox = dataPoint.as_float();
                if(count == 5) temp.gyroy = dataPoint.as_float();
                if(count == 4) temp.gyroz = dataPoint.as_float();
                if(count == 3) temp.magx = dataPoint.as_float();
                if(count == 2) temp.magy = dataPoint.as_float();
                if(count == 1) temp.magz = dataPoint.as_float();

                count--;
                mtime = ts.p_time();
                if(count == 0) {
                    sprintf(fp, "%s,%f,%f,%f,%f,%f,%f,%f,%f,%f\n", mtime, temp.gyrox, temp.gyroy, temp.gyroz, temp.magx, temp.magy, temp.magz, temp.accelx, temp.accely, temp.accelz);
                    emit send_acc(accel_x, accel_y, accel_z);
                    writeFile.write(fp, strlen(fp));
                    break;
                }
            }
            if(count == 0){
                break;
            }
        }
        QThread::msleep(40);

    }
}

void imuThread::stop(){
	stop_flag = true;
	writeFile.close();
}

void imuThread::get_dir(QString dir_str){
	dir = dir_str.toStdString();
}
