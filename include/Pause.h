#ifndef PAUSE_H
#define PAUSE_H

#include <QGraphicsProxyWidget>
#include <QGraphicsItem>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include "include/MyScene.h"
#include "include/Player.h"

class MyScene;
class Player;

class Pause : public QGraphicsProxyWidget{
    Q_OBJECT

private:
    MyScene* scene;
    Player* player;
    int width;
    int height;
public:
    Pause(MyScene* scene, Player* player, QGraphicsItem* parent = nullptr);
    ~Pause();
    void updatePos();

public slots:
    void exit();
    void restart();
    void kill();
};

#endif