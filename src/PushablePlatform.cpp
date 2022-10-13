#include "PushablePlatform.h"
#include "math.h"

PushablePlatform::PushablePlatform(MyScene* scene, Player* player, int x, int y, int width, int height, QString ressource_url) : Platform(scene, player, x, y, width, height, ressource_url), vert_speed(0){
    scene->pushPushablePlatform(this);
    init_x = x;
    init_y = y;
}

PushablePlatform::~PushablePlatform(){
    qDebug() << this;
    scene->getPushablePlatforms()->removeOne(this);
}

void PushablePlatform::update(){
    if(isCollidingDown(-1) == nullptr){
        vert_speed -= 0.5;
        if(vert_speed <= -15){
            vert_speed = -15; // Vitesse verticale limite
        }
    }

    if(isCollidingDown(floor(vert_speed)) == nullptr){
        moveTo(x, y - floor(vert_speed));
    }
    else{
        vert_speed = 0;
    }
}

Platform* PushablePlatform::isCollidingDown(int speed){
    if(width == 0 || height == 0){
        return nullptr;
    }

    int min_distance = 0; // Pour savoir quel est le bloc le plus proche
    int new_coord = 0;
    Platform* closest = nullptr;

    for(auto platform : *scene->getPlatforms()){
        if(platform->getWidth() == 0 || platform->getHeight() == 0 || platform == this || platform->metaObject()->className() == QString::fromStdString("Lava")){
            continue;
        }

        if(collidesWithPlatform(platform, speed, 0)){
            if(platform->getY() - y + height * item_height < min_distance || closest == nullptr){
                min_distance = platform->getY() - y + height * item_height;
                closest = platform;
                new_coord = platform->getY() - height * item_height;
            }
        }

        if(closest != nullptr){
            moveTo(x, new_coord);
            closest->isOnIt();
            return closest;
        }
    }

    if(player->collidesWithPlatform(this, -speed, 0)){ // Tue le joueur si une collision avec lui
        player->death(this);
    }

    return nullptr;
}

void PushablePlatform::toInitialState(){
    vert_speed = 0;
    moveTo(init_x, init_y);
}