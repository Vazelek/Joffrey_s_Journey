#ifndef SEMIPASSABLEPLATFORM_H
#define SEMIPASSABLEPLATFORM_H

#include "include/Platform.h"

class SemiPassablePlatform : public Platform{
    Q_OBJECT

private:

public:
    SemiPassablePlatform(MyScene* scene, Player* player, int x, int y, int width, int height, QString ressource_url);
    ~SemiPassablePlatform();
    virtual void isOnIt();
    virtual void toInitialState();
};

#endif