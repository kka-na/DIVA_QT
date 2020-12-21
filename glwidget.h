#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QtOpenGL/QGLWidget>
#include <QTimer>
#include <QObject>
#include <QWidget>

#include <math.h>
#include <fstream>
#include <sstream>
#include <istream>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstdlib>

#include "mscl/mscl.h"
#include <GL/freeglut.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "mainwindow.h"
#include "Timestamp.h"
#include "ObjParser.h"

class glwidget : public QGLWidget
{
    Q_OBJECT



public:
    explicit glwidget(QWidget *parent = 0);
    ~glwidget();
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

    void draw_obj(ObjParser *objParser);
    void drawBitmapText(const char *str, float x, float y, float z);
    void draw_line(double roll, double pitch, double yaw);


    ObjParser *car;

    QTimer timer;

    Timestamp ts;

	float accel_x = 0.1;
	float accel_y = 0.1;
	float accel_z = 0.1;

    const char * mtime;
    //char path[256];
    char fp[526];
    string path;
    ofstream writeFile;


private slots:
	void streaming_start();
    void initialize_glwidget();
};

#endif // GLWIDGET_H
