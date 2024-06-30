#ifndef ARROW_H
#define ARROW_H

#include "EventItem.h"

class Arrow : public EventItem{

public:
    Arrow(MyScene* scene, Player* player, int x, int y, QString resource_url);
    ~Arrow();
    virtual unsigned short int move();
    virtual void update();
    virtual void toInitialState();
};


#include "ArrowDown.h"
#include "ArrowUp.h"
#include "ArrowLeft.h"
#include "ArrowRight.h"

#endif