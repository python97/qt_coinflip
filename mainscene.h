#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QMainWindow>
#include <mypushbutton.h>
#include <chooseselectscene.h>

namespace Ui {
class MainScene;
}

class MainScene : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainScene(QWidget *parent = nullptr);
    ~MainScene();
    void paintEvent(QPaintEvent *event);

private:
    Ui::MainScene *ui;
};

#endif // MAINSCENE_H
