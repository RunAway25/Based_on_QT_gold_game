#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>
#include <QMouseEvent>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    //构造函数，参数1：正常图片显示；参数2：按下后显示的图片
    MyPushButton(QString normalImg,QString pressImg = "");

    QString normalImg;
    QString pressImg;

    //弹跳特效
    void jumpUp();
    void jumpDown();

    //鼠标按下事件
    void mousePressEvent(QMouseEvent *e);

    //鼠标释放事件
    void mouseReleaseEvent(QMouseEvent *e);

signals:
};

#endif // MYPUSHBUTTON_H
