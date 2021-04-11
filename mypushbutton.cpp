#include "mypushbutton.h"
#include <QDebug>


MyPushButton::MyPushButton(QString normalImg, QString pressImg){
    normalImgPath = normalImg;
    pressedImgPath = pressImg;

    QPixmap pix;
    bool ret = pix.load(normalImgPath);
    if (ret == false){
        qDebug()<<"加载图片失败";
    }
    this->setFixedSize( pix.width(), pix.height() );
    //设置不规则图片的样式表
    this->setStyleSheet("QPushButton{border-style:none;}");
    //设置图标
    this->setIcon(pix);
    //设置图标大小
    this->setIconSize(QSize(pix.width(),pix.height()));

}

void MyPushButton::zoom1(){
    //创建动态对象
    QPropertyAnimation *animation = new QPropertyAnimation(this,"geometry");
    //设置动画时间间隔
    animation->setDuration(200);
    //设置起始位置
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //设置结束位置
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //执行动画
    animation->start();
}
void MyPushButton::zoom2(){
    //创建动态对象
    QPropertyAnimation *animation = new QPropertyAnimation(this,"geometry");
    //设置动画时间间隔
    animation->setDuration(200);
    //设置起始位置
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //设置结束位置
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //执行动画
    animation->start();
}
void MyPushButton::mousePressEvent(QMouseEvent *e){
    //判断是哪种按钮，开始按钮不调用此函数
    if(this->pressedImgPath != ""){
        QPixmap pix;
        bool ret = pix.load(this->pressedImgPath);
        if (ret == false){
            qDebug()<<"加载图片失败";
        }
        this->setFixedSize( pix.width(), pix.height() );
        //设置不规则图片的样式表
        this->setStyleSheet("QPushButton{border-style:none;}");
        //设置图标
        this->setIcon(pix);
        //设置图标大小
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    //让父类执行其他内容
    return QPushButton::mousePressEvent(e);
}

void MyPushButton::mouseReleaseEvent(QMouseEvent *e){
    //判断是哪种按钮，开始按钮不调用此函数
    if(this->pressedImgPath != ""){
        QPixmap pix;
        bool ret = pix.load(this->normalImgPath);
        if (ret == false){
            qDebug()<<"加载图片失败";
        }
        this->setFixedSize( pix.width(), pix.height() );
        //设置不规则图片的样式表
        this->setStyleSheet("QPushButton{border-style:none;}");
        //设置图标
        this->setIcon(pix);
        //设置图标大小
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    return QPushButton::mouseReleaseEvent(e);
}
