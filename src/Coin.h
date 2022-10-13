#ifndef COIN_H
#define COIN_H

#include "EventItem.h"

class MyScene;
class Player;

class Coin : public EventItem{

private:
public:
    Coin(MyScene* scene, Player* player, int x, int y);
    ~Coin();
    virtual void update();
    virtual void toInitialState();
};

#endif