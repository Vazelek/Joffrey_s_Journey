#ifndef ARROW_RIGHT_H
#define ARROW_RIGHT_H

#include "Arrow.h"

class ArrowRight : public Arrow{

private:
    int final_x;
    float speed;
public:
    ArrowRight(MyScene* scene, Player* player, int x, int y, int final_x, float speed = 3);
    ~ArrowRight();
    virtual unsigned short int  move();
    virtual void update();
};

#endif