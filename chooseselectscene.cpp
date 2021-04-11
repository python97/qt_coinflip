#include "chooseselectscene.h"
#include <QMenuBar>
#include <QMenu>
#include <QPainter>
#include <QTimer>
#include <QLabel>
#include <QSound>
chooseselectscene::chooseselectscene(QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize(390,570);
    this->setWindowIcon(QPixmap(":/rec/Coin0001.png"));
    this->setWindowTitle("老王带你翻金币");
    //创建菜单栏
    QMenuBar *menubar = menuBar();
    QMenu *start = menubar->addMenu("开始");
    QAction *quit = new QAction(tr("退出"));
    start->addAction(quit);
    connect(quit,&QAction::triggered,[=](){
        this->close();
    });
    //返回按钮
    MyPushButton *backBtn = new MyPushButton(":/rec/BackButton.png",":/rec/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());
    //设置选中关卡后的音效
    QSound *selectSound = new QSound(":/rec/TapButtonSound.wav");

    //点击返回
    connect(backBtn,&MyPushButton::clicked,[=](){
        //切换图片，按下一个图，释放原来的图

        QTimer::singleShot(200,this,[=](){
            emit chooseScenceBack();
        });

    });

    //创建选择关卡的按钮
    for(int i=0;i<20;i++){
        MyPushButton *btn = new MyPushButton(":/rec/LevelIcon.png");
        btn->setParent(this);
        btn->move(65+(i%4)*70,130+(i/4)*70);

        //建立每一个关卡按钮的监听事件
        connect(btn,&MyPushButton::clicked,[=](){
            if(pScene == NULL){

                selectSound->play();
                this->hide(); //选关场景隐藏
                //这个场景放里面，是因为每一关的场景都不一样
                pScene = new PlayScene(i+1);
                pScene->show();

                //设置游戏场景位置
                pScene->setGeometry(this->geometry());
                //这个连接放里面，保证pScene不为NULL
                connect(pScene,&PlayScene::scenceBack,[=](){
                    this->setGeometry(pScene->geometry());
                    this->show();
                    delete pScene;
                    pScene = NULL;
                });
            }
        });

        QLabel *label = new QLabel;
        label->setParent(this);
        label->setFixedSize(btn->width(),btn->height());

        label->setText(QString::number(i+1));
        label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        label->move(65+(i%4)*70,130+(i/4)*70);
        //设置鼠标穿透
        label->setAttribute(Qt::WA_TransparentForMouseEvents);
    }
}

void chooseselectscene::paintEvent(QPaintEvent *){
    //创建画家
    QPainter painter(this);
    //创建QPixmap对象
    QPixmap pix;
    //加载图片
    pix.load(":/rec/OtherSceneBg.png");
    //显示图片
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //加载标题
    pix.load(":/rec/Title.png");
    pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix.width(),pix.height(),pix);
}


