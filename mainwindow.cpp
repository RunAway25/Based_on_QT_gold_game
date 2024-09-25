#include <QPainter>
#include <QTimer>
#include <QSound>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mypushbutton.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //配置开始界面
    //设置固定大小
    setFixedSize(350,600);
    //设置图标
    setWindowIcon(QIcon(":/image/image/CoinApp.ico"));
    //设置标题
    setWindowTitle("翻金币游戏");
    //退出按钮功能实现
    connect(ui->actionquit,&QAction::triggered,this,[=](){
        this->close();//关闭该窗口，释放资源，发送关闭信号，若为顶层窗口则会直接关闭程序
    });

    //开始按钮
    MyPushButton * startButton = new MyPushButton(":/image/image/MenuSceneStartButton.png");
    startButton->setParent(this);
    startButton->move(this->width()*0.5-startButton->width()/2,this->height()*0.65);

    //创建音乐对象
    QSound * startSound = new QSound(":/music/music/TapButtonSound.wav",this);
    QSound * backSound = new QSound(":/music/music/BackButtonSound.wav",this);

    //创建选择关卡的对象
    selectlevel =  new SelectLevel;

    //接受关卡选择界面的自定义信号，如果接收到则返回开始界面
    connect(selectlevel,&SelectLevel::selectLevelQuit,this,[=](){
        backSound->play();

        //延迟0.3秒，进入下一界面
        QTimer::singleShot(300,this,[=](){
            this->setGeometry(selectlevel->geometry());
            selectlevel->hide();
            this->show();
        });
    });

    //点击开始按钮，进入关卡选择界面
    connect(startButton,&MyPushButton::clicked,this,[=](){
        //启用按钮动画
        startButton->jumpUp();
        startButton->jumpDown();

        startSound->play();//播放音效

        //延迟0.3秒，进入下一界面
        QTimer::singleShot(300,this,[=](){
            selectlevel->setGeometry(this->geometry());
            this->hide();//隐藏当前界面，不释放资源
            selectlevel->show();//显示关卡选择界面
        });
    });
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);//创建画家
    //加载图片
    QPixmap pixmap;
    pixmap.load(":/image/image/PlayLevelSceneBg.png");
    //画背景图
    painter.drawPixmap(0,0,this->width(),this->height(),pixmap);

    //添加左上角图标
    pixmap.load(":/image/image/Title.png");
    //改变图标大小
    pixmap = pixmap.scaled(pixmap.width()*0.6,pixmap.height()*0.6);
    painter.drawPixmap(0,30,pixmap);

}

MainWindow::~MainWindow()
{
    delete ui;
}
