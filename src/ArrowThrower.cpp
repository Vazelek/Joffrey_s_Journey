#include "ArrowThrower.h"

ArrowThrower::ArrowThrower(MyScene* scene, Player* player, int x, int y, QString orientation, int final_coord, float delay) : EventItem(scene, player, x, y, "arrow_thrower_" + orientation + ".png"), delay(delay * FPS), initial_delay(delay * FPS), final_coord(final_coord), orientation(orientation){

}

ArrowThrower::~ArrowThrower(){
    
}

void ArrowThrower::update(){
    delay --;
    if(delay <= 0){
        delay = initial_delay;
        throwArrow();
    }
}

void ArrowThrower::throwArrow(){
    if(orientation == "left"){
        new ArrowLeft(scene, player, x(), y() + 5, final_coord);
        return;
    }
    else if(orientation == "right"){
        new ArrowRight(scene, player, x(), y() + 5, final_coord);
        return;
    }
    else if(orientation == "up"){
        new ArrowUp(scene, player, x() + 5, y(), final_coord);
        return;
    }
    else if(orientation == "down"){
        new ArrowDown(scene, player, x() + 5, y(), final_coord);
        return;
    }
    else{
        qDebug() << "Invalid orientation";
    }
}