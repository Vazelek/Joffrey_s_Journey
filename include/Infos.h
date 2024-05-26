#ifndef INFOS_H
#define INFOS_H

#include <QWidget>
#include <QLabel>
#include <QGraphicsProxyWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QImage>
#include "MyScene.h"
#include "Player.h"

class Infos : public QGraphicsProxyWidget{
    Q_OBJECT

private:
    MyScene* scene;
    Player* player;
    QLabel* chronometer;
    QLabel* coins;
    QLabel* deaths;
    QLabel* jump;
    QLabel* dash;
    QLabel* shield;
    int width;
    int height;
    double seconds;
    int minutes;


public:
    Infos(MyScene* scene, Player* player, QGraphicsItem* parent = nullptr);
    ~Infos();
    void update();
    int getMinutes();
    double getSeconds();
    void updateSkills();
    void toZero();
};

#endif