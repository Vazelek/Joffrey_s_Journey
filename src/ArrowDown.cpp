#include "ArrowDown.h"

ArrowDown::ArrowDown(MyScene* scene, Player* player, int x, int y, int final_y, float speed) : Arrow(scene, player, x, y, "arrow_down"), final_y(final_y), speed(speed) {
    setZValue(-1);
}

ArrowDown::~ArrowDown(){
}

unsigned short int  ArrowDown::move() {
    setY(y() + speed);
    if(y() >= final_y){
        delete this;
        return 0;
    }
    return 1;
}

void ArrowDown::update(){
    Arrow::update();
}
