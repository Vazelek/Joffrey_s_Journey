#include "Arrow.h"

Arrow::Arrow(MyScene* scene, Player* player, int x, int y, QString orientation, int final_coord, float speed) : EventItem(scene, player, x, y, "../ressources/arrow_" + orientation), final_coord(final_coord), orientation(orientation), speed(speed){
    setZValue(-1); // On les met toutes en arrière plan pour avoir l'impression qu'elles disparaissent
}

Arrow::~Arrow(){
    
}

void Arrow::update(){
    if(orientation == "left"){
        setX(x() - speed);
        if(x() <= final_coord){
            delete this;
            return;
        }
    }
    else if(orientation == "right"){
        setX(x() + speed);
        if(x() >= final_coord){
            delete this;
            return;
        }
    }
    else if(orientation == "up"){
        setY(y() - speed);
        if(y() <= final_coord){
            delete this;
            return;
        }
    }
    else if(orientation == "down"){
        setY(y() + speed);
        if(y() >= final_coord){
            delete this;
            return;
        }
    }
    else{
        qDebug() << "Invalid orientation";
    }

    if(collidesWithItem(player)){
        if(player->hasShield()){
            player->removeShield();
            delete this;
        }
        else{
            player->death();
        }
    }
}

void Arrow::toInitialState(){
    
}