#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include <mypushbutton.h>
#include <mycoin.h>
#include <dataconfig.h>
class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
//    explicit PlayScene(QWidget *parent = nullptr);
    PlayScene(int i);
    void paintEvent(QPaintEvent *event);
private:
    //记录关卡索引
    int levelIndex;
    //二维数组 记录是金币还是银币 0和1
    int gameArray[4][4];
    //二维数据，保存金币
    MyCoin *coinBtn[4][4];
    bool isWin = true;//判断是否胜利
signals:
    void scenceBack();

public slots:
};

#endif // PLAYSCENE_H
