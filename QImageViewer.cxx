#include "QImageViewer.h"

QImageViewer::QImageViewer(QWidget *parent)
    :QLabel(parent)
{
    
}

QImageViewer::~QImageViewer()
{
    
}

void QImageViewer::view(cv::Mat m)
{
    this->mat = m;
    
    QImage img = QImage(static_cast<const uchar*>(this->mat.data),
                                this->mat.cols, this->mat.rows,
                                this->mat.step,
                                QImage::Format_RGB888);
    
    this->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    this->setPixmap(QPixmap::fromImage(img));    
    this->resize(this->pixmap()->size());    
    this->show();
}

cv::Mat QImageViewer::getMat()
{
    return mat;
}
