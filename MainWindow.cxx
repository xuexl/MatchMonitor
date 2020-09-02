#include "MainWindow.h"
#include "./ui_MainWindow.h"

#include<iostream>

#include<opencv2/core/core.hpp>
#include <opencv2/imgproc.hpp>


using namespace cv;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    connect(this->ui->pb_read, &QPushButton::clicked, this, &MainWindow::ImRead);
    connect(this->ui->pb_anchor, &QPushButton::clicked, [this](){
        this->ui->lb_view->setPainting();
    });
    
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ImRead()
{
    const char* f = "C:/Users/xxl/Pictures/ov/ali-oss-f4ff0e34-8342-4ff7-ae6b-b6bd11f60229.jpg";    
    Mat imgMat = imread(f);
      
    cv::cvtColor(imgMat, imgMat, COLOR_BGR2RGB);//颜色空间转换
    QImage img = QImage((const uchar*)(imgMat.data),
                                imgMat.cols,imgMat.rows,
                                imgMat.cols*imgMat.channels(),
                                QImage::Format_RGB888);
    
    this->ui->lb_view->setPixmap(QPixmap::fromImage(img));
    this->ui->lb_view->resize(this->ui->lb_view->pixmap()->size());
    this->ui->lb_view->show();

}
