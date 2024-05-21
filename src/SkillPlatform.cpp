#include "include/SkillPlatform.h"

SkillPlatform::SkillPlatform(MyScene* scene, Player* player, int x, int y, QString type) : Platform(scene, player, x, y, 1, 1, "skill_platform_" + type, 48, 16), type(type){
    scene->pushSkillPlatform(this);
}

SkillPlatform::~SkillPlatform(){
    qDebug() << this;
    scene->getSkillPlatforms()->removeOne(this);
}

void SkillPlatform::isOnIt(){
    if(type == "jump"){
        player->setSkillsAvailable(0);
    }
    else if(type == "dash"){
        player->setSkillsAvailable(1);
    }
    else if(type == "shield"){
        player->setSkillsAvailable(2);
    }
    else if(type == "size_decrease"){
        if(player->getHeight() != 24){
            player->reducePlayerSize();
        }
    }
    else if(type == "size_increase"){
        if(player->getHeight() != 48){
        player->increasePlayerSize();
        }
    }
    scene->getInfos()->updateSkills();
}

void SkillPlatform::toInitialState(){
    
}