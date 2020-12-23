#include "glwidget.h"

glwidget::glwidget(QWidget *parent) : QGLWidget(parent)
{
    car = new ObjParser("/home/kanakim/DIVA_QT/obj/Car.obj");
}

glwidget::~glwidget(){}


class IMUdata {
public:
    float gyrox, gyroy, gyroz, magx, magy, magz, accelx, accely, accelz;
};

void glwidget::initializeGL(){
        glClearColor(0.0, 0.0, 0.0, 0.0);
        glClearDepth(1.0);
        glEnable(GL_DEPTH_TEST);
}

mscl::Connection connection = mscl::Connection::Serial("/dev/ttyACM1", 115200);
mscl::InertialNode node(connection);

void glwidget::paintGL(){
    

    mscl::MipDataPackets packets = node.getDataPackets(500);
    IMUdata temp;

        for(mscl::MipDataPacket packet : packets)
        {
            int count = 0;
            packet.descriptorSet();
            mscl::MipDataPoints points = packet.data();

            for(mscl::MipDataPoint dataPoint : points)
            {
                const char* cName = dataPoint.channelName().c_str();
                const char* mtime = ts.p_time();

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

                //if(0 < count && count <= 9) cout << dataPoint.channelName() << " : " << dataPoint.as_float() << endl;
                count--;

                if(count == 0) {
                    sprintf(fp, "%s,%f,%f,%f,%f,%f,%f,%f,%f,%f\n", mtime, temp.gyrox, temp.gyroy, temp.gyroz, temp.magx, temp.magy, temp.magz, temp.accelx, temp.accely, temp.accelz);
                    writeFile.write(fp, strlen(fp));
                    break;
                }
            }
            //QCoreApplication::processEvents();

            if(count == 0){
                break;
            }
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glTranslatef(0, 0, -4.0);
        glRotatef(-60, 1.0, 0.0, 0.0);
        glRotatef(0, 0.0, 1.0, 0.0);
        glRotatef(45, 0.0, 0.0, 1.0);



        double pitch = 180 * atan(accel_x / sqrt(accel_y * accel_y + accel_z * accel_z)) / M_PI;
        double yaw = 180 * atan(accel_z / sqrt(accel_x * accel_x + accel_z * accel_z)) / M_PI;
        double roll =   180 * atan(accel_y / sqrt(accel_x * accel_x + accel_z * accel_z)) / M_PI;

        draw_line(roll, pitch, yaw);

        glRotatef(float(roll), 1.0, 0.0, 0.0);
        glRotatef(float(pitch), 0.0, 1.0, 0.0);
        //glRotatef(yaw, 0.0, 0.0, 1.0);

        draw_obj(car);
        //QThread::msleep(10);

}

void glwidget::resizeGL(int w, int h){
        glViewport(0, 0, w, h);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        gluPerspective(45, (float)w / h, 1.0, 100.0);

        glMatrixMode(GL_MODELVIEW);
}


void glwidget::streaming_start(){

    mtime = ts.p_time();
    path = "/home/kanakim/Documents/IMU/i30_IMU_"+ts.getMilliTime()+".csv";
    writeFile.open(path.c_str());
    std::cout<<"The IMU.csv file saved to ["<<path<<"]\n";

    connect(&timer, SIGNAL(timeout()), this, SLOT(updateGL()));
    timer.start(10);
}

void glwidget::initialize_glwidget(){
    disconnect(&timer, SIGNAL(timeout()),this, SLOT(updateGL()));
    timer.stop();
    writeFile.close();
}


void glwidget::draw_obj(ObjParser *objParser) {
    glTranslated(0.0, 0.0, -0.5);
    glScaled(0.5, 0.5, 0.5);
    glRotated(-90.0, 0.0, 0.0, 1.0);
    glRotated(90.0, 1.0, 0.0, 0.0);
    glColor4f(0.549, 0.360, 1, 0.2);
    glBegin(GL_TRIANGLES);
    for (unsigned int n = 0; n < objParser->getFaceSize(); n += 3) {
        glNormal3f(objParser->normal[objParser->normalIdx[n] - 1].x,
            objParser->normal[objParser->normalIdx[n] - 1].y,
            objParser->normal[objParser->normalIdx[n] - 1].z);
        glVertex3f(objParser->vertices[objParser->vertexIdx[n] - 1].x,
            objParser->vertices[objParser->vertexIdx[n] - 1].y,
            objParser->vertices[objParser->vertexIdx[n] - 1].z);


        glNormal3f(objParser->normal[objParser->normalIdx[n + 1] - 1].x,
            objParser->normal[objParser->normalIdx[n + 1] - 1].y,
            objParser->normal[objParser->normalIdx[n + 1] - 1].z);
        glVertex3f(objParser->vertices[objParser->vertexIdx[n + 1] - 1].x,
            objParser->vertices[objParser->vertexIdx[n + 1] - 1].y,
            objParser->vertices[objParser->vertexIdx[n + 1] - 1].z);


        glNormal3f(objParser->normal[objParser->normalIdx[n + 2] - 1].x,
            objParser->normal[objParser->normalIdx[n + 2] - 1].y,
            objParser->normal[objParser->normalIdx[n + 2] - 1].z);
        glVertex3f(objParser->vertices[objParser->vertexIdx[n + 2] - 1].x,
            objParser->vertices[objParser->vertexIdx[n + 2] - 1].y,
            objParser->vertices[objParser->vertexIdx[n + 2] - 1].z);
    }
    glEnd();
}


void glwidget::drawBitmapText(const char *str, float x, float y, float z)
{
    glRasterPos3f(x, y, z); //문자열이 그려질 위치 지정

    while (*str)
    {
        //GLUT_BITMAP_TIMES_ROMAN_24 폰트를 사용하여 문자열을 그린다.
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *str);

        str++;
    }
}



void glwidget::draw_line(double roll, double pitch, double yaw)
{
    char *xroll = new char[256];
    char *ypitch = new char[256];
    char *zyaw = new char[256];

    sprintf(xroll, "R_%f", roll);
    sprintf(ypitch, "P_%f", pitch);
    sprintf(zyaw, "Y_%f", yaw);



    glPushMatrix();

    glPushMatrix();
        glColor3f(0.313, 0.737, 0.929);
        glBegin(GL_LINES);
            glVertex3f(5.0, 0.0, 0.0);
            glVertex3f(-5.0, 0.0, 0.0);
        glEnd();
        drawBitmapText(xroll, -2.0, 0.0, 0.0);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.313, 0.929, 0.615);
        glBegin(GL_LINES);
            glVertex3f(0.0, 5.0, 0.0);
            glVertex3f(0.0, -5.0, 0.0);
        glEnd();
        drawBitmapText(ypitch, 0.0, 2.0, 0.0);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.823, 0.929, 0.313);
        glBegin(GL_LINES);
            glVertex3f(0.0, 0.0, 5.0);
            glVertex3f(0.0, 0.0, -5.0);
        glEnd();
        drawBitmapText(zyaw, 0.0, -0.1, 1.0);
    glPopMatrix();

    glPopMatrix();

    glFlush();
}
