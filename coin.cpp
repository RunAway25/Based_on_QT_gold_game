#include <QDebug>
#include "coin.h"

Coin::Coin(QString path)
{
    QPixmap pixmap;
    bool ret = pixmap.load(path);

    if(!ret)
    {
        qDebug()<<"图片加载失败";
    }
    pixmap = pixmap.scaled(pixmap.width()*1.05,pixmap.height()*1.05);
    this->setFixedSize(pixmap.width(),pixmap.height());
    this->setStyleSheet("QPushButton{border:0px}");
    this->setIcon(pixmap);
    this->setIconSize(this->size());

    this->timer1 = new QTimer(this);
    this->timer2 = new QTimer(this);

    //监听定时器发射的信号
    connect(timer1,&QTimer::timeout,this,[=](){
        QPixmap pixmap;
        QString str = QString(":/image/image/Coin000%1.png").arg(this->min++);
        pixmap.load(str);
        pixmap = pixmap.scaled(pixmap.width()*1.05,pixmap.height()*1.05);
        this->setFixedSize(pixmap.width(),pixmap.height());
        this->setStyleSheet("QPushButton{border:0px}");
        this->setIcon(pixmap);
        this->setIconSize(QSize(pixmap.width(),pixmap.height()));

        if(this->min == 9)
        {
            this->min = 1;
            timer1->stop();
            this->isAnimation = true;
        }
    });

    //监听定时器发射的信号
    connect(timer2,&QTimer::timeout,this,[=](){
        QPixmap pixmap;
        QString str = QString(":/image/image/Coin000%1.png").arg(this->max--);
        pixmap.load(str);
        pixmap = pixmap.scaled(pixmap.width()*1.05,pixmap.height()*1.05);
        this->setFixedSize(pixmap.width(),pixmap.height());
        this->setStyleSheet("QPushButton{border:0px}");
        this->setIcon(pixmap);
        this->setIconSize(QSize(pixmap.width(),pixmap.height()));

        if(this->max == 0)
        {
            this->max = 8;
            timer2->stop();
            this->isAnimation = true;
        }
    });
}

void Coin::changeFlag()
{
    if(this->flag & this->isAnimation)
    {
        this->flag = false;
        this->isAnimation = false;
        this->timer1->start(20);//定时器启动,每隔30毫秒发射一个信号
    }
    else if(!this->flag & this->isAnimation)
    {
        this->flag = true;
        this->isAnimation = false;
        this->timer2->start(20);
    }
}
