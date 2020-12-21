#ifndef IMUWIDGET_H
#define IMUWIDGET_H

#include <QtOpenGL/QGLWidget>
#include <QTimer>
#include <QObject>
#include <QWidget>
#include <QThread>

#include <math.h>
#include <fstream>
#include <sstream>
#include <istream>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstdlib>

#include <GL/freeglut.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "ObjParser.h"

class imuWidget : public QGLWidget
{
   Q_OBJECT

   public:
      imuWidget(QWidget *parent = 0);

       void initializeGL();
       void paintGL();
       void resizeGL(int w, int h);

       void draw_obj(ObjParser *objParser);
       void drawBitmapText(const char *str, float x, float y, float z);
       void draw_line(double roll, double pitch, double yaw);

       QTimer timer;
       ObjParser *car;

       float accel_x = 0.0;
       float accel_y = 0.0;
       float accel_z = 0.0;


private slots:
  void streaming_start(float ax, float ay, float az);
  void initialize_glwidget();

};

#endif // IMUWIDGET_H
