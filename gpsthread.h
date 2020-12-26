#ifndef GPSTHREAD_H
#define GPSTHREAD_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QThread>
#include <QDebug>
#include <QCoreApplication>
#include <string>
#include <iostream>
#include <QtWebEngineWidgets/QtWebEngineWidgets>

#include "Timestamp.h"
#include "Strtok_m.h"
#include "Can_serial.h"

#define GPSDEVICE "/dev/ttyACM0"
#define BAUDRATE B9600


class gpsThread : public QThread
{
     Q_OBJECT
public:
    explicit gpsThread(QObject *parent = 0);

    Timestamp ts;
    Strtok_m stm;
    Can_serial cs;

    int iDev;
    int iRet;

    string latitude;
    string longitude;

    char cBuff[526];

    const char * mtime;
    string dir;
    string path;
    ofstream writeFile;
    QTimer timer;
    bool stop_flag = false;
    long double Convert_to_dd(long double raw);

public slots:
    void get_dir(std::string);
    void stop();

private:
    void run() override;

signals:
    void send_ll(QString, QString);
    void send_end();

};

#endif // GPSTHREAD_H
