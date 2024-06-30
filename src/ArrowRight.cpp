#include "ArrowRight.h"

ArrowRight::ArrowRight(MyScene* scene, Player* player, int x, int y, int final_x, float speed) : Arrow(scene, player, x, y, "arrow_right"), final_x(final_x), speed(speed) {
    setZValue(-1);
}

ArrowRight::~ArrowRight(){
}

unsigned short int  ArrowRight::move() {
    setX(x() + speed);
    if(x() >= final_x){
        delete this;
        return 0;
    }
    return 1;
}

void ArrowRight::update(){
    Arrow::update();
}

void ArrowRight::toInitialState(){
    
}