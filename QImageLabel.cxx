#include "QImageLabel.h"

#include<opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include<vector>

#include<QPainter>
#include<QApplication>
#include<QMouseEvent>

using namespace std;
using namespace cv;


QImageLabel::QImageLabel(QWidget *parent)
    :QLabel(parent)
{
    
}

QImageLabel::~QImageLabel()
{
        
}

void QImageLabel::paintEvent(QPaintEvent* event)
{
     QLabel::paintEvent(event);
     
     if(this->isPainting)
     {
         QPainter painter(this);
      
         painter.setPen(QPen(Qt::red, 2));
         painter.drawRect(QRect(this->x1, this->y1, this->x2 - this->x1, this->y2 - this->y1));
     }
}

void QImageLabel::mousePressEvent(QMouseEvent* event)
{
    if(this->isPainting)
	{
        this->x1 = event->pos().x();
        this->y1 = event->pos().y();
        QCursor cursor;
        cursor.setShape(Qt::ClosedHandCursor);
        QApplication::setOverrideCursor(cursor);
	}
}

void QImageLabel::mouseReleaseEvent(QMouseEvent* event)
{
    if(this->isPainting)
	{        
        x2 = event->pos().x(); 
        y2 = event->pos().y();
        update();
        QApplication::restoreOverrideCursor();
	}
}

void QImageLabel::mouseMoveEvent(QMouseEvent* event)
{
    if(this->isPainting)
	{
        if (event->buttons() & Qt::LeftButton) 
        {
            x2 = event->pos().x(); 
            y2 = event->pos().y();
            update();
        }
	}
}

void QImageLabel::setPainting()
{
    this->isPainting = !this->isPainting;       
}

void QImageLabel::ImRead()
{
    const char* f = "C:/Users/xxl/Pictures/ov/ali-oss-f4ff0e34-8342-4ff7-ae6b-b6bd11f60229.jpg";    
    Mat imgMat = imread(f);
      
//    cv::cvtColor(imgMat, imgMat, COLOR_BGR2RGB);//颜色空间转换
    
    this->imgOrigin = imgMat.clone();
    
    Mat gray;
    cvtColor(this->imgOrigin, gray, COLOR_BGR2GRAY);
    
    QImage img = QImage((const uchar*)(gray.data),
                                gray.cols, gray.rows,
                                gray.cols*gray.channels(),
                                QImage::Format_RGB888);
    
    this->setPixmap(QPixmap::fromImage(img));
    this->resize(this->pixmap()->size());
    this->show();

}

void QImageLabel::getContour()
{
    Mat dst, m, gray;
    dst.create(this->imgOrigin.size(), this->imgOrigin.type());    
    
    cvtColor(this->imgOrigin, gray, COLOR_BGR2GRAY);
        
    blur(gray, m, Size(3,3));
           
    Canny(m, m, 20, 60);
    dst = Scalar::all(0);
    
    this->imgOrigin.copyTo(dst, m);
//    vector<vector<Point>> contours;
    
//    findContours(this->imgOrigin, contours, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
    
//    Mat drawing = 
//    drawContours(this->imgOrigin, contours, -1, Scalar(0, 0, 0), 2);
    
    
    QImage img = QImage((const uchar*)(dst.data),
                                dst.cols, dst.rows,
                                dst.cols * dst.channels(),
                                QImage::Format_RGB888);
    
    this->setPixmap(QPixmap::fromImage(img));
    this->resize(this->pixmap()->size());
    this->show();
    
}
