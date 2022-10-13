#ifndef MOVING_PLATFORM_H
#define MOVING_PLATFORM_H

#include "Platform.h"

class MyScene;

class MovingPlatform : public Platform{
    Q_OBJECT

private:
    int initial_coord; // Initial coord doit être plus petite que final coord
    int final_coord;
    bool movement_vertical; // Orientation du mouvement
    int speed;
    int repeat; // Nombre de fois que le mouvement doit être répété
    int init_repeat;
    bool movement_stop;
    bool init_movement_stop;
    int init_x;
    int init_y;
    int init_speed;
public:
    MovingPlatform(MyScene* scene, Player* player, int x, int y, int width, int height, QString ressource_url, int final_coord, bool movement_vertical, int speed, bool start_on_create = true, int repeat = -1, int initial_coord = -666);
    ~MovingPlatform();
    void move();
    virtual void isOnIt();
    void startMovement();
    virtual void toInitialState();
};


#endif