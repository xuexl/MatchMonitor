#include "QImageViewerWithAnchor.h"

#include<QPainter>
#include<QApplication>
#include<QMouseEvent>

#include<string>
#include<iostream>


QImageViewerWithAnchor::QImageViewerWithAnchor(QWidget *parent)
    :QImageViewer(parent)
{

}

QImageViewerWithAnchor::~QImageViewerWithAnchor()
{
    
}

void QImageViewerWithAnchor::paintEvent(QPaintEvent* event)
{
     QLabel::paintEvent(event);
     
     if(this->isPainting)
     {
        QPainter painter(this);      
        painter.setPen(QPen(Qt::red, 2));     
                
        for(auto ar: this->anchorRects)
        {
            painter.drawRect(QRect(ar.x1, ar.y1, ar.x2 - ar.x1, ar.y2 - ar.y1));            
        }
     }
}

void QImageViewerWithAnchor::mousePressEvent(QMouseEvent* event)
{
    if(this->isPainting)
	{
        this->anchorRects.push_back(AnchorRect(event->pos().x(), event->pos().y(), event->pos().x(), event->pos().y()));
        
        QCursor cursor;
        cursor.setShape(Qt::ClosedHandCursor);
        QApplication::setOverrideCursor(cursor);
	}
}

void QImageViewerWithAnchor::mouseReleaseEvent(QMouseEvent* event)
{
    if(this->isPainting)
	{        
        this->anchorRects.back().x2 = event->pos().x(); 
        this->anchorRects.back().y2 = event->pos().y();
        
        update();
        QApplication::restoreOverrideCursor();
	}
}

void QImageViewerWithAnchor::mouseMoveEvent(QMouseEvent* event)
{
    if(this->isPainting)
	{
        if (event->buttons() & Qt::LeftButton) 
        {
            this->anchorRects.back().x2 = event->pos().x(); 
            this->anchorRects.back().y2 = event->pos().y();
            
            update();
        }
	}
}

void QImageViewerWithAnchor::setPainting()
{    
    this->isPainting = !this->isPainting;       
    
    if(this->isPainting)    
    {       
        this->anchorRects.clear();
    }
}

void QImageViewerWithAnchor::exportTemplate()
{
    std::string dir("C:/Users/xxl/Pictures/ov/tem/");
    int i = 0;
    for(auto ar: this->anchorRects)
    {        
        cv::imwrite(dir + std::to_string (++i) + ".jpg", this->mat(cv::Rect(ar.x1, ar.y1, (ar.x2-ar.x1), (ar.y2-ar.y1))));        
    }     
}
