#ifndef ARROW_H
#define ARROW_H

#include "EventItem.h"

class Arrow : public EventItem{

private:
    int final_coord; // Mettre une coordonnée finale évite que chaque flèche vérifie ses collisions avec toutes les plateforms à chaque fois (faux)
    QString orientation;
    float speed;
public:
    Arrow(MyScene* scene, Player* player,int x, int y, QString orientation, int final_coord, float speed = 3);
    ~Arrow();
    virtual void update();
    virtual void toInitialState();
};

#endif