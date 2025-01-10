#include "framelesswindow.h"
#include <QSpacerItem>

FrameLessWindow::FrameLessWindow(QWidget *parent)
{
    setupUI();
    titleBar->setStyleSheet("QPushButton{ border:none; }");
    setResizeableAreaWidth(8);
    setWindowFlags(Qt::FramelessWindowHint);
    setTitleBar(titleBar);
    showMaximize = true;
    changeMaximizeButton();
    setTitlebarModel(BLACK);
}

FrameLessWindow::~FrameLessWindow()
{
    // 清理分隔符列表
    qDeleteAll(separateList);
    separateList.clear();

    // 删除标题栏（它会自动删除所有子控件）
    delete titleBar;
}

void FrameLessWindow::setupUI()
{
    // 创建标题栏
    titleBar = new QWidget(this);
    titleBar->setMinimumHeight(32);
    titleBar->setMaximumHeight(32);

    // 创建水平布局
    horizontalLayout = new QHBoxLayout(titleBar);
    horizontalLayout->setSpacing(0);
    horizontalLayout->setContentsMargins(0, 0, 0, 0);

    // 左侧间隔
    horizontalLayout->addItem(new QSpacerItem(5, 20, QSizePolicy::Fixed, QSizePolicy::Minimum));

    // 图标
    icon = new QLabel(titleBar);
    icon->setMinimumSize(18, 18);
    icon->setMaximumSize(18, 18);
    horizontalLayout->addWidget(icon);

    // 图标和标题间隔
    horizontalLayout->addItem(new QSpacerItem(3, 20, QSizePolicy::Fixed, QSizePolicy::Minimum));

    // 标题
    title = new QLabel("程序标题", titleBar);
    horizontalLayout->addWidget(title);

    // 弹簧
    horizontalLayout->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));

    // 最小化按钮
    minimize = new QPushButton(titleBar);
    minimize->setMinimumSize(32, 32);
    minimize->setMaximumSize(32, 32);
    minimize->setIconSize(QSize(10, 10));
    horizontalLayout->addWidget(minimize);

    // 还原按钮
    restore = new QPushButton(titleBar);
    restore->setMinimumSize(32, 32);
    restore->setMaximumSize(32, 32);
    restore->setIconSize(QSize(10, 10));
    horizontalLayout->addWidget(restore);

    // 最大化按钮
    maximize = new QPushButton(titleBar);
    maximize->setMinimumSize(32, 32);
    maximize->setMaximumSize(32, 32);
    maximize->setIconSize(QSize(10, 10));
    horizontalLayout->addWidget(maximize);

    // 关闭按钮
    closeButton = new QPushButton(titleBar);
    closeButton->setMinimumSize(32, 32);
    closeButton->setMaximumSize(32, 32);
    closeButton->setIconSize(QSize(10, 10));
    horizontalLayout->addWidget(closeButton);

    // 连接信号槽
    connect(closeButton, &QPushButton::clicked, this, &FrameLessWindow::closeButtonClicked);
    connect(maximize, &QPushButton::clicked, this, &FrameLessWindow::maximizeClicked);
    connect(minimize, &QPushButton::clicked, this, &FrameLessWindow::minimizeClicked);
    connect(restore, &QPushButton::clicked, this, &FrameLessWindow::restoreClicked);
}

void FrameLessWindow::setMaximizeButtonShowType(bool show)
{
    showMaximize = show;
    changeMaximizeButton();
}

void FrameLessWindow::changeMaximizeButton()
{
    if(showMaximize){
        if(isMaximized()){
            // 在隐藏前，先模拟鼠标离开事件来清除hover状态
            QEvent leaveEvent(QEvent::Leave);
            QApplication::sendEvent(maximize, &leaveEvent);

            maximize->setHidden(true);
            restore->setHidden(false);
        }else{
            // 同上
            QEvent leaveEvent(QEvent::Leave);
            QApplication::sendEvent(restore, &leaveEvent);

            maximize->setHidden(false);
            restore->setHidden(true);
        }
    }else{
        maximize->setHidden(true);
        restore->setHidden(true);
    }
}

void FrameLessWindow::changeMinimizeButton(bool show)
{
    minimize->setHidden(!show);
}

