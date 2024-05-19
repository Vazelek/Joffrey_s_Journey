#include "EventItem.h"

EventItem::EventItem(MyScene* scene, Player* player, int x, int y, QString ressource_url) : QGraphicsPixmapItem(QPixmap("resources/" + ressource_url)), player(player), scene(scene), used(false){
    setPos(x, y);
    setScale(0.1);

    scene->pushEventItem(this);
    scene->addItem(this);
}

EventItem::~EventItem(){
    scene->getEventItems()->removeOne(this);
}

void EventItem::toInitialState(){
    
}