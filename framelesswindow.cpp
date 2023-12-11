#include "framelesswindow.h"
#include "ui_framelesswindow.h"

FrameLessWindow::FrameLessWindow(QWidget *parent) :
    NativeWindowTemplate<QWidget>(parent),
    ui(new Ui::FrameLessWindow)
{
    ui->setupUi(this);
    ui->titleBar->setStyleSheet("QPushButton{ border:none; }");
    setResizeableAreaWidth(8);
    setWindowFlags(Qt::FramelessWindowHint);
    setTitleBar(ui->titleBar);
    showMaximize = true;
    changeMaximizeButton();
    setTitlebarModel(BLACK);
}

FrameLessWindow::~FrameLessWindow()
{
    // 销毁分隔符的内存
    for(int i = 0; i < separateList.size(); i++){
        delete separateList.at(i);
    }
    delete ui;
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
            ui->maximize->setHidden(true);
            ui->restore->setHidden(false);
        }else{
            ui->maximize->setHidden(false);
            ui->restore->setHidden(true);
        }
    }else{
        ui->maximize->setHidden(true);
        ui->restore->setHidden(true);
    }
}

void FrameLessWindow::changeMinimizeButton(bool show)
{
    if(show){
        ui->minimize->setHidden(false);
    }else{
        ui->minimize->setHidden(true);
    }
}

void FrameLessWindow::changeCloseButton(bool show)
{
    if(show){
        ui->closeButton->setHidden(false);
    }else{
        ui->closeButton->setHidden(true);
    }
}

void FrameLessWindow::setTitlebarModel(Model type)
{
    nowModel = type;
    switch(type){
    case BLACK:
        ui->closeButton->setIcon(QIcon(":/titleBar/Close_black.png"));
        ui->maximize->setIcon(QIcon(":/titleBar/Maximize_black.png"));
        ui->restore->setIcon(QIcon(":/titleBar/Restore_black.png"));
        ui->minimize->setIcon(QIcon(":/titleBar/Minimize_black.png"));
        setCloseButtonColor("#AE1C1C", "#450B0B");
        setMaximizeButtonColor("#272727", "#020202");
        setMinimizeButtonColor("#272727", "#020202");
        setTitleColor("#ffffff");
        break;
    case WHITE:
        ui->closeButton->setIcon(QIcon(":/titleBar/Close.png"));
        ui->maximize->setIcon(QIcon(":/titleBar/Maximize.png"));
        ui->restore->setIcon(QIcon(":/titleBar/Restore.png"));
        ui->minimize->setIcon(QIcon(":/titleBar/Minimize.png"));
        setCloseButtonColor("#C42B1C", "#C84031");
        setMaximizeButtonColor("#E9E9E9", "#EDEDED");
        setMinimizeButtonColor("#E9E9E9", "#EDEDED");
        setTitleColor("#000000");
        break;
    }
}

void FrameLessWindow::setCloseButtonColor(QString hover, QString pressed)
{
    ui->closeButton->setStyleSheet("QPushButton:hover {background-color:"+hover+";} QPushButton:pressed {background-color:"+pressed+";}");
}

void FrameLessWindow::setMaximizeButtonColor(QString hover, QString pressed)
{
    ui->maximize->setStyleSheet("QPushButton:hover {background-color:"+hover+";} QPushButton:pressed {background-color:"+pressed+";}");
    ui->restore->setStyleSheet("QPushButton:hover {background-color:"+hover+";} QPushButton:pressed {background-color:"+pressed+";}");
}

void FrameLessWindow::setMinimizeButtonColor(QString hover, QString pressed)
{
    ui->minimize->setStyleSheet("QPushButton:hover {background-color:"+hover+";} QPushButton:pressed {background-color:"+pressed+";}");
}

void FrameLessWindow::setTitle(QString title)
{
    ui->title->setText(title);
}

void FrameLessWindow::setIcon(QPixmap icon)
{
    ui->icon->setPixmap(icon.scaled(QSize(16, 16)));
}

void FrameLessWindow::setTitleColor(QString color)
{
    ui->title->setStyleSheet("color:" + color + ";");
}

void FrameLessWindow::addWidget(QWidget *widget, int index)
{
    if(index >= 0){
        ui->horizontalLayout->insertWidget(index, widget);
    }else{
        ui->horizontalLayout->addWidget(widget);
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
    ui->titleBar->raise();
}

void FrameLessWindow::setBackground(QString color)
{
    ui->titleBar->setStyleSheet("#titleBar{ background-color: " + color + "; } QPushButton{ border:none; }");
}

void FrameLessWindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::WindowStateChange){
        changeMaximizeButton();
        if (windowState() & Qt::WindowMaximized){
            // 窗口最大化，我屏幕是1920，走到这里后，titleBar的宽度会变成1936，所以需要-16
            QTimer::singleShot(50, [=]{
                ui->titleBar->resize(ui->titleBar->width() - 16, ui->titleBar->height());
            });
        }
    }

    QWidget::changeEvent(event);
}

void FrameLessWindow::resizeEvent(QResizeEvent *event)
{
    ui->titleBar->resize(width(), ui->titleBar->height());
    QWidget::resizeEvent(event);
}

void FrameLessWindow::on_closeButton_clicked()
{
    close();
}

void FrameLessWindow::on_maximize_clicked()
{
    showMaximized();
}

void FrameLessWindow::on_minimize_clicked()
{
    showMinimized();
}

void FrameLessWindow::on_restore_clicked()
{
    showNormal();
}
