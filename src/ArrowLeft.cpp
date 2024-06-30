#include "ArrowLeft.h"

ArrowLeft::ArrowLeft(MyScene* scene, Player* player, int x, int y, int final_x, float speed) : Arrow(scene, player, x, y, "arrow_left"), final_x(final_x), speed(speed) {
    setZValue(-1);
}

ArrowLeft::~ArrowLeft(){
}

unsigned short int  ArrowLeft::move() {
    setX(x() - speed);
    if(x() <= final_x){
        delete this;
        return 0;
    }
    return 1;
}

void ArrowLeft::update(){
    Arrow::update();
}
