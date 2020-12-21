#ifndef DISPLAYTHREAD_H
#define DISPLAYTHREAD_H

#include <QObject>
#include <QWidget>
#include <QThread>

class DisplayThread : public QThread
{
    Q_OBJECT
public:
    DisplayThread(QObject *parent = 0);
public slots:
    void display_frames();
private:
    void run();
signals:
    void send_pixmap(QString);
    void send_pcd(QString);

};

#endif // DISPLAYTHREAD_H
