#include "include/MovingPlatform.h"

MovingPlatform::MovingPlatform(MyScene* scene, Player* player, int x, int y, int width, int height, QString ressource_url, int final_coord, bool movement_vertical, int speed, bool start_on_create, int repeat, int initial_coord): Platform(scene, player, x, y, width, height, ressource_url), speed(speed), final_coord(final_coord), movement_vertical(movement_vertical), repeat(repeat), movement_stop(!start_on_create){
    scene->pushMovingPlatform(this);
    if(initial_coord == -666){
        if(movement_vertical){
            this->initial_coord = y;
        }
        else{
            this->initial_coord = x;
        }
    }
    else{
        this->initial_coord = initial_coord;
    }

    this->speed = abs(speed);

     // Initial coord must be lower than final coord
     if(this->initial_coord > final_coord){
        int temp = final_coord;
        this->final_coord = this->initial_coord;
        this->initial_coord = temp;
        this->speed = -abs(speed);
    }

    init_movement_stop = movement_stop;
    init_repeat = this->repeat;
    init_x = this->x;
    init_y = this->y;
    init_speed = this->speed;

}

MovingPlatform::~MovingPlatform(){
    qDebug() << this;
    scene->getMovingPlatforms()->removeOne(this);
}

void MovingPlatform::move(){
    if(repeat == 0 || movement_stop){
        return; // End of the movement of the platform if its animation is completed
    }
    bool positive_speed = speed > 0;

    if(movement_vertical){
        if(y + speed >= final_coord && speed > 0){
            moveTo(x, final_coord);
            speed = -abs(speed);
            if(repeat > 0){
                repeat--;
            }
        }
        else if(y + speed <= initial_coord && speed < 0){
            moveTo(x, initial_coord);
            speed = abs(speed);
            if(repeat > 0){
                repeat--;
            }
        }
        else{
            moveTo(x, y + speed);
        }
    }
    else{
        if(x >= final_coord && speed > 0){
            moveTo(final_coord, y);
            speed = -abs(speed);
            if(repeat > 0){
                repeat--;
            }
        }
        else if(x <= initial_coord && speed < 0){
            moveTo(initial_coord, y);
            speed = abs(speed);
            if(repeat > 0){
                repeat--;
            }
        }
        else{
            moveTo(x + speed, y);
        }
    }

    // Check if platform must push a box or the player
    platformCollidesWithGravitySensitiveItem(positive_speed, movement_vertical);

    // The player is killed if he get crushed by the platform
    for(auto platform : *scene->getPlatforms()){
        if(platform->getWidth() == 0 || platform->getHeight() == 0 || platform == this){
            continue;
        }
        if(platform->getX() < player->x() + player->getWidth() && platform->getX() + platform->getWidth() * platform->getItemWidth() > player->x()){
            if(platform->getY() < player->y() + +player->getHeight() && platform->getY() + platform->getHeight() * platform->getItemHeight() > player->y()){
                player->death(platform);
            }
        }
    }

}

void MovingPlatform::isOnIt(){
    
}

void MovingPlatform::startMovement(){
    movement_stop = false;
}

void MovingPlatform::toInitialState(){
    movement_stop = init_movement_stop;
    repeat = init_repeat;
    speed = init_speed;
    moveTo(init_x, init_y);
}