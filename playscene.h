#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include "coin.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class PlayScene; }
QT_END_NAMESPACE

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    PlayScene(int levelNumber);
    ~PlayScene();

    virtual void paintEvent(QPaintEvent *event);

    int levelNumber;//记录关卡数

    int gameArray[4][4];//二维数组，维护每个关卡的具体数据

    Coin * coin[4][4];

    bool isProcessing = false;//防止重复点击

private:
    Ui::PlayScene *ui;

signals:
    //自定义信号
    void playSceneQuit();
};

#endif // PLAYSCENE_H
