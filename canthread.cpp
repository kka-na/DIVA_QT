#include "canthread.h"

canThread::canThread(QObject *parent) : QThread(parent)
{
	if (QCanBus::instance()->plugins().contains(QStringLiteral("socketcan"))) {
		std::cout<<"socketcan"<<std::endl;
        QString errorString;
          device = QCanBus::instance()->createDevice(QStringLiteral("socketcan"), QStringLiteral("can0"), &errorString);
         if (!device) {
             // Error handling goes here
             qDebug() << errorString;
         }else {
             device->connectDevice();
	    }
                
     }
   			 
}

void canThread::run(){
	
    path = "/home/kanakim/Documents/CAN/i30_CAN_"+ts.getMilliTime()+".csv";
	writeFile.open(path.c_str());

	int sssiabal = 0;
	QCanBusFrame frame;
	
    QString view;
     int fid = 0;
     string view_string;
     string csv_string;
     char cancsv[256];

             //while(device->waitForFramesReceived(500)){
             while(!stop_flag){
             	device->waitForFramesReceived(100);
             	sssiabal++;
                 
                frame = device->readFrame();
                view = frame.toString();

                fid = frame.frameId();
                 
             	view_string = view.toStdString();

             	const char* mtime = ts.p_time();

                 if(fid == 688){
                 	
                 	frame_bin += hexToBinary(view_string.at(19));
                 	frame_bin += hexToBinary(view_string.at(20));
                 	frame_bin += hexToBinary(view_string.at(16));
                 	frame_bin += hexToBinary(view_string.at(17));

                 	//handle_int = S2Bconvert(0, 15, frame_bin);
                 	handle_int = std::stoi(frame_bin,nullptr,2);
                 	handle_qstring = QString::number(handle_int);
                 	//std::cout<<"handle "<<handle_qstring.toStdString()<<std::endl;
            
                 	frame_bin = ""; 

                 	frame_bin += hexToBinary(view_string.at(22));
                 	frame_bin += hexToBinary(view_string.at(23));
                 	handle_int2 =  std::stoi(frame_bin,nullptr,2);
                 	handle_qstring2 = QString::number(handle_int2);

                 	emit send_handle(handle_qstring, handle_qstring2);
                	QCoreApplication::processEvents();
                 	frame_bin = ""; 


                 }else if(fid == 790){
                 	
                 	frame_bin += hexToBinary(view_string.at(34));
                 	frame_bin += hexToBinary(view_string.at(35));
                 	
                 	speed_int = std::stoi(frame_bin,nullptr,2);
                 	
                 	emit send_speed(speed_int);
                	QCoreApplication::processEvents();
                	frame_bin = "";

                	sprintf(cancsv, "%s,%d,%d,%d\n", mtime, handle_int, handle_int2, speed_int);
                	writeFile.write(cancsv,strlen(cancsv));

                 }else{

                 	continue;
                 }

                 device->clear();
         }

}
//sudo ip link set can0 type can bitrate 500000
// sudo ip link set up can0
// candump can0

void canThread::stop(){
	stop_flag = true;
    emit send_end();
    writeFile.close();
}

string canThread::hexToBinary(char str){
    //char str = s.at(0);
    string result;

    switch(str){
    case '0':
        result = "0000";
        break;
    case '1':
        result = "0001";
        break;
    case '2':
        result = "0010";
        break;
    case '3':
        result = "0011";
        break;
    case '4':
        result = "0100";
        break;
    case '5':
        result = "0101";
        break;
    case '6':
        result = "0110";
        break;
    case '7':
        result = "0111";
        break;
    case '8':
        result = "1000";
        break;
    case '9':
        result = "1001";
        break;
    case 'A':
        result = "1010";
        break;
    case 'B':
        result = "1011";
        break;
    case 'C':
        result = "1100";
        break;
    case 'D':
        result = "1101";
        break;
    case 'E':
        result = "1110";
        break;
    case 'F':
        result = "1111";
        break;
    }
    return result;
}

int canThread::S2Bconvert(int start, int end, std::string binary)
{
    std::string a;

    for(int i = start; i<=end; i++){
        a += binary.at(i);
    }
    int j = std::stoi(a,nullptr,2);

    return j;
}
