#ifndef ARROW_UP_H
#define ARROW_UP_H

#include "Arrow.h"

class ArrowUp : public Arrow{

private:
    int final_y;
    float speed;
public:
    ArrowUp(MyScene* scene, Player* player, int x, int y, int final_y, float speed = 3);
    ~ArrowUp();
    virtual unsigned short int  move();
    virtual void update();
};

#endif