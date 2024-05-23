#include "SlidingPlatform.h"

SlidingPlatform::SlidingPlatform(MyScene* scene, Player* player, int x, int y, int width, int height, QString ressource_url) : Platform(scene, player, x, y, width, height, ressource_url){
    scene->pushSlidingPlatform(this);
}

SlidingPlatform::~SlidingPlatform(){
    qDebug() << this;
    scene->getSlidingPlatforms()->removeOne(this);
}

void SlidingPlatform::isOnIt(){
    player->isOnIce();
}

void SlidingPlatform::toInitialState(){
    
}