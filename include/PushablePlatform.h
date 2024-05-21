#ifndef PUSHABLE_PLATFORM_H
#define PUSHABLE_PLATFORM_H

#include "include/Platform.h"


class PushablePlatform : public Platform{
    Q_OBJECT

private:
    float vert_speed;
    int init_x;
    int init_y;

public:
    PushablePlatform(MyScene* scene, Player* player, int x, int y, int width, int height, QString ressource_url);
    ~PushablePlatform();
    Platform* isCollidingDown(int speed = 0);
    void update();
    virtual void toInitialState();
};

#endif