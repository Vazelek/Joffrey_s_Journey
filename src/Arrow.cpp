#include "include/Arrow.h"

Arrow::Arrow(MyScene* scene, Player* player, int x, int y, QString orientation, int final_coord, float speed) : EventItem(scene, player, x, y, "arrow_" + orientation), final_coord(final_coord), orientation(orientation), speed(speed){
    qDebug() << "created " << orientation;
    setZValue(-1);
}

Arrow::~Arrow(){
    
}

void Arrow::update(){
    if(orientation == "left"){
        qDebug() << "left";
        setX(x() - speed);
        if(x() <= final_coord){
            delete this;
            return;
        }
        qDebug() << "END";
    }
    else if(orientation == "right"){
        qDebug() << "right";
        setX(x() + speed);
        if(x() >= final_coord){
            delete this;
            return;
        }
        qDebug() << "END";
    }
    else if(orientation == "up"){
        qDebug() << "up";
        setY(y() - speed);
        if(y() <= final_coord){
            delete this;
            return;
        }
        qDebug() << "END";
    }
    else if(orientation == "down"){
        qDebug() << "down";
        setY(y() + speed);
        if(y() >= final_coord){
            delete this;
            return;
        }
        qDebug() << "END";
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
    qDebug() << "ok";
}

void Arrow::toInitialState(){
    
}