#ifndef STORINGDB_H
#define STORINGDB_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QFile>
#include <QString>
#include <QDebug>
#include <QTextStream>

#include "jsoncpp/json/json.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <ctime>

using namespace std;

class storingDB
{
public:
    QSqlDatabase database;
    string folder_path;
    storingDB(string fpath);

    bool settingDB();
    void toLogDB(string path);
    void toSceneDB(string path);
    void toFrameDB(string path);
    void toFrameDataDB(string path);
    void toGPSDataDB(string path);
    void toIMUDataDB(string path);
    void toCANDataDB(string path);
};

#endif // STORINGDB_H
