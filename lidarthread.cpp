#include "lidarthread.h"

lidarThread::lidarThread(QObject* parent) : QThread(parent)
{
    cloud.reset( new pcl::PointCloud<pcl::PointXYZ>);
}

void lidarThread::run(){
    path = dir+"/LiDAR/i30_LiDAR_ts_" + ts.getMilliTime() + ".txt";
    writeFile.open(path.c_str());

    std::shared_ptr<OS1::client> cli;
    if (do_config) {
        std::cout << "Configuring sensor: " << os1_host
                  << " UDP Destination:" << os1_udp_dest << std::endl;
        cli = ouster::OS1::init_client(os1_host, os1_udp_dest, mode,
              ouster::OS1::TIME_FROM_INTERNAL_OSC, lidar_port, imu_port);
    }
    uint8_t lidar_buf[ouster::OS1::lidar_packet_bytes + 1];
    if (do_config) metadata = OS1::get_metadata(*cli);
    ouster::OS1::sensor_info info = OS1::parse_metadata(metadata);
    std::vector<double> xyz_lut = OS1::make_xyz_lut(W, H, info.beam_azimuth_angles, info.beam_altitude_angles);
    int cnt_ok = 0;

    while (!stop_flag) {
            OS1::client_state st = OS1::poll_client(*cli);
            if (st & OS1::client_state::LIDAR_DATA) {
                if (OS1::read_lidar_packet(*cli, lidar_buf)){
                    WritePCD(xyz_lut, lidar_buf);
                }
                if(cnt_ok == 10){
                    emit connectedOK();
                }
            }

            if(count == W*H){
                std::string ch_ts = ts.getMilliTime();
                std::string name = dir+"/LiDAR/PCD/i30_LiDAR_" + ch_ts + ".pcd";
                pcl::io::savePCDFile(name, *cloud, true);

                emit send_lidar(cloud); //emit signal
                if(writeFile.is_open()){
                    writeFile << ch_ts << "\n";
                }
                cloud.reset( new pcl::PointCloud<pcl::PointXYZ>);
                count = 0;
            }
            //QCoreApplication::processEvents();
            cnt_ok++;
    }
}

void lidarThread::get_dir(QString dir_str){
    dir = dir_str.toStdString();
}
void lidarThread::stop(){
    stop_flag = true;
    writeFile.close();
}


void lidarThread::WritePCD(std::vector<double> xyz_lut, uint8_t* buf){
    //std::cout<<"WritePCD"<<std::endl;
    for (int icol = 0; icol < OS1::columns_per_buffer; icol++) {
        //std::cout<<"for"<<std::endl;
        const uint8_t* col_buf = OS1::nth_col(icol, buf);
        const uint16_t m_id = OS1::col_measurement_id(col_buf);
        const int idx = H * m_id;

        for (uint8_t ipx = 0; ipx < H; ipx++) {
            //std::cout<<"second for"<<std::endl;
            const uint8_t* px_buf = OS1::nth_px(ipx, col_buf);
            uint32_t r = OS1::px_range(px_buf);
            int ind = 3 * (idx + ipx);
            pcl::PointXYZ LiDAR;
            LiDAR.x = r * 0.001f * xyz_lut[ind + 0];
            LiDAR.y = r * 0.001f * xyz_lut[ind + 1];
            LiDAR.z = r * 0.001f * xyz_lut[ind + 2];
            if(count > W*H){
                break;
            }

            cloud->push_back(LiDAR);
            count++;
        }
    }

}

std::string read_metadata(const std::string& meta_file) {
    std::stringstream buf{};
    std::ifstream ifs{};
    ifs.open(meta_file);
    buf << ifs.rdbuf();
    ifs.close();

    if (!ifs) {
        std::exit(EXIT_FAILURE);
    }

    return buf.str();
}

