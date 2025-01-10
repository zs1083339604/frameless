#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : FrameLessWindow(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    button_menu = nullptr;
    addSettingMenu();
}

Widget::~Widget()
{
    if(button_menu != nullptr){
        button_menu->disconnect();
        button_menu->deleteLater();
    }

    delete ui;
}

void Widget::addSettingMenu()
{
    if(button_menu == nullptr){
        addSeparate(1, 5);
        // 判断模式
        QString icon = "setting_blank.png";
        QString hoverColor = "#272727";
        if(getModel() == WHITE){
            icon = "setting.png";
            hoverColor = "#E9E9E9";
        }
        // 添加按钮和菜单
        button_menu = new QPushButton(this);
        button_menu->setStyleSheet("QPushButton{\
            background-image: url(:/titleBar/icon/"+icon+");\
            border:none;\
            background-repeat: no-repeat;\
            background-position: center center;\
            width: 30px;\
            height: 32px;\
            color: #fff;\
            border-radius: 5px;\
        }\
        QPushButton:hover{\
            background-color: "+hoverColor+";\
        }\
        QPushButton::menu-indicator{\
            width: 0px;\
        }");

        addWidget(button_menu, 5);

        // 连接点击信号
        connect(button_menu, &QPushButton::clicked, this, []{
            qDebug() << "按钮被点击了";
        });
    }
}
