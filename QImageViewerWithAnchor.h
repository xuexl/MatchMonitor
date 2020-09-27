#ifndef QIMAGEVIEWERWITHANCHOR_H
#define QIMAGEVIEWERWITHANCHOR_H

#include"QImageViewer.h"

#include <QWidget>

#include<vector>


struct AnchorRect
{
    AnchorRect(int _x1, int _y1, int _x2, int _y2)
    {
        x1 = _x1; 
        y1 = _y1; 
        x2 = _x2; 
        y2 = _y2; 
    }
    int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
};

class QImageViewerWithAnchor: public QImageViewer
{
    Q_OBJECT
public:
    explicit QImageViewerWithAnchor(QWidget *parent);
    virtual ~QImageViewerWithAnchor() override;
    
public:
    /*   
    * update isPainting
    */
    void setPainting();
    
    /*
     * get template
    */
    void exportTemplate();
    
protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    
private:
    bool isPainting = false;
    std::vector<AnchorRect> anchorRects;    
    
};

#endif // QIMAGEVIEWERWITHANCHOR_H
