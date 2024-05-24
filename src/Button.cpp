#include "Button.h"

Button::Button(MyScene* scene, Player* player, int x, int y, int linked_platform) : Platform(scene, player, x, y, 1, 1, "button", 32), pushed(false), linked_platform(linked_platform){
    scene->pushButton(this);
}

Button::~Button(){
    // qDebug() << this;
    scene->getButtons()->removeOne(this);
}

void Button::isOnIt(){
    if(!pushed){
    //    QUrl baseUrl = QUrl::fromLocalFile(QDir::currentPath() + "/");

    //    QMediaPlaylist *playlist = new QMediaPlaylist();
    //    playlist->addMedia(baseUrl.resolved(QUrl("sound_effects/dk.wav")));
    //    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    //    QMediaPlayer* musicPlayer = new QMediaPlayer;
    //    musicPlayer->setPlaylist(playlist);
    //    musicPlayer->setVolume(50);
    //    musicPlayer->play();

        QString res = "resources/pushed_button.png";
        graphics_items[0][0]->setPixmap(res);
        graphics_items[0][0]->setY(y + 12);
        y = y + 12;
        if(linked_platform >= 0 && linked_platform < (*scene->getMovingPlatforms()).size()){
            if((*scene->getMovingPlatforms())[linked_platform] != nullptr){
                (*scene->getMovingPlatforms())[linked_platform]->startMovement();
            }
        }
        pushed = true;
    }
}

void Button::toInitialState(){
    if(pushed){
        pushed = false;
        QString res = "resources/button.png";
        graphics_items[0][0]->setPixmap(res);
        graphics_items[0][0]->setY(y - 12);
        y = y - 12;
    }
}