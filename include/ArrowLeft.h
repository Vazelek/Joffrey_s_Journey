#ifndef ARROW_LEFT_H
#define ARROW_LEFT_H

#include "Arrow.h"

class ArrowLeft : public Arrow{

private:
    int final_x;
    float speed;
public:
    ArrowLeft(MyScene* scene, Player* player, int x, int y, int final_x, float speed = 3);
    ~ArrowLeft();
    virtual unsigned short int  move();
    virtual void update();
    virtual void toInitialState();
};

#endif