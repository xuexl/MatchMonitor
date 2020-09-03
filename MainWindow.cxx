#include "MainWindow.h"
#include "./ui_MainWindow.h"

#include<iostream>





MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    connect(this->ui->pb_read, &QPushButton::clicked, [this](){
        this->ui->lb_view->ImRead();
    });
    connect(this->ui->pb_anchor, &QPushButton::clicked, [this](){
        this->ui->lb_view->setPainting();
    });   
    connect(this->ui->pb_contour, &QPushButton::clicked, [this](){
        this->ui->lb_view->getContour();
    });
    
}

MainWindow::~MainWindow()
{
    delete ui;
}


