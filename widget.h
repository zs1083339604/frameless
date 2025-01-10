#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "framelesswindow.h"
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public FrameLessWindow
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    // 添加设置按钮，向标题栏中
    void addSettingMenu();

private:
    Ui::Widget *ui;
    QPushButton* button_menu;
};
#endif // WIDGET_H
