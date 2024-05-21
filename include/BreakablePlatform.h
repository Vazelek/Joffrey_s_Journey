#ifndef BREAKABLEPLATFORM_H
#define BREAKABLEPLATFORM_H

#include "include/Platform.h"

class BreakablePlatform : public Platform{
    Q_OBJECT

private:
    int lifetime;
    int initial_lifetime;
    int respawn_time;
    int initial_respawn_time;
    int status;
    int initial_width;
    int initial_height;

public:
    BreakablePlatform(MyScene* scene, Player* player, int x, int y, int width, int height, int lifetime, int respawn_time = -1);
    ~BreakablePlatform();
    int getLifeTime();
    virtual void isOnIt();
    void update();
    virtual void toInitialState();
};

#endif