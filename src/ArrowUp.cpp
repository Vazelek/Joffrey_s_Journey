#include "ArrowUp.h"

ArrowUp::ArrowUp(MyScene* scene, Player* player, int x, int y, int final_y, float speed) : Arrow(scene, player, x, y, "arrow_up"), final_y(final_y), speed(speed) {
    setZValue(-1);
}

ArrowUp::~ArrowUp(){  
}

unsigned short int ArrowUp::move() {
    setY(y() - speed);
    if(y() <= final_y){
        delete this;
        return 0;
    }
    return 1;
}

void ArrowUp::update(){
    Arrow::update();
}