#include <QLabel>
#include <QFont>
#include <QPainter>
#include <QPainter>
#include <QPixmap>
#include <QTimer>
#include <QDebug>
#include <QPropertyAnimation>
#include <QSound>
#include "mypushbutton.h"
#include "playscene.h"
#include "ui_playscene.h"
#include "coin.h"
#include "dataconfig.h"

PlayScene::PlayScene(int levelNumber)
    : ui(new Ui::PlayScene)
{
    ui->setupUi(this);

    this->levelNumber = levelNumber;

    //配置关卡内场景
    this->setFixedSize(350,600);
    this->setWindowIcon(QIcon(":/image/image/CoinApp.ico"));//设置图标
    this->setWindowTitle("翻金币游戏");//设置标题

    //退出按钮功能实现
    connect(ui->actionquit,&QAction::triggered,this,[=](){
        this->close();
    });

    //放置返回按钮
    MyPushButton * quitButton = new MyPushButton(":/image/image/BackButton.png",":/image/image/BackButtonSelected.png");
    quitButton->setParent(this);
    quitButton->move(this->width()-quitButton->width(),this->height()-quitButton->height());

    //返回按钮功能实现
    connect(quitButton,&MyPushButton::clicked,this,[=](){
        emit this->playSceneQuit();//发送关闭关卡界面关闭的信号
    });

    //显示当前关卡数
    QLabel * label = new QLabel(this);
    QFont font;//创建字体对象
    font.setFamily("华文新魏");//设置字体样式
    font.setPointSize(21);//设置字号
    QString str = QString("Level：%1").arg(this->levelNumber);
    label->setFont(font);//将label的字体设置为font
    label->setText(str);
    label->setGeometry(30,this->height()-50,130,50);

    //初始化每个关卡的二维数组
    dataConfig config;
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            this->gameArray[i][j] = config.mData[this->levelNumber][i][j];
        }
    }

    //胜利图片显示
    QLabel * winLabel = new QLabel(this);
    QPixmap winPixmap;
    winPixmap.load(":/image/image/LevelCompletedDialogBg.png");
    winLabel->setFixedSize(winPixmap.size());
    winLabel->setPixmap(winPixmap);
    winLabel->move((this->width()-winPixmap.width())*0.5,-winLabel->height());

    //创建动画对象
    QPropertyAnimation * animation = new QPropertyAnimation(winLabel,"geometry");
    animation->setDuration(800);
    animation->setStartValue(QRect((this->width()-winPixmap.width())*0.5,-winLabel->height(),winLabel->width(),winLabel->height()));
    animation->setEndValue(QRect((this->width()-winPixmap.width())*0.5,winLabel->height(),winLabel->width(),winLabel->height()));
    animation->setEasingCurve(QEasingCurve::OutBounce);

    //创建音效对象
    QSound * filpSound = new QSound(":/music/music/ConFlipSound.wav",this);
    QSound * winSound = new QSound(":/music/music/LevelWinSound.wav",this);

    //显示金币背景图
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            QLabel * label = new QLabel(this);
            QPixmap pixmap;
            pixmap.load(":/image/image/BoardNode.png");
            pixmap = pixmap.scaled(pixmap.width()*1.1,pixmap.height()*1.1);
            label->setFixedSize(pixmap.width(),pixmap.height());
            label->setPixmap(pixmap);
            label->move(60+i*60,180+j*60);

            //创建金币
            QString str;
            if(this->gameArray[i][j] == 1)
            {
                str = ":/image/image/Coin0001.png";
            }
            else
            {
                str = ":/image/image/Coin0008.png";
            }

            //创建金币
            Coin * coin = new Coin(str);
            coin->setParent(this);
            coin->move(63+i*60,184+j*60);

            //将金币放入二维数组，方便维护
            this->coin[i][j] = coin;

            //给金币属性赋值
            coin->flag = this->gameArray[i][j];//1是金币面，0是银币面

            //监听金币点击事件
            connect(coin,&Coin::clicked,this,[=](){
                if (this->isProcessing) return;
                this->isProcessing = true;

                filpSound->play();

                coin->changeFlag();
                this->gameArray[i][j] = this->gameArray[i][j]==0?1:0;

                //周围延迟翻转
                QTimer::singleShot(300,this,[=](){
                    if(i<3)//右侧翻转
                    {
                        this->coin[i+1][j]->changeFlag();//翻转图片
                        this->gameArray[i+1][j] = this->gameArray[i+1][j]==0?1:0;//修改矩阵内对应图片的值
                    }
                    if(i>0)//左侧翻转
                    {
                        this->coin[i-1][j]->changeFlag();
                        this->gameArray[i-1][j] = this->gameArray[i-1][j]==0?1:0;
                    }
                    if(j<3)//上方翻转
                    {
                        this->coin[i][j+1]->changeFlag();
                        this->gameArray[i][j+1] = this->gameArray[i][j+1]==0?1:0;
                    }
                    if(j>0)//下方翻转
                    {
                        this->coin[i][j-1]->changeFlag();
                        this->gameArray[i][j-1] = this->gameArray[i][j-1]==0?1:0;

                    }
                    //判断是否胜利
                    int count = 0;
                    for(int i = 0; i < 4; i++) {
                        for(int j = 0; j < 4; j++) {
                            if(this->gameArray[i][j] == 1) {
                                count++;
                            }
                        }
                    }

                    if(count == 16) {
                        for (int i = 0; i < 4; i++) {
                            for (int j = 0; j < 4; j++) {
                                this->coin[i][j]->disconnect();//断开所有金币的信号连接
                                animation->start();//启动胜利画面
                                winSound->play();//播放音效
                            }
                        }
                    }
                    this->isProcessing = false;
                });
            });
        }
    }
}

void PlayScene::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pixmap;

    pixmap.load(":/image/image/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pixmap);

    pixmap.load(":/image/image/Title.png");
    pixmap = pixmap.scaled(pixmap.width()*0.6,pixmap.height()*0.6);
    painter.drawPixmap(0,30,pixmap);
}

PlayScene::~PlayScene()
{
    delete ui;
}
