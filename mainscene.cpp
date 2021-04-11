#include "mainscene.h"
#include "ui_mainscene.h"
#include <QPainter>
#include <QTimer>
#include <QSound>
#include <QMediaPlayer>
MainScene::MainScene(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainScene)
{
    ui->setupUi(this);
    this->setFixedSize(390,570);
    this->setWindowIcon(QPixmap(":/rec/Coin0001.png"));
    this->setWindowTitle("老王带你翻金币");
    //设置开始按钮的音效
    QSound *startSound = new QSound(":/rec/TapButtonSound.wav");
    //设置返回按钮的音效
    QSound *backSound = new QSound(":/rec/BackButtonSound.wav");
    //设置全程背景音乐
    QMediaPlayer *backendSound = new QMediaPlayer(this);
//    backendSound->setMedia(QUrl::fromLocalFile("G:\\QT_Creater\\Newyear2021\\CoinFlip\\rec\\disappointed.mp3"));
    backendSound->setMedia(QUrl("qrc:/rec/disappointed.mp3"));
    backendSound->play();
    connect(ui->actionquit,&QAction::triggered,[=](){
        this->close();
    });

    MyPushButton *startBtn = new MyPushButton(":/rec/MenuSceneStartButton.png");
    chooseselectscene *chooseScene = new chooseselectscene;
    startBtn->setParent(this);
    startBtn->move(this->width()*0.5-startBtn->width()*0.5,this->height()*0.7);
    //监听选择关卡点击返回按钮的信号
    connect(chooseScene,&chooseselectscene::chooseScenceBack,[=](){
        this->setGeometry(chooseScene->geometry());
        backSound->play();
        chooseScene->hide();
        this->show();
    });
    connect(startBtn,&MyPushButton::clicked,[=](){
        //播放点击开始音效
        chooseScene->setGeometry(this->geometry());
        startSound->play();
        startBtn->zoom1();
        startBtn->zoom2();
        //延迟0.5秒执行
        QTimer::singleShot(500,this,[=](){
            //自身隐藏
            this->hide();
            //显示关卡选择场景
            chooseScene->show();
        });
    });


}

MainScene::~MainScene()
{
    delete ui;
}

void MainScene::paintEvent(QPaintEvent *event){
    //创建画家
    QPainter painter(this);
    //创建QPixmap对象
    QPixmap pix;
    //加载图片
    pix.load(":/rec/PlayLevelSceneBg.png");
    //显示图片
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //加载标题
    pix.load(":/rec/Title.png");
    pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix.width(),pix.height(),pix);
}

