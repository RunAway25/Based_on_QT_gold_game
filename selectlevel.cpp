#include <QPainter>
#include <QPixmap>
#include <QLabel>
#include <QTimer>
#include <QDebug>
#include <QSound>
#include "selectlevel.h"
#include "ui_selectlevel.h"
#include "mypushbutton.h"

SelectLevel::SelectLevel(QWidget *parent)
    : QMainWindow{parent}
    , ui(new Ui::SelectLevel)
{
    ui->setupUi(this);

    //设置关卡选择界面的场景
    setFixedSize(350,600);//设置固定大小
    setWindowIcon(QIcon(":/image/image/CoinApp.ico"));//设置图标
    setWindowTitle("翻金币游戏");//设置标题
    //退出按钮实现
    connect(ui->actionquit,&QAction::triggered,this,[=](){
        this->close();
    });

    //返回按钮功能实现
    MyPushButton * quitButton = new MyPushButton(":/image/image/BackButton.png",":/image/image/BackButtonSelected.png");
    quitButton->setParent(this);
    quitButton->move(this->width()-quitButton->width(),this->height()-quitButton->height());

    connect(quitButton,&MyPushButton::clicked,this,[=](){
        emit this->selectLevelQuit();//发送关闭关卡选择界面关闭的信号
    });

    //创建音乐对象
    QSound * startSound = new QSound(":/music/music/TapButtonSound.wav",this);

    for(int i=0;i<20;i++)
    {
        MyPushButton * levelButton = new MyPushButton(":/image/image/LevelIcon.png");
        levelButton->setParent(this);
        levelButton->move(35+i%4*75,160+i/4*75);//一个for循环创建二维矩阵

        QLabel * label = new QLabel(levelButton);
        label->setFixedSize(levelButton->width(),levelButton->height());
        label->setText(QString::number(i+1));
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);//设置水平垂直居中
        label->setAttribute(Qt::WA_TransparentForMouseEvents);//设置鼠标穿透属性

        connect(levelButton,&MyPushButton::clicked,this,[=](){
            //设置点击关卡选择时的动画
            levelButton->jumpUp();
            levelButton->jumpDown();
            startSound->play();//播放音效
            QTimer::singleShot(300,this,[=](){
                this->hide();//隐藏关卡选择界面
                play = new PlayScene(i+1);//创建关卡界面
                play->setGeometry(this->geometry());
                play->show();//显示关卡界面

                connect(play,&PlayScene::playSceneQuit,this,[=](){
                    QTimer::singleShot(300,this,[=](){
                        this->setGeometry(play->geometry());
                        this->show();
                        delete play;
                        play = nullptr;
                    });
                });
            });
        });
    }
}

void SelectLevel::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pixmap;

    pixmap.load(":/image/image/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pixmap);

    pixmap.load(":/image/image/Title.png");
    painter.drawPixmap((this->width()-pixmap.width())*0.5,30,pixmap.width(),pixmap.height(),pixmap);
}

SelectLevel::~SelectLevel()
{
    delete ui;
}
