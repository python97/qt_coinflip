#ifndef MYCOIN_H
#define MYCOIN_H
#include <QTimer>
#include <QPushButton>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    MyCoin(QString imgPath);
    int posX; //x坐标
    int posY; //y坐标
    bool flag; //正反标志
    QTimer *time1;
    void changeFlag();//改变标志，执行翻转效果
    //重写鼠标按下事件
    void mousePressEvent(QMouseEvent *e);
    bool isWin = false;//判断是否胜利
private:
    int min = 1;
    int max = 8;
    bool isAnimation = false; //设置动画是否在执行的标志

signals:

public slots:
};

#endif // MYCOIN_H
