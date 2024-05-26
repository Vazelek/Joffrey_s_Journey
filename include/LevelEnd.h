#ifndef LEVELEND_H
#define LEVELEND_H

#include <QGraphicsProxyWidget>
#include <QGraphicsItem>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include "MyScene.h"
#include "Player.h"
#include "Infos.h"

class MyScene;
class Player;
class Infos;
class Menu;

class LevelEnd : public QGraphicsProxyWidget{
    Q_OBJECT

private:
    MyScene* scene;
    Player* player;
    Infos* infos;
    Menu* menu;
    int width;
    int height;
    int animation_status;
    int animation_direction;
    QLabel* moving_player;
public:
    LevelEnd(MyScene* scene, Player* player, Infos* infos, Menu* menu, QGraphicsItem* parent = nullptr);
    ~LevelEnd();
    void updatePos();

public slots:
    void exit();
    void restart();
    void updatePlayer();
};

#endif