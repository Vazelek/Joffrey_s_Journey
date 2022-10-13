#include "Platform.h"

Platform::Platform(MyScene* scene, Player* player, int x, int y, int width, int height, QString ressource_url, int item_width, int item_height) : QObject(), scene(scene), player(player), x(x), y(y), width(width), height(height), item_width(item_width), item_height(item_height){

    scene->pushPlatform(this);
    
    itemsGeneration(ressource_url);

}

Platform::~Platform(){
    qDebug() << this;
    scene->getPlatforms()->removeOne(this);
    deleteItems();
}

void Platform::deleteItems(){
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

void Platform::itemsGeneration(QString ressource_url, int new_width, int new_height){
    if(new_width != 0 && new_height != 0){
        width = new_width;
        height = new_height;
    }
    graphics_items = new QGraphicsPixmapItem**[width];
    for (int i = 0; i < width; ++i){
        graphics_items[i] = new QGraphicsPixmapItem*[height];
    }

    // Chemin vers le fichier contenant les ressources
    QString path = "../ressources/";


    if(ressource_url == "button"){ // Ressources url spéciale (prédéfinie)
        QString res = "button.png";
        graphics_items[0][0] = new QGraphicsPixmapItem(path + res);
        graphics_items[0][0]->setScale(0.1);
        graphics_items[0][0]->setPos(x, y);
        scene->addItem(graphics_items[0][0]);
    }
    else if(ressource_url == "fence"){
        QString res = "fence.png";
        graphics_items[0][0] = new QGraphicsPixmapItem(path + res);
        graphics_items[0][0]->setScale(0.1);
        graphics_items[0][0]->setPos(x, y);
        scene->addItem(graphics_items[0][0]);
        item_width = 12;
        item_height = 48;
    }
    else if(ressource_url == "crate"){
        QString res;
        if(width == 1){
            res = "crate_16.png";
        }
        else if(width == 2){
            item_width = 32;
            item_height = 32;
            width = 1;
            height = 1;
            res = "crate_32.png";
        }
        else if(width == 3){
            item_width = 48;
            item_height = 48;
            width = 1;
            height = 1;
            res = "crate_48.png";
        }
        graphics_items[0][0] = new QGraphicsPixmapItem(path + res);
        graphics_items[0][0]->setScale(0.1);
        graphics_items[0][0]->setPos(x, y);
        scene->addItem(graphics_items[0][0]);
    }
    else if(ressource_url == "lava"){
        for(int i = 0; i < width; i++){
            for(int j = 0; j < height; j++){
                if(j == 0){
                    graphics_items[i][j] = new QGraphicsPixmapItem(path + ressource_url + "_top.png");
                    graphics_items[i][j]->setScale(0.1);
                    graphics_items[i][j]->setPos(x + item_width * i, y + item_height * j);
                    scene->addItem(graphics_items[i][j]);
                }
                else{
                    graphics_items[i][j] = new QGraphicsPixmapItem(path + ressource_url + ".png");
                    graphics_items[i][j]->setScale(0.1);
                    graphics_items[i][j]->setPos(x + item_width * i, y + item_height * j);
                    scene->addItem(graphics_items[i][j]);
                }
            }
        }
    }
    else if(ressource_url == "grass"){
        for(int i = 0; i < width; i++){
            for(int j = 0; j < height; j++){
                if(j == 0){
                    graphics_items[i][j] = new QGraphicsPixmapItem(path + "grass.png");
                    graphics_items[i][j]->setScale(0.1);
                    graphics_items[i][j]->setPos(x + item_width * i, y + item_height * j);
                    scene->addItem(graphics_items[i][j]);
                }
                else{
                    graphics_items[i][j] = new QGraphicsPixmapItem(path + "dirt.png");
                    graphics_items[i][j]->setScale(0.1);
                    graphics_items[i][j]->setPos(x + item_width * i, y + item_height * j);
                    scene->addItem(graphics_items[i][j]);
                }
            }
        }
    }
    else if(ressource_url == "door"){
        for(int i = 0; i < width; i++){
            for(int j = 0; j < height; j++){
                graphics_items[i][j] = new QGraphicsPixmapItem(path + ressource_url + ".png");
                graphics_items[i][j]->setScale(0.1);
                graphics_items[i][j]->setPos(x + item_width * i, y + item_height * j);
                graphics_items[i][j]->setZValue(-1);
                scene->addItem(graphics_items[i][j]);
            }
        }
    }
    else{
        for(int i = 0; i < width; i++){
            for(int j = 0; j < height; j++){
                graphics_items[i][j] = new QGraphicsPixmapItem(path + ressource_url);
                graphics_items[i][j]->setScale(0.1);
                graphics_items[i][j]->setPos(x + item_width * i, y + item_height * j);
                scene->addItem(graphics_items[i][j]);
            }
        }
    }
}

QGraphicsPixmapItem*** Platform::getItems(){
    return graphics_items;
}

int Platform::getX(){
    return x;
}

int Platform::getY(){
    return y;
}

int Platform::getWidth(){
    return width;
}

int Platform::getHeight(){
    return height;
}

int Platform::getItemWidth(){
    return item_width;
}

int Platform::getItemHeight(){
    return item_height;
}

void Platform::isOnIt(){

}

void Platform::moveTo(int new_x, int new_y){
    x = new_x;
    y = new_y;
    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            graphics_items[i][j]->setPos(x + item_width * i, y + item_height * j);
        }
    }
}

