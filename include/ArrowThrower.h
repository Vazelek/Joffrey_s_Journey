#ifndef ARROWTHROWER_H
#define ARROWTHROWER_H

#include "include/EventItem.h"

class ArrowThrower : public EventItem{

private:
    float initial_delay;
    float delay;
    int final_coord;
    QString orientation;
public:
    ArrowThrower(MyScene* scene, Player* player,int x, int y, QString orientation, int final_coord, float delay);
    ~ArrowThrower();
    virtual void update();
    void throwArrow();
    virtual void toInitialState();
};

#endif