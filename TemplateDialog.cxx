#include "TemplateDialog.h"
#include "ui_TemplateDialog.h"

#include"ImageLoader.h"

TemplateDialog::TemplateDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TemplateDialog)
{
    ui->setupUi(this);
    
    const char* file = "C:/Users/xxl/Pictures/ov/1599536949346.jpeg";
    this->ui->lb_selectTemplates->view(ImageLoader().imgRead(file));
    
    //connect
    connect(this->ui->pb_anchorTemplates, &QPushButton::clicked, [this](){        
        this->ui->lb_selectTemplates->setPainting();        
    }); 
    connect(this->ui->pb_setTemplates, &QPushButton::clicked, [this](){        
        this->ui->lb_selectTemplates->exportTemplate();    
        
    }); 
    
}

TemplateDialog::~TemplateDialog()
{
    delete ui;
}
