#include "QImageLabel.h"

#include<QPainter>
#include<QApplication>
#include<QMouseEvent>


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


