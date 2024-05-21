#ifndef EVENTITEM_H
#define EVENTITEM_H

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QString>
#include "include/MyScene.h"
#include "include/Player.h"

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
    virtual void toInitialState();
};

#include "include/Coin.h"
#include "include/Flag.h"
#include "include/ArrowThrower.h"
#include "include/Arrow.h"

#endif