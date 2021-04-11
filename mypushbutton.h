#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>
#include <QPropertyAnimation>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    //normalImg 按钮按下前 pressImg 按钮按下后
    MyPushButton(QString normalImg,QString pressImg = "");
    void zoom1();
    void zoom2();
    //重写鼠标按下、释放事件
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
private:
    QString normalImgPath,pressedImgPath;
signals:

public slots:
};

#endif // MYPUSHBUTTON_H
