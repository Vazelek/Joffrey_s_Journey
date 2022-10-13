#ifndef LAVA_H
#define LAVA_H

#include "Platform.h"

class MyScene;

class Lava : public Platform{
    Q_OBJECT

private:
    int initial_y; // Initial y doit être plus petite que final y
    int final_y;
    int speed;
    int wait_time;
    int initial_wait_time;

public:
    Lava(MyScene* scene, Player* player, int x, int y, int width, int height, int final_y, int speed, int wait_time);
    ~Lava();
    void move();
    virtual void isOnIt();
    virtual void toInitialState();
};


#endif