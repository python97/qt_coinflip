#include "playscene.h"
#include <QPainter>
#include <QMenu>
#include <QMenuBar>
#include <QTimer>
#include <QLabel>
#include <QFont>
#include<QDebug>
#include<QPropertyAnimation>
#include <QSound>
PlayScene::PlayScene(int i){
    this->setFixedSize(390,570);
    this->setWindowIcon(QPixmap(":/rec/Coin0001.png"));
    this->setWindowTitle("翻金币");
    //创建菜单栏
    QMenuBar *menubar = menuBar();
    QMenu *start = menubar->addMenu("开始");
    QAction *quit = new QAction(tr("退出"));
    start->addAction(quit);
    connect(quit,&QAction::triggered,[=](){
        this->close();
    });
    levelIndex = i;

    //翻金币的音效
    QSound *slipSound= new QSound(":/rec/ConFlipSound.wav");
    //胜利的音效
    QSound *winSound = new QSound(":/rec/LevelWinSound.wav");
    //返回按钮
    MyPushButton *backBtn = new MyPushButton(":/rec/BackButton.png",":/rec/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());
    //设置返回按钮的音效
    QSound *backSound = new QSound(":/rec/BackButtonSound.wav");
    //点击返回
    connect(backBtn,&MyPushButton::clicked,[=](){
        //切换图片，按下一个图，释放原来的图
        backSound->play();
        QTimer::singleShot(200,this,[=](){
            this->hide();
            emit this->scenceBack();
        });

    });
    //初始化数组
    dataConfig config;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            gameArray[i][j] = config.mData[this->levelIndex][i][j];
        }
    }

    //加载关卡文字
    QLabel *text = new QLabel;
    text->setParent(this);
    //设置字体
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    //加载字体
    text->setFont(font);
    QString str = QString("Level:%1").arg(this->levelIndex);
    text->setText(str);
    //label默认没有大小
    //第一种
    //text->setFixedSize(150,20);
    //text->move(20,500);
    //第二种，直接同时设置位置和大小
    text->setGeometry(QRect(30, this->height() - 50,120, 50));
    //胜利图片

    QLabel *winLabel = new QLabel;
    QPixmap winpix;
    winpix.load(":/rec/LevelCompletedDialogBg.png");
    winLabel->setGeometry(0,0,winpix.width(),winpix.height());
    winLabel->setPixmap(winpix);
    winLabel->setParent(this);
    winLabel->move(this->width()*0.5-winpix.width()*0.5,-winpix.height());
    //创建金币背景图
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            QLabel *label = new QLabel;
            QPixmap pix;
            pix.load(":/rec/BoardNode(1).png");
            label->setGeometry(0,0,pix.width(),pix.height());
            label->setPixmap(pix);
            label->setParent(this);
            label->move(95+i*50,200+j*50);

            //创建金币对象
            QString img;
            if(gameArray[i][j] == 1){
                img = ":/rec/Coin0001.png";
            }
            else{
                 img = ":/rec/Coin0008.png";
            }
            MyCoin *mycoin = new MyCoin(img);
            mycoin->setParent(this);
            mycoin->move(95+i*50,200+j*50);
            mycoin->posX = i;
            mycoin->posY = j;
            mycoin->flag = this->gameArray[i][j];
            this->coinBtn[i][j] = mycoin;
            //给金币点击事件 ，翻转
            connect(mycoin,&MyCoin::clicked,[=](){
                mycoin->changeFlag();
                this->gameArray[i][j] = this->gameArray[i][j] == 0 ?1 :0;
                slipSound->play();
                //翻转周围金币
                QTimer::singleShot(300,this,[=](){
                    if(mycoin->posX + 1 <=3){ //可翻转下侧金币
                        this->coinBtn[mycoin->posX+1][mycoin->posY]->changeFlag();
                        this->gameArray[mycoin->posX+1][mycoin->posY] = this->gameArray[mycoin->posX+1][mycoin->posY] == 0 ?1 :0;
                    }
                    if(mycoin->posX -1 >=0) //可翻转左侧金币
                    {
                        this->coinBtn[mycoin->posX -1][mycoin->posY]->changeFlag();
                        this->gameArray[mycoin->posX-1][mycoin->posY] = this->gameArray[mycoin->posX-1][mycoin->posY] == 0 ?1 :0;
                    }
                    if(mycoin->posY + 1 <=3)//可翻转下侧金币
                    {
                        this->coinBtn[mycoin->posX][mycoin->posY+1]->changeFlag();
                        this->gameArray[mycoin->posX][mycoin->posY+1] = this->gameArray[mycoin->posX][mycoin->posY+1] == 0 ?1 :0;
                    }
                    if(mycoin->posY - 1 >=0)//可翻转上侧金币
                    {
                        this->coinBtn[mycoin->posX][mycoin->posY-1]->changeFlag();
                        this->gameArray[mycoin->posX][mycoin->posY-1] = this->gameArray[mycoin->posX][mycoin->posY-1] == 0 ?1 :0;
                    }
                    //判断是否胜利
                    this->isWin = true;
                    for(int i=0;i<4;i++){
                        for(int j=0;j<4;j++){
                            if(coinBtn[i][j]->flag == false){
                                this->isWin = false;
                                break;
                            }
                        }
                       }
                    if(this->isWin){
                        //将所有按钮标志改为胜利
                        for(int i=0;i<4;i++){
                            for(int j=0;j<4;j++){
                                coinBtn[i][j]->isWin = true;
                            }}
                        winSound->play();
                        //显示胜利图片
                        QPropertyAnimation *ani = new QPropertyAnimation(winLabel,"geometry");
                        //设置事件间隔
                        ani->setDuration(1000);
                        //设置起始位置
                        ani->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
                        //设置结束位置
                        ani->setEndValue(QRect(winLabel->x(),winLabel->y()+115,winLabel->width(),winLabel->height()));
                        //设置缓和曲线
                        ani->setEasingCurve(QEasingCurve::OutBounce);
                        //执行动画
                        ani->start();

                    }
                });

            });
        }
    }

}

void PlayScene::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/rec/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,pix.width(),pix.height(),pix);

    //加载标题
    pix.load(":/rec/Title.png");
    pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix.width(),pix.height(),pix);
}
