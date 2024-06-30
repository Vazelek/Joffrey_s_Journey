#ifndef ARROW_DOWN_H
#define ARROW_DOWN_H

#include "Arrow.h"

class ArrowDown : public Arrow{

private:
    int final_y;
    float speed;
public:
    ArrowDown(MyScene* scene, Player* player, int x, int y, int final_y, float speed = 3);
    ~ArrowDown();
    virtual unsigned short int  move();
    virtual void update();
    virtual void toInitialState();
};

#endif