void FrameLessWindow::changeCloseButton(bool show)
{
    closeButton->setHidden(!show);
}

void FrameLessWindow::setTitlebarModel(Model type)
{
    nowModel = type;
    switch(type){
    case BLACK:
        closeButton->setIcon(QIcon(":/titleBar/icon/Close_black.png"));
        maximize->setIcon(QIcon(":/titleBar/icon/Maximize_black.png"));
        restore->setIcon(QIcon(":/titleBar/icon/Restore_black.png"));
        minimize->setIcon(QIcon(":/titleBar/icon/Minimize_black.png"));
        setCloseButtonColor("#AE1C1C", "#450B0B");
        setMaximizeButtonColor("#272727", "#020202");
        setMinimizeButtonColor("#272727", "#020202");
        setTitleColor("#ffffff");
        break;
    case WHITE:
        closeButton->setIcon(QIcon(":/titleBar/icon/Close.png"));
        maximize->setIcon(QIcon(":/titleBar/icon/Maximize.png"));
        restore->setIcon(QIcon(":/titleBar/icon/Restore.png"));
        minimize->setIcon(QIcon(":/titleBar/icon/Minimize.png"));
        setCloseButtonColor("#C42B1C", "#C84031");
        setMaximizeButtonColor("#E9E9E9", "#EDEDED");
        setMinimizeButtonColor("#E9E9E9", "#EDEDED");
        setTitleColor("#000000");
        break;
    }
}

void FrameLessWindow::setCloseButtonColor(QString hover, QString pressed)
{
    closeButton->setStyleSheet("QPushButton:hover {background-color:"+hover+";} QPushButton:pressed {background-color:"+pressed+";}");
}

void FrameLessWindow::setMaximizeButtonColor(QString hover, QString pressed)
{
    maximize->setStyleSheet("QPushButton:hover {background-color:"+hover+";} QPushButton:pressed {background-color:"+pressed+";}");
    restore->setStyleSheet("QPushButton:hover {background-color:"+hover+";} QPushButton:pressed {background-color:"+pressed+";}");
}

void FrameLessWindow::setMinimizeButtonColor(QString hover, QString pressed)
{
    minimize->setStyleSheet("QPushButton:hover {background-color:"+hover+";} QPushButton:pressed {background-color:"+pressed+";}");
}

void FrameLessWindow::setTitle(QString text)
{
    title->setText(text);
}

void FrameLessWindow::setIcon(QPixmap pixmap)
{
    icon->setPixmap(pixmap.scaled(QSize(16, 16)));
}

void FrameLessWindow::setTitleColor(QString color)
{
    title->setStyleSheet("color:" + color + ";");
}

void FrameLessWindow::addWidget(QWidget *widget, int index)
{
    if(index >= 0){
        horizontalLayout->insertWidget(index, widget);
    }else{
        horizontalLayout->addWidget(widget);
    }
}

void FrameLessWindow::addSeparate(int width, int index)
{
    separateList.append(new QLabel(this));
    QString label_str = "|";
    for(int i = 0; i < width; i++){
        label_str = "&nbsp;" + label_str + "&nbsp;";
    }
    separateList.last()->setText("<html><head/><body><p style=\" color:#2F2F2F; font-size: 10px;\">"+label_str+"</p></body></html>");
    addWidget(separateList.last(), index);
}

void FrameLessWindow::setRaise()
{
    titleBar->raise();
}

void FrameLessWindow::setBackground(QString color)
{
    titleBar->setStyleSheet("#titleBar{ background-color: " + color + "; } QPushButton{ border:none; }");
}

void FrameLessWindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::WindowStateChange){
        changeMaximizeButton();
    }
    QWidget::changeEvent(event);
}

void FrameLessWindow::resizeEvent(QResizeEvent *event)
{
    // 始终让titleBar填满QWidget
    titleBar->resize(width(), titleBar->height());
    QWidget::resizeEvent(event);
}

void FrameLessWindow::closeButtonClicked()
{
    close();
}

void FrameLessWindow::maximizeClicked()
{
    showMaximized();
}

void FrameLessWindow::minimizeClicked()
{
    showMinimized();
}

void FrameLessWindow::restoreClicked()
{
    showNormal();
}
