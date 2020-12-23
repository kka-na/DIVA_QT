#include "canthread.h"

canThread::canThread(QObject *parent) : QThread(parent)
{
	if (QCanBus::instance()->plugins().contains(QStringLiteral("socketcan"))) {
		std::cout<<"socketcan"<<std::endl;
        QString errorString;
          device = QCanBus::instance()->createDevice(QStringLiteral("socketcan"), QStringLiteral("can0"), &errorString);
         if (!device) {
             qDebug() << errorString;
         }else {
             device->connectDevice();
	    }
                
     }
   			 
}

void canThread::run(){

	CANdata temp;
    string automatic_transmission_mode;
    string turn_signal_direction;
    string turn_signal_blink;
    string turn_signal_blink_left;
    string turn_signal_blink_right;

	
    path = "/home/kanakim/Documents/CAN/i30_CAN_"+ts.getMilliTime()+".csv";
	writeFile.open(path.c_str());

	QCanBusFrame frame;
	
    QString view;
    int fid = 0;
    string view_string;
    string csv_string;
    char cancsv[256];

             while(!stop_flag){
             	device->waitForFramesReceived(10);
                 
                frame = device->readFrame();
                view = frame.toString();

                fid = frame.frameId();
                 
             	view_string = view.toStdString();

             	

                 if(fid == 688){
                 	
                 	frame_bin += hexToBinary(view_string, 19);
                 	frame_bin += hexToBinary(view_string, 20);
                 	frame_bin += hexToBinary(view_string, 16);
                 	frame_bin += hexToBinary(view_string, 17);

                 	temp.handle_angle = std::stoi(frame_bin,nullptr,2);
                 	handle_qstring = QString::number(temp.handle_angle);
            
                 	frame_bin = ""; 

                 	frame_bin += hexToBinary(view_string,22);
                 	frame_bin += hexToBinary(view_string,23);
                 	temp.handle_accel=  std::stoi(frame_bin,nullptr,2);
                 	handle_qstring2 = QString::number(temp.handle_accel);

                 	emit send_handle(handle_qstring, handle_qstring2);
                	QCoreApplication::processEvents();
                 	frame_bin = ""; 

                 }else if(fid == 790){
                 	frame_bin += hexToBinary(view_string, 34);
                 	frame_bin += hexToBinary(view_string, 35);
                 	
                 	temp.vehicle_speed = std::stoi(frame_bin,nullptr,2);
                 	
                 	emit send_speed(temp.vehicle_speed);
                	QCoreApplication::processEvents();
                	frame_bin = "";
              
                 }else if(fid == 1322){//automatic transmission
                 	automatic_transmission_mode = "";
	             	automatic_transmission_mode += hexToBinary(view_string, 19);
	             	automatic_transmission_mode += hexToBinary(view_string, 20);
		            if(automatic_transmission_mode.at(7) == '0'){
		                if(automatic_transmission_mode.at(6) == '1'){
		                     //parking
		                     temp.gear = 0; //'P';
		                     emit send_gear(0);
		                     cout<<"p"<<endl;
		                     QCoreApplication::processEvents();
		                 }
		                 else if(automatic_transmission_mode.at(5) == '1'){
		                     //rewind
		                     temp.gear = 1; //'R';
		                     emit send_gear(1);
		                     QCoreApplication::processEvents();
		                 }
		                 else if(automatic_transmission_mode.at(4) == '1'){
		                     //neutral
		                     temp.gear = 2; //'N';
		                     emit send_gear(2);
		                     QCoreApplication::processEvents();
		                 }
		                 else if(automatic_transmission_mode.at(3) == '1'){
		                     //drive
		                     temp.gear = 3;//'D';
		                     emit send_gear(3);
		                     QCoreApplication::processEvents();
		                 }
		                // emit send_gear(temp.gear);
          			}
                }
                else if(fid == 1345){ //direction light
                	turn_signal_direction = "";
		             turn_signal_blink_left = "";
		             turn_signal_blink_right = "";
		             turn_signal_direction += hexToBinary(view_string, 32);
		             turn_signal_blink_left +=hexToBinary(view_string, 23); // left
		             turn_signal_blink_right += hexToBinary(view_string, 37); // right

		             //if(turn_signal_direction.at(1) == '1') <- When delay occures
		             if(turn_signal_blink_left.at(0) == '1'){
		                 temp.turn_indicator = 0;//'L';
		                  emit send_turn(0);
		                  QCoreApplication::processEvents();
		             }
		             //else if(turn_signal_direction.at(2) == '1') <- When delay occures
		             else if(turn_signal_blink_right.at(1) == '1'){ // right
		                 temp.turn_indicator = 1;//'R';
		                  emit send_turn(1);
		                  QCoreApplication::processEvents();
		             }
		             else{
		                 temp.turn_indicator = 2;//' ';
		                 emit send_turn(2);
		                 QCoreApplication::processEvents();
		             }
		             //emit send_turn(temp.turn_indicator);
                }

                const char* mtime = ts.p_time();
                sprintf(cancsv, "%s,%d,%d,%d,%d,%d\n", mtime, temp.handle_angle, temp.handle_accel, temp.vehicle_speed, temp.gear, temp.turn_indicator);
                writeFile.write(cancsv,strlen(cancsv));

                device->clear();
                QCoreApplication::processEvents();
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

string canThread::hexToBinary(string s, int index){
    char str = s.at(index);
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

