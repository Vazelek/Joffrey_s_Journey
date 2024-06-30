#include "Arrow.h"

Arrow::Arrow(MyScene* scene, Player* player, int x, int y, QString resource_url) : EventItem(scene, player, x, y, resource_url) {
    setZValue(-1);
}

Arrow::~Arrow(){
    
}

unsigned short int Arrow::move() {

}

void Arrow::update(){
    if (!this->move()) // Means delete 
        return;

    if(collidesWithItem(player)){
        if(player->hasShield()){
            player->removeShield();
            delete this;
        }
        else{
            player->death();
            delete this;
        }
    }
}

void Arrow::toInitialState(){
    
}