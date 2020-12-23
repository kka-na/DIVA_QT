#include "lidarvtkwidget.h"

lidarVTKWidget::lidarVTKWidget(QWidget* parent) : QVTKWidget(parent){
    
    transform = Eigen::Affine3f::Identity();
    transform.translation() << 0.0, 0.0, 0.0;
    transform.rotate(Eigen::AngleAxisf (M_PI/2, Eigen::Vector3f::UnitZ()));
}

void lidarVTKWidget::initialVtkWidget(){
    defcloud.reset( new pcl::PointCloud<pcl::PointXYZ>);
    viewer.reset(new pcl::visualization::PCLVisualizer("viewer", false));
    viewer->addPointCloud(defcloud, "cloud");
    viewer->addCoordinateSystem(1.0, "cloud");
    viewer->setBackgroundColor(0.05, 0.05, 0.05, 0);
    viewer->setCameraPosition(0,-8,50,1,0,0,0,0,0,0);
    this->render_window = viewer->getRenderWindow();
    this->SetRenderWindow(render_window);
    this->render_window_interactor = this->GetInteractor();
    this->show();
}

void lidarVTKWidget::display_lidar(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud){ //Const& ::Ptr
    pcl::transformPointCloud(*cloud, *cloud, transform);
    viewer->updatePointCloud(cloud, "cloud");
    this->update();
    while (!viewer->wasStopped ()) { // Display the visualiser until 'q' key is pressed
       viewer->spinOnce ();
    }
}

void lidarVTKWidget::display_pcd(QString fileName){ //Const& ::Ptr
    std::string file_name = fileName.toStdString();
    pcl::io::loadPCDFile(fileName.toStdString(), *defcloud);
    pcl::transformPointCloud(*defcloud, *defcloud, transform);
    viewer->updatePointCloud(defcloud, "cloud");
    this->update();
    while (!viewer->wasStopped ()) { // Display the visualiser until 'q' key is pressed
       viewer->spinOnce ();
    }
}


void lidarVTKWidget::init(){
    this->initialVtkWidget();
}
