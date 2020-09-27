#include "MainWindow.h"
#include "./ui_MainWindow.h"

#include<opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>

#include<vector>
#include<string>
#include<iostream>

#include<QDir>

#include"ImageLoader.h"

using namespace cv;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    this->templateDilog = new TemplateDilog(this);
    
    //init template list
    this->ui->lw_templates->setViewMode(QListView::IconMode);
    this->ui->lw_templates->setIconSize(QSize(100, 100));
    this->ui->lw_templates->setSpacing(10);
    this->ui->lw_templates->setResizeMode(QListWidget::Adjust);
    this->ui->lw_templates->setMovement(QListWidget::Static);    
    //load images
    loadTemplates("C:/Users/xxl/Pictures/ov/tem");
    
    //init image list
    this->ui->lw_images->setViewMode(QListView::IconMode);
    this->ui->lw_images->setIconSize(QSize(100, 100));
    this->ui->lw_images->setSpacing(10);
    this->ui->lw_images->setResizeMode(QListWidget::Adjust);
    this->ui->lw_images->setMovement(QListWidget::Static);    
    const char* imgDir = "C:/Users/xxl/Pictures/ov";
    connect(ui->lw_images, &QListWidget::itemClicked, [this, imgDir](QListWidgetItem* item){                
        this->imgRead(std::string(imgDir).append("/").append(item->text().toStdString()).c_str());             
        //
        this->match();
    });
    //load images
    loadImages(imgDir);
    
    //menu
    this->templateAction = new QAction(QString::fromLocal8Bit("选出ROI"), this); 
    connect(this->templateAction, &QAction::triggered, [this](){
        this->templateDialog = new TemplateDialog(this);
        this->templateDialog->setModal(true);
        this->templateDialog->show();
    });
    this->templateMenu = menuBar()->addMenu(QString::fromLocal8Bit("模板管理"));
    this->templateMenu->addAction(this->templateAction);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::imgRead(const char* f)
{    
    Mat imgMat = imread(f);

    cvtColor(imgMat, imgMat, COLOR_BGR2GRAY);
    cvtColor(imgMat, imgMat, COLOR_GRAY2RGB);

    this->ui->lb_view->view(imgMat);
}

void MainWindow::getTemplate()
{    
//    this->ui->lb_anchorView->view(this->ui->lb_view->getTemplate());   
}

void MainWindow::match()
{
    
    auto method = TM_SQDIFF_NORMED;
    
    auto img = this->ui->lb_view->getMat();
    
    for(auto item = this->templatesCache.begin(); item != this->templatesCache.end(); ++item)
    {        
        Mat r;
        Mat tp = *item;
        
        matchTemplate(img, tp, r, method);
        normalize(r, r, 0, 1, NORM_MINMAX, -1, Mat());
        
        double minV;
        double maxV;
        Point minL;
        Point maxL;
        Point matchL;
        minMaxLoc(r, &minV, &maxV, &minL, &maxL, Mat());
        
        if(method == TM_SQDIFF || method == TM_SQDIFF_NORMED)
            matchL = minL;
        else
            matchL = maxL;
            
        rectangle(img, matchL, Point(matchL.x + tp.cols, matchL.y + tp.rows), Scalar(0, 0, 255), 2, 8, 0);
//        rectangle(r, matchL, Point(matchL.x + tp.cols, matchL.y + tp.rows), Scalar(0, 0, 255), 2, 8, 0);
        
    }
    
    this->ui->lb_view->view(img);
//    imshow("img", img);
//    imshow("r", r);
}

void MainWindow::loadTemplates(const char* directory)
{    
    QDir dir(directory);
    if(dir.exists())
    {
        QStringList filter;
        filter << "*.jpeg"<< "*.png"<< "*.jpg";        
        dir.setNameFilters(filter);
        
        dir.setFilter(QDir::NoDotAndDotDot | QDir::AllEntries);
        
        for(auto entry: dir.entryList())
        {            
            this->ui->lw_templates->addItem(new QListWidgetItem(
                                                QIcon(QString("%1/%2").arg(directory).arg(entry)), 
                                                entry));
        }        
        //
        for(auto entry: dir.entryList())
        {            
            this->templatesCache.push_back(ImageLoader().imgRead(QString("%1/%2").arg(directory).arg(entry).toStdString().c_str()));
        }                
    }
}

void MainWindow::loadImages(const char* directory)
{
    QDir dir(directory);
    if(dir.exists())
    {
        QStringList filter;
        filter << "*.jpeg"<< "*.png"<< "*.jpg";        
        dir.setNameFilters(filter);
        
        dir.setFilter(QDir::NoDotAndDotDot | QDir::AllEntries);
        
        for(auto entry: dir.entryList())
        {            
            this->ui->lw_images->addItem(new QListWidgetItem(
                                                QIcon(QString("%1/%2").arg(directory).arg(entry)), 
                                                entry));
        }
    }    
}
