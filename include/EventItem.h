#ifndef EVENTITEM_H
#define EVENTITEM_H

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QString>
#include "MyScene.h"
#include "Player.h"

class MyScene;
class Player;

class EventItem : public QGraphicsPixmapItem{

protected:
    bool used;
    MyScene* scene;
    Player* player;

public:
    EventItem(MyScene* scene, Player* player, int x, int y, QString ressource_url);
    ~EventItem();
    virtual void update() = 0;
};

#include "Coin.h"
#include "Flag.h"
#include "Arrow.h"
#include "ArrowThrower.h"

#endif