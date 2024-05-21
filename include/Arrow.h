#ifndef ARROW_H
#define ARROW_H

#include "include/EventItem.h"

class Arrow : public EventItem{

private:
    int final_coord;
    QString orientation;
    float speed;
public:
    Arrow(MyScene* scene, Player* player,int x, int y, QString orientation, int final_coord, float speed = 3);
    ~Arrow();
    virtual void update();
    virtual void toInitialState();
};

#endif