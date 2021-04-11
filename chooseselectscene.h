#ifndef CHOOSESELECTSCENE_H
#define CHOOSESELECTSCENE_H

#include <QMainWindow>
#include <mypushbutton.h>
#include <playscene.h>
class chooseselectscene : public QMainWindow
{
    Q_OBJECT
public:
    explicit chooseselectscene(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);

private:
    PlayScene *pScene = NULL;
signals:
    //自定义一个信号，告诉主场景 点击了返回
    void chooseScenceBack();

public slots:
};

#endif // CHOOSESELECTSCENE_H
