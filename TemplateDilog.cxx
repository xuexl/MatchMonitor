#include "TemplateDilog.h"
#include "ui_TemplateDilog.h"

TemplateDilog::TemplateDilog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TemplateDilog)
{
    ui->setupUi(this);
}

TemplateDilog::~TemplateDilog()
{
    delete ui;
}
