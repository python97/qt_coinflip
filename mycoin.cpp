#include "mycoin.h"
#include <QDebug>
#include <QPixmap>
MyCoin::MyCoin(QString imgPath)
{
    QPixmap pix;
    bool ret = pix.load(imgPath);
    if(!ret){
        qDebug()<<"图片加载失败";
    }
    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));
    time1 = new QTimer(this);
    connect(time1,&QTimer::timeout,[=](){
        QPixmap pix1;
         QString str;
        if(!flag){
            str = QString(":/rec/Coin000%1.png").arg(this->min++);
//            qDebug()<<"执行meiyohng翻转";
        }
        else{
//           qDebug()<<"执行翻转";
           str = QString(":/rec/Coin000%1.png").arg(this->max--);
        }
        pix1.load(str);
        this->setFixedSize(pix1.width(),pix1.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix1);
        this->setIconSize(QSize(pix1.width(),pix1.height()));
        //判断如果翻转完了
        if((this->min-1 == this->max) || (this->max+1 == this->min)){
            if(!flag){
                this->min = 1;
            }
            else{
                this->max = 8;
            }

            time1->stop();
            isAnimation = false;


        }

    });
}

void MyCoin::changeFlag(){
    if(this->flag)//正面
    {

        this->flag = false;
        time1->start(100);

        this->isAnimation = true;
    }
    else{

        this->flag = true;
        time1->start(100);

        this->isAnimation = true;
    }
}

//对单个金币而言
void MyCoin::mousePressEvent(QMouseEvent *e){
    if(this->isAnimation || this->isWin){
        return;
    }
    else{
        QPushButton::mousePressEvent(e);
    }
}
