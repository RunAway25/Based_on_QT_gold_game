#ifndef COIN_H
#define COIN_H

#include <QPushButton>
#include <QTimer>

class Coin : public QPushButton
{
    Q_OBJECT
public:
    Coin(QString path);

    //金币属性
    int x;//x轴坐标
    int y;//y轴坐标
    bool flag;//正反标志

    //改变标志的方法
    void changeFlag();

    QTimer * timer1;
    QTimer * timer2;
    int max = 7;
    int min = 2;

    bool isAnimation = true;

    bool isWin = false;

signals:
};

#endif // COIN_H