void Platform::platformCollidesWithGravitySensitiveItem(bool positive_speed, bool movement_vertical, QVector<Platform*>* platforms_moved, QVector<Platform*>* platforms_to_move){
    if(width == 0 || height == 0){
        return;
    }
    for(auto platform : *scene->getPushablePlatforms()){
        if(platform->getWidth() == 0 || platform->getHeight() == 0 || platform == this){
            continue;
        }
        if(platforms_to_move){
            if(!platforms_to_move->contains(platform)){
                continue;
            }
        }

        if(collidesWithPlatform(platform)){
            if(!movement_vertical){
                if(positive_speed){
                    platform->moveTo(x + width * item_width, platform->getY());
                    if(platforms_moved != nullptr){
                        platforms_moved->push_back(platform);
                    }
                    platform->platformCollidesWithGravitySensitiveItem(positive_speed, movement_vertical);
                }
                else{
                    platform->moveTo(x - platform->getWidth() * platform->getItemWidth()  , platform->getY());
                    if(platforms_moved != nullptr){
                        platforms_moved->push_back(platform);
                    }
                    platform->platformCollidesWithGravitySensitiveItem(positive_speed, movement_vertical);
                }
            }
            else{
                if(!positive_speed){
                    platform->moveTo(platform->getX(), y - platform->getHeight() * platform->getItemHeight());
                    if(platforms_moved != nullptr){
                        platforms_moved->push_back(platform);
                    }
                    platform->platformCollidesWithGravitySensitiveItem(positive_speed, movement_vertical);
                }
                // Collision en descente impossible selon le game design
            }
        }
    }

    if(player->collidesWithPlatform(this)){
        if(!movement_vertical){
            if(positive_speed){
                player->setX(x + width * item_width);
            }
            else{
                player->setX(x - player->sceneBoundingRect().width());
            }
        }
        else{
            if(positive_speed){
                player->setY(y + height * item_height);
            }
            else{
                player->setY(y- player->sceneBoundingRect().height());
            }
        }
    }
}

bool Platform::collidesWithPlatform(Platform* platform, int v_speed, int h_speed){
    if(platform->getX() < x + width * item_width + h_speed && platform->getX() + platform->getWidth() * platform->getItemWidth() > x + h_speed){
        if(platform->getY() < y + height * item_height - v_speed && platform->getY() + platform->getHeight() * platform->getItemHeight() > y - v_speed){
            return true;
        }
    }
    return false;
}

void Platform::updateImage(QString ressource_url){
    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            QString path = "../ressources/";
            graphics_items[i][j]->setPixmap(path + ressource_url);
        }
    }
}

void Platform::toInitialState(){
    
}