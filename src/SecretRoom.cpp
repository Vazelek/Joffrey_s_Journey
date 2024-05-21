#include "include/SecretRoom.h"

SecretRoom::SecretRoom(MyScene* scene, Player* player, int x, int y, int width, int height, QString ressource_url) : QObject(), scene(scene), player(player), x(x), y(y), width(width), height(height){

    scene->pushSecretRoom(this);
    
    itemsGeneration(ressource_url);
    is_hidden = false;
}

SecretRoom::~SecretRoom(){
    qDebug() << this;
    scene->getSecretRooms()->removeOne(this);
    deleteItems();
}

void SecretRoom::deleteItems(){
    if(width == 0 || height == 0){
        return;
    }
    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            scene->removeItem(graphics_items[i][j]);
            delete graphics_items[i][j];
        }
        delete [] graphics_items[i];
    }
    delete [] graphics_items;
    width = 0;
    height = 0;
}

void SecretRoom::itemsGeneration(QString ressource_url, int new_width, int new_height){
    if(new_width != 0 && new_height != 0){
        width = new_width;
        height = new_height;
    }
    graphics_items = new QGraphicsPixmapItem**[width];
    for (int i = 0; i < width; ++i){
        graphics_items[i] = new QGraphicsPixmapItem*[height];
    }

    QString path = "resources/";

    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            graphics_items[i][j] = new QGraphicsPixmapItem(path + ressource_url);
            graphics_items[i][j]->setScale(0.1);
            graphics_items[i][j]->setPos(x + 16 * i, y + 16 * j);
            scene->addItem(graphics_items[i][j]);
        }
    }
}

QGraphicsPixmapItem*** SecretRoom::getItems(){
    return graphics_items;
}

int SecretRoom::getX(){
    return x;
}

int SecretRoom::getY(){
    return y;
}

int SecretRoom::getWidth(){
    return width;
}

int SecretRoom::getHeight(){
    return height;
}

void SecretRoom::collidesWithSecretRoom(){
    if(x < player->x() + player->getWidth() && x + width * 16 > player->x()){
        if(y < player->y() + player->getHeight() && y + height * 16 > player->y()){
            if(!is_hidden){
                hide();
            }
            return;
        }
    }
    if(is_hidden){
        show();
    }
}

void SecretRoom::hide(){
    is_hidden = true;
    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            scene->removeItem(graphics_items[i][j]);
        }
    }
}

void SecretRoom::show(){
    is_hidden = false;
    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            scene->addItem(graphics_items[i][j]);
        }
    }
}

void SecretRoom::toInitialState(){
    
}