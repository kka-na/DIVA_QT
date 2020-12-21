#include "camthread.h"

camThread::camThread(QObject *parent) : QThread(parent)
{
    Compression_params.push_back(cv::IMWRITE_JPEG_QUALITY); //Select jpeg
    Compression_params.push_back(30);
}

void camThread::run(){
    std::cout<<"CAM Streaming_start"<<std::endl;

    path = "/home/kanakim/Documents/CAM/i30_CAM_ts_"+ts.getMilliTime()+".txt";
    wirteFile.open(path.c_str());
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
        sprintf(buf,"/home/kanakim/Documents/CAM/JPG/i30_CAM_%s.jpg", now_time);
        string tmp = "\n";

        //opencv uses bgr order, need to conver it to rgb
        cvtColor(frame, mat,cv::COLOR_BGR2RGB);
        //image is created according to mat dimensions
        QImage image(mat.size().width, mat.size().height, QImage::Format_RGB888);
        memcpy(image.scanLine(0), mat.data, static_cast<size_t>(image.width() * image.height() * frame.channels()));
        emit send_qimage(image);

        wirteFile.write(now_time, m_time.size());
        wirteFile.write(tmp.c_str(), tmp.size());
        imwrite(buf, frame, Compression_params);
        
        QThread::msleep(10);
        QCoreApplication::processEvents();
    }
}

void camThread::stop(){
    stop_flag = true;
    wirteFile.close();
    cap.release();
}
