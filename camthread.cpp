#include "camthread.h"

camThread::camThread(QObject *parent) : QThread(parent)
{
    Compression_params.push_back(cv::IMWRITE_JPEG_QUALITY); //Select jpeg
    Compression_params.push_back(30);
}

void camThread::run(){
    std::cout<<"CAM Streaming_start"<<std::endl;

    path = dir+"/CAM/i30_CAM_ts_"+ts.getMilliTime()+".txt";
    writeFile.open(path.c_str());
    std::cout<<"The CAM_ts.txt file saved to ["<<path<<"]\n";
    cap.open(2);
    cap.read(frame);
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 4000);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 4000);
    cap.read(frame);

    if( !cap.isOpened() )
          QThread::msleep(10);

    while(!stop_flag){
        cap >> frame;

        string m_time = ts.getMilliTime();
        const char * now_time = ts.p_time();
        //sprintf(buf,"/home/kanakim/Documents/CAM/JPG/i30_CAM_%s.jpg", now_time);
        string save_path = dir+"CAM/JPG/i30_CAM_"+m_time+".jpg";
        string tmp = "\n";

        cvtColor(frame, mat,cv::COLOR_BGR2RGB);
        QImage image(mat.size().width, mat.size().height, QImage::Format_RGB888);
        memcpy(image.scanLine(0), mat.data, static_cast<size_t>(image.width() * image.height() * frame.channels()));
        emit send_qimage(image);

        //wirteFile.write(now_time, m_time.size());
        //wirteFile.write(tmp.c_str(), tmp.size());
        if(writeFile.is_open()){
            writeFile << m_time << "\n";
        }
        imwrite(save_path.c_str(), frame, Compression_params);
        
        QThread::msleep(10);
        QCoreApplication::processEvents();
    }
}

void camThread::get_dir(std::string dir_str){
    dir = dir_str;
}
void camThread::stop(){
    stop_flag = true;
    writeFile.close();
    cap.release();
}
