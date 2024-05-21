#include "include/SemiPassablePlatform.h"

SemiPassablePlatform::SemiPassablePlatform(MyScene* scene, Player* player, int x, int y, int width, int height, QString ressource_url) : Platform(scene, player, x, y, width, height, ressource_url, 16, 16){
    scene->pushSemiPassablePlatform(this);
}

SemiPassablePlatform::~SemiPassablePlatform(){
    qDebug() << this;
    scene->getSemiPassablePlatforms()->removeOne(this);
}

void SemiPassablePlatform::isOnIt(){
    
}

void SemiPassablePlatform::toInitialState(){
    
}