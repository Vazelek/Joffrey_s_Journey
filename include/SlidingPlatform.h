#ifndef SLIDINGPLATFORM_H
#define SLIDINGPLATFORM_H

#include "include/Platform.h"

class SlidingPlatform : public Platform{
    Q_OBJECT

private:

public:
    SlidingPlatform(MyScene* scene, Player* player, int x, int y, int width, int height, QString ressource_url);
    ~SlidingPlatform();
    virtual void isOnIt();
    virtual void toInitialState();
};

#endif