#ifndef TEMPLATEDILOG_H
#define TEMPLATEDILOG_H

#include <QWidget>

namespace Ui {
class TemplateDilog;
}

class TemplateDilog : public QWidget
{
    Q_OBJECT
    
public:
    explicit TemplateDilog(QWidget *parent = nullptr);
    ~TemplateDilog();
    
private:
    Ui::TemplateDilog *ui;
};

#endif // TEMPLATEDILOG_H
