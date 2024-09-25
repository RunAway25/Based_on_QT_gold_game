#include <QDebug>
#include <QPropertyAnimation>
#include "mypushbutton.h"

MyPushButton::MyPushButton(QString normalImg,QString pressImg)
{
    this->normalImg = normalImg;
    this->pressImg = pressImg;

    QPixmap pixmap;
    bool ret = pixmap.load(normalImg);

    if(!ret)
    {
        qDebug()<<"图片加载失败！";
        return;
    }

    this->setFixedSize(pixmap.width(),pixmap.height());//设置按钮固定大小
    this->setStyleSheet("QPushButton{border:0px}");//设置不规则图片样式
    this->setIcon(pixmap);//设置图标
    this->setIconSize(QSize(pixmap.width(),pixmap.height()));//设置图标大小
}

//向上跳
void MyPushButton::jumpUp()
{
    //创建动画对象
    QPropertyAnimation * animation = new QPropertyAnimation(this,"geometry");
    //设置动画持续时间
    animation->setDuration(50);
    //起始位置
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //结束位置
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //执行动画
    animation->start();
}

//向下跳
void MyPushButton::jumpDown()
{
    //创建动画对象
    QPropertyAnimation * animation = new QPropertyAnimation(this,"geometry");
    //设置动画持续时间
    animation->setDuration(50);
    //起始位置
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //结束位置
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //执行动画
    animation->start();
}

//鼠标按下事件
void MyPushButton::mousePressEvent(QMouseEvent *e)
{
    if(this->pressImg != "")//如果传入的按下图片不为空，说明有按下状态，切换为该状态的图片
    {
        QPixmap pixmap;
        bool ret = pixmap.load(this->pressImg);

        if(!ret)
        {
            qDebug()<<"图片加载失败！";
        }

        this->setFixedSize(pixmap.width(),pixmap.height());
        this->setStyleSheet("QPushButton{border:0px}");
        this->setIcon(pixmap);
        this->setIconSize(QSize(pixmap.width(),pixmap.height()));
    }

    return QPushButton::mousePressEvent(e);//其他的正常处理
}

//鼠标释放事件
void MyPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    if(this->pressImg != "")//如果传入的按下图片不为空，说明有按下状态，切换为该状态的图片
    {
        QPixmap pixmap;
        bool ret = pixmap.load(this->normalImg);

        if(!ret)
        {
            qDebug()<<"图片加载失败！";
        }

        this->setFixedSize(pixmap.width(),pixmap.height());
        this->setStyleSheet("QPushButton{border:0px}");
        this->setIcon(pixmap);
        this->setIconSize(QSize(pixmap.width(),pixmap.height()));
    }

    return QPushButton::mouseReleaseEvent(e);//其他的正常处理
}
