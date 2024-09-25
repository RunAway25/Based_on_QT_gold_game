#ifndef SELECTLEVEL_H
#define SELECTLEVEL_H

#include <QMainWindow>
#include "playscene.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class SelectLevel; }
QT_END_NAMESPACE

class SelectLevel : public QMainWindow
{
    Q_OBJECT
public:
    explicit SelectLevel(QWidget *parent = nullptr);
    ~SelectLevel();

    //重写绘图事件
    virtual void paintEvent(QPaintEvent *event);

    //创建关卡指针
    PlayScene * play = nullptr;

private:
    Ui::SelectLevel *ui;

signals:
    //自定义信号
    void selectLevelQuit();
};

#endif // SELECTLEVEL_H
