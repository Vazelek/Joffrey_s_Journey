#include "Lava.h"

Lava::Lava(MyScene* scene, Player* player, int x, int y, int width, int height, int final_y, int speed, int wait_time): Platform(scene, player, x, y, width, height, "lava"), speed(speed), final_y(final_y), wait_time(wait_time * FPS), initial_wait_time(wait_time * FPS){
    scene->pushLavaArea(this);

    initial_y = y;

    this->speed = abs(speed);

     // Initial coord must be lower than final coord
     if(initial_y > final_y){
         int temp = final_y;
         this->final_y = initial_y;
         initial_y = temp;
         this->speed = -abs(speed);
     }

}

Lava::~Lava(){
    // qDebug() << this;
    scene->getLavaAreas()->removeOne(this);
}

void Lava::move(){
    if(speed == 0){
        return;
    }
    if(wait_time != 0){
        wait_time --;
        return;
    }
    bool positive_speed = speed > 0;

    if(y + speed >= final_y && speed > 0){
        moveTo(x, final_y);
        speed = -abs(speed);
        wait_time = initial_wait_time;
    }
    else if(y + speed <= initial_y && speed < 0){
        moveTo(x, initial_y);
        speed = abs(speed);
        wait_time = initial_wait_time;
    }
    else{
        moveTo(x, y + speed);
    }
}

void Lava::isOnIt(){
    
}

void Lava::toInitialState(){
    
}