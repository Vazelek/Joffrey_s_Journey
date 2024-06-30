#include "BreakablePlatform.h"

BreakablePlatform::BreakablePlatform(MyScene* scene, Player* player, int x, int y, int width, int height, int lifetime, int respawn_time) : Platform(scene, player, x, y, width, height, "breakable_platform.png"), lifetime(lifetime * FPS), initial_lifetime(lifetime * FPS), status(0), respawn_time(respawn_time * FPS), initial_respawn_time(respawn_time * FPS), initial_width(width), initial_height(height){
    scene->pushBreakablePlatform(this);
}

BreakablePlatform::~BreakablePlatform(){
    // qDebug() << this;
    scene->getBreakablePlatforms()->removeOne(this);
}

int BreakablePlatform::getLifeTime(){
    return lifetime;
}

void BreakablePlatform::isOnIt(){
    lifetime --;
    if(lifetime < (3 - status) * initial_lifetime / 4 && status < 3){
        status++;
        QString res = "breakable_platform_broken" + QString::number(status) + ".png";
        updateImage(res);
    }
    if(lifetime <= 0){
        deleteItems();
    }
}

void BreakablePlatform::update(){
    if(lifetime <= 0 && respawn_time >= 0){
        respawn_time--;
        if(respawn_time <= 0){
            lifetime = initial_lifetime;
            status = 0;
            itemsGeneration("breakable_platform.png", initial_width, initial_height);
            respawn_time = initial_respawn_time;
            if(
                collidesWithPlatform(
                    this->getX(), 
                    this->getY(), 
                    player->x(),
                    player->y(),
                    this->getWidth() * this->getItemWidth(),
                    this->getHeight() * this->getItemHeight(),
                    player->getWidth(),
                    player->getHeight(),
                    0,
                    0
                )
            ){ // Check if platform was created on the player
                player->setY(y - player->sceneBoundingRect().height());
            }
            platformCollidesWithGravitySensitiveItem(false, true);
        }
    }
}

void BreakablePlatform::toInitialState(){
    
}