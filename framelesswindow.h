#ifndef FRAMELESSWINDOW_H
#define FRAMELESSWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include "NativeWindowTemplate.hpp"

class FrameLessWindow: public NativeWindowTemplate<QWidget>
{
    Q_OBJECT
public:
    // 标题栏的模式，我的项目中需要用到两个，黑色和白色
    // 黑色采用的剪映样式，白色采用的win11默认样式
    enum Model{
        BLACK = 1,
        WHITE
    };

    explicit FrameLessWindow(QWidget *parent = nullptr);
    ~FrameLessWindow();
    // 切换3个按钮的显示，有时是不需要显示某些按钮的
    void setMaximizeButtonShowType(bool show);
    void changeMaximizeButton();
    void changeMinimizeButton(bool show);
    void changeCloseButton(bool show);
    // 设置标题栏的模式
    void setTitlebarModel(Model type);
    // 设置3个按钮的背景颜色，传入16进制颜色，因为是用QSS设置的，例：#FFFFFF
    void setCloseButtonColor(QString hover, QString pressed);
    void setMaximizeButtonColor(QString hover, QString pressed);
    void setMinimizeButtonColor(QString hover, QString pressed);
    // 设置标题和图标
    void setTitle(QString title);
    void setIcon(QPixmap icon);
    void setTitleColor(QString color);
    // 向标题栏中单独添加QWidget
    // index为向下标为哪里的位置插入，如果为负数，则在最后插入
    // 注意：该Widget内存不会自动销毁，请在调用类中手动销毁该内存
    void addWidget(QWidget *widget, int index = -1);
    // 插入分隔符，index意思同上
    void addSeparate(int width = 1, int index = -1);
    // 将标题栏置顶，如果继承类没有在上面留32像素，标题栏会被遮挡，需要调用此方法将标题栏层级置顶
    void setRaise();
    // 设置背景颜色
    void setBackground(QString color);
    // 获取模式
    Model getModel(){return nowModel;};

protected:
    void changeEvent(QEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void closeButtonClicked();
    void maximizeClicked();
    void minimizeClicked();
    void restoreClicked();

private:
    void setupUI();

    QWidget* titleBar;
    QHBoxLayout* horizontalLayout;
    QLabel* icon;
    QLabel* title;
    QPushButton* minimize;
    QPushButton* restore;
    QPushButton* maximize;
    QPushButton* closeButton;
    bool showMaximize;
    QList<QLabel*> separateList;
    Model nowModel;
};

#endif // FRAMELESSWINDOW_H
