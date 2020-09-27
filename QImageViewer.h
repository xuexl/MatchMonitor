#ifndef QIMAGEVIEWER_H
#define QIMAGEVIEWER_H

#include <QWidget>
#include<QLabel>

#include<opencv2/opencv.hpp>


class QImageViewer: public QLabel
{
    Q_OBJECT
public:
    explicit QImageViewer(QWidget *parent);
    virtual ~QImageViewer() override;
    
    void view(cv::Mat m);
    cv::Mat getMat();
protected:
    cv::Mat mat;
    
};

#endif // QIMAGEVIEWER_H
