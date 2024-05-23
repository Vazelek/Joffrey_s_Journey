#ifndef BUTTON_H
#define BUTTON_H

#include "Platform.h"

class Button : public Platform{
    Q_OBJECT

private:
    bool pushed;
    int linked_platform;
public:
    Button(MyScene* scene, Player* player, int x, int y, int linked_platform = -1);
    ~Button();
    virtual void isOnIt();
    virtual void toInitialState();
};

#endif