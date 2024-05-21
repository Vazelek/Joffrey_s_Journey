#ifndef FLAG_H
#define FLAG_H

#include "include/EventItem.h"

class MyScene;
class Player;

class Flag : public EventItem{

private:
    bool is_end_flag;
    int animation_state;
    int animation_time;

public:
    Flag(MyScene* scene, Player* player, int x, int y, bool is_end_flag = false);
    ~Flag();
    virtual void update();
    virtual void toInitialState();
    void toFullyInitialState();
};

#endif