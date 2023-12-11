#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : FrameLessWindow(parent)
    , ui(new Ui::Widget)
{
//    ui->setupUi(getContent());
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

