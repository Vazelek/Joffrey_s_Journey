#include "include/Flag.h"

Flag::Flag(MyScene* scene, Player* player, int x, int y, bool is_end_flag) : EventItem(scene, player, x, y, "flag_1.png"), is_end_flag(is_end_flag){
    if(is_end_flag){
        QString res = "resources/end_flag.png";
        setPixmap(res);
    }
    scene->pushFlag(this);
}

Flag::~Flag(){
    qDebug() << this;
}

void Flag::update(){
    if(!used){
        if(collidesWithItem(player)){
            if(!is_end_flag){
                player->setSpawnPoint(x(), y());
                used = true;
            }
            else{
                scene->levelEnd();
            }
            animation_state = 1;
            animation_time = 5;
        }
    }
    if(animation_state != 0 && !is_end_flag){
        if(animation_time == 0){
            animation_state ++;
            QString res = "resources/flag_" + QString::number(animation_state % 4 + 1) + ".png";
            setPixmap(res);
            animation_time = 5;
            if(animation_state >= 32){
                animation_state = 0;
            }
            animation_time = 5;
        }
        else{
            animation_time--;
        }
    }
}

void Flag::toInitialState(){
    
}

void Flag::toFullyInitialState(){
    if(used){
        used = false;
    }
}