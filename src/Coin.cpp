#include "Coin.h"

Coin::Coin(MyScene* scene, Player* player, int x, int y) : EventItem(scene, player, x, y, "coin.png"){
    scene->setTotalCoins(scene->getTotalCoins() + 1);
}

Coin::~Coin(){
    qDebug() << this;
}

void Coin::update(){
    if(!used){
        if(collidesWithItem(player)){
            used = true;
            scene->removeItem(this);
            scene->setCoinsCount(scene->getCoinsCount() + 1);
        }
    }
}

void Coin::toInitialState(){
    if(used){
        used = false;
        scene->addItem(this);
    }
}