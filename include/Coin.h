#ifndef COIN_H
#define COIN_H

#include "EventItem.h"
#include "SpecialInitialStateEventItem.h"

class MyScene;
class Player;

class Coin : public EventItem, public SpecialInitialStateEventItem{

private:
public:
    Coin(MyScene* scene, Player* player, int x, int y);
    ~Coin();
    virtual void update();
    virtual void toInitialState();
};

#endif