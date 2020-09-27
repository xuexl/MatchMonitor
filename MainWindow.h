#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QMenu>
#include<QAction>

#include<opencv2/opencv.hpp>

#include<vector>

#include"TemplateDialog.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    

private:
    Ui::MainWindow *ui;
    TemplateDialog* templateDialog; 
    
    //menu
    QMenu* templateMenu;
    QAction* templateAction;
    
    //
    std::vector<cv::Mat> templatesCache;
    
private:
    /*
     * read
    */
    void imgRead(const char* f);

    /**
     * get the part of anchor ???
    */
    
    /*
     *get the contour  
    */
//    void getContour();
    
    /*
     * get template
    */
    void getTemplate();
    
    /*
     * get images
    */
//    void getImages();
    
    /*
     * matchTemplate
    */
    void match();
    
    /*
     * load templates
    */
    void loadTemplates(const char* directory);

    /*
     * load images     
    */
    void loadImages(const char* directory);
        
    
};
#endif // MAINWINDOW_H
