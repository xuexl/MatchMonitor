#ifndef QIMAGELABEL_H
#define QIMAGELABEL_H

#include <QWidget>
#include<QLabel>


class QImageLabel: public QLabel
{
    Q_OBJECT
public:
    explicit QImageLabel(QWidget *parent);
    ~QImageLabel() override;
    
public:
    /**
     update isPainting
    */
    void setPainting();
    
    /**
     * get the part of anchor ???
    */
    
    
protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    
private:
    bool isPainting = false;
    int x1, y1, x2, y2;
    
};

#endif // QIMAGELABEL_H
