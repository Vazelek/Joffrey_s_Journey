#include "Player.h"
#include "math.h"
#include <tuple>


Player::Player(QString image_url, MyScene* scene) : QGraphicsPixmapItem(QPixmap(image_url)), scene(scene){
    vert_speed = 0;
    hori_speed = 0;
    base_vert_speed = 9;
    base_hori_speed = 4;
    width = 26;
    height = 48;
    spawn_x = 0;
    spawn_y = 0;
    next_jump_speed = 0;
    for(int i = 0; i < 3; i++){
        skills_available[i] = false;
    }
    has_shield = false;
    shield = nullptr;
    ice_speed = 0;
    is_on_ice = false;
    animation_status = 2;
    animation_time = 6;
    animation_direction = 1;
    facing_left = false;
}

Player::~Player(){
    // qDebug() << this;
}

void Player::jump(){
    if(next_jump_speed == 0){
        vert_speed = base_vert_speed;
    }
    else{
        vert_speed = next_jump_speed;
        next_jump_speed = 0;
    }
}

void Player::move(){

    // Check whether the player's feet are on the ground
    if(isColliding("down", -1) == nullptr){
        vert_speed -= 0.5;
        if(vert_speed <= -15){
            vert_speed = -15; // Max vertical speed
        }
    }

    hori_speed = 0;
    if(scene->getPressedKeys(0)){
        hori_speed -= base_hori_speed;
    }
    if(scene->getPressedKeys(1)){
        hori_speed += base_hori_speed;
    }

    if(facing_left && hori_speed > 0){
        setPixmap(pixmap().transformed(QTransform().scale(-1, 1)));
        facing_left = false;
    }
    else if(!facing_left && hori_speed < 0){
        setPixmap(pixmap().transformed(QTransform().scale(-1, 1)));
        facing_left = true;
    }

    if(hori_speed != 0){
        if(animation_time == 0){
            if(animation_status == 1){
                animation_direction = 1;
            }
            if(animation_status == 3){
                animation_direction = -1;
            }
            animation_status += animation_direction;
            if(facing_left){
                setPixmap(QPixmap("resources/player_" + QString::number(animation_status) + ".png").transformed(QTransform().scale(-1, 1)));
            }
            else{
                setPixmap(QPixmap("resources/player_" + QString::number(animation_status) + ".png"));
            }
            animation_time = 6;
        }
        else{
            animation_time--;
        }
    }

    std::tie(hori_speed, ice_speed) = getIceSpeed(hori_speed, ice_speed, is_on_ice);

    // Check if the player is trying to go Out Of Bounds
    // - down
    if(vert_speed < 0){
        if(isColliding("down", floor(vert_speed)) != nullptr){
            vert_speed = 0;
        }
    }
    // - up
    if(vert_speed > 0){
        Platform* platform = isColliding("up", floor(vert_speed));
        if(platform != nullptr){
            if(platform->metaObject()->className() == QString::fromStdString("SemiPassablePlatform")){
                setY(platform->getY() - height);
            }
            vert_speed = 0;
        }
    }

    setY(y() - floor(vert_speed));

    Platform* platform = nullptr;

    // - on the left
    if(hori_speed < 0){
        platform = isColliding("left", hori_speed);
        if(platform != nullptr){
            hori_speed = 0;

            std::string class_name(platform->metaObject()->className());
            // Check if he is trying to push a box
            if(class_name == "PushablePlatform"){
                if(scene->getPressedKeys(2)){ // If A key is pressed, try to push the box

                    platform->moveTo(platform->getX() -1, platform->getY());
                    QVector<Platform*>* platforms_moved = new QVector<Platform*>;
                    platforms_moved->push_back(platform);
                    platform->platformCollidesWithGravitySensitiveItem(false, false, platforms_moved);

                    for(auto plt : *scene->getPlatforms()){
                        if(plt->getWidth() == 0 || plt->getHeight() == 0){
                            continue;
                        }

                        std::string class_name2(plt->metaObject()->className());
                        if(class_name2 == "PushablePlatform"){
                            continue;
                        }

                        // Stop the pushable platforms if they hit a wall
                        plt->platformCollidesWithGravitySensitiveItem(true, false, nullptr, platforms_moved);
                    }
                    delete platforms_moved;

                    // Stick the player to the platform he is trying to push
                    isColliding("left", -1);
                }
            }
        }
    } // - on the right
    else if(hori_speed > 0){
        platform = isColliding("right", hori_speed);
        if(platform != nullptr){
            hori_speed = 0;

            std::string class_name(platform->metaObject()->className());
            // Check if he is trying to push a box
            if(class_name == "PushablePlatform"){
                if(scene->getPressedKeys(2)){ // If A key is pressed, try to push the box

                    platform->moveTo(platform->getX() +1, platform->getY());
                    QVector<Platform*>* platforms_moved = new QVector<Platform*>;
                    platforms_moved->push_back(platform);
                    platform->platformCollidesWithGravitySensitiveItem(true, false, platforms_moved);

                    for(auto plt : *scene->getPlatforms()){
                        if(plt->getWidth() == 0 || plt->getHeight() == 0){
                            continue;
                        }

                        std::string class_name2(plt->metaObject()->className());
                        if(class_name2 == "PushablePlatform"){
                            continue;
                        }

                        plt->platformCollidesWithGravitySensitiveItem(false, false, nullptr, platforms_moved);
                    }
                    isColliding("right", 1);
                    delete platforms_moved;
                }
            }
        }
    }
    setX(x() + hori_speed);

    updateShield();
    is_on_ice = false;
}

void Player::setVerticalSpeed(int speed) {
    vert_speed = speed;
}

float Player::getHorizontalSpeed() {
    return hori_speed;
}

float Player::getVerticalSpeed() {
    return vert_speed;
}

Platform* Player::isColliding(QString direction, float speed){

    // qDebug() << "Collides " << platform << " -----> (x, y, width, height) : (" << platform->getX() << ", " << platform->getY() << ", " << platform->getWidth() * platform->getItemWidth() << ", " << platform->getHeight() * platform->getItemHeight() << ") //// Player : " << x() << ", " << y() << ", " << width << ", " << height;

    int min_distance = 0; // To know what is the closest bloc
    int new_coord = 0;
    Platform* closest = nullptr;
    if(direction == "left"){

        for(auto platform : *scene->getPlatforms()){

            if(platform->getWidth() == 0 || platform->getHeight() == 0 || platform->metaObject()->className() == QString::fromStdString("Lava")){
                continue;
            }

            if(
                collidesWithPlatform(
                    platform->getX(), 
                    platform->getY(), 
                    x(),
                    y(),
                    platform->getWidth() * platform->getItemWidth(),
                    platform->getHeight() * platform->getItemHeight(),
                    width,
                    height,
                    0, 
                    speed
                )
            ) {
                if(x() - (platform->getX() + platform->getWidth() * platform->getItemWidth()) < min_distance || closest == nullptr){
                    min_distance = x() - (platform->getX() + platform->getWidth() * platform->getItemWidth());
                    closest = platform;
                    new_coord = platform->getX() + platform->getWidth() * platform->getItemWidth();
                }
            }
        }

        if(closest != nullptr){
            setX(new_coord);
            return closest;
        }

    }
    else if(direction == "up"){

        for(auto platform : *scene->getPlatforms()){

            if(platform->getWidth() == 0 || platform->getHeight() == 0 || platform->metaObject()->className() == QString::fromStdString("Lava")){
                continue;
            }

            if(
                collidesWithPlatform(
                    platform->getX(), 
                    platform->getY(), 
                    x(),
                    y(),
                    platform->getWidth() * platform->getItemWidth(),
                    platform->getHeight() * platform->getItemHeight(),
                    width,
                    height,
                    speed,
                    0
                )
            ) {
                if(y() - (platform->getY() + platform->getHeight() * platform->getItemHeight()) < min_distance || closest == nullptr){
                    min_distance = y() - platform->getY() - platform->getHeight() * platform->getItemHeight();
                    closest = platform;
                    new_coord = platform->getY() + platform->getHeight() * platform->getItemHeight();
                }
            }
        }

        if(closest != nullptr){
            setY(new_coord);
            return closest;
        }

    }
    else if(direction == "right"){

        for(auto platform : *scene->getPlatforms()){

            if(platform->getWidth() == 0 || platform->getHeight() == 0 || platform->metaObject()->className() == QString::fromStdString("Lava")){
                continue;
            }

            if(
                collidesWithPlatform(
                    platform->getX(), 
                    platform->getY(), 
                    x(),
                    y(),
                    platform->getWidth() * platform->getItemWidth(),
                    platform->getHeight() * platform->getItemHeight(),
                    width,
                    height,
                    0, 
                    speed
                )
            ) {
                if(platform->getX() - x() + width < min_distance || closest == nullptr){
                    min_distance = platform->getX() - x() + width;
                    closest = platform;
                    new_coord = platform->getX() - width;
                }
            }
        }

        if(closest != nullptr){
            setX(new_coord);
            return closest;
        }

    }
    else if(direction == "down"){

        for(auto platform : *scene->getPlatforms()){

            if(platform->getWidth() == 0 || platform->getHeight() == 0 || platform->metaObject()->className() == QString::fromStdString("Lava")){
                continue;
            }

            if(
                collidesWithPlatform(
                    platform->getX(), 
                    platform->getY(), 
                    x(),
                    y(),
                    platform->getWidth() * platform->getItemWidth(),
                    platform->getHeight() * platform->getItemHeight(),
                    width,
                    height,
                    speed,
                    0
                )
            ) {
                if(platform->getY() - y() + height < min_distance || closest == nullptr){
                    min_distance = platform->getY() - y() + height;
                    closest = platform;
                    new_coord = platform->getY() - height;
                }
            }
        }

        if(closest != nullptr){
            setY(new_coord);
            closest->isOnIt();
            return closest;
        }

    }
    else{
        qDebug() << "Invalid direction";
    }
    return nullptr;
}

// bool Player::collidesWithPlatform(Platform* platform, int v_speed, int h_speed){
//     if(platform->getX() < x() + width + h_speed && platform->getX() + platform->getWidth() * platform->getItemWidth() > x() + h_speed){
//         if(platform->getY() < y() + height - v_speed && platform->getY() + platform->getHeight() * platform->getItemHeight() > y() - v_speed){
//             return true;
//         }
//     }
//     return false;
// }

void Player::death(Platform* platform){ // A suppr
    // qDebug() << "DEATH " << platform << " -----> (x, y, width, height) : (" << platform->getX() << ", " << platform->getY() << ", " << platform->getWidth() * platform->getItemWidth() << ", " << platform->getHeight() * platform->getItemHeight() << ") //// Player : " << x() << ", " << y() << ", " << width << ", " << height;
    death();
}

void Player::death(){
    setPos(spawn_x, spawn_y);
    scene->setDeaths(scene->getDeaths() + 1);
    vert_speed = 0;
    hori_speed = 0;
    next_jump_speed = base_vert_speed;
    for(int i = 0; i < 3; i++){
        skills_available[i] = false;
    }
    scene->getInfos()->updateSkills();
    if(has_shield){
        removeShield();
    }
    if(height == 24){
        increasePlayerSize();
    }
    scene->toInitialState();
}

void Player::setSpawnPoint(int x, int y){
    spawn_x = x;
    spawn_y = y;
}

bool Player::getSkillsAvailable(unsigned short int index) {
    if(index > 2 || index < 0){
        qDebug() << "Index out of range";
        return false;
    }
    return skills_available[index];
}

void Player::setSkillsAvailable(unsigned short int index) {
    if(index > 2 || index < 0){
        qDebug() << "Index out of range";
        return;
    }
    skills_available[index] = true;
}

void Player::useSuperJump(){
    next_jump_speed = 13;
    skills_available[0] = false;
    scene->getInfos()->updateSkills();
}

void Player::useDash(){
    if(!scene->getPressedKeys(0) && !scene->getPressedKeys(1)){
        return;
    }

    hori_speed = 0;
    if(scene->getPressedKeys(0)){
        hori_speed -= 4;
    }
    if(scene->getPressedKeys(1)){
        hori_speed += 4;
    }

    auto views = scene->views();

    for(int i = 0; i < 16; i++){
        if(scene->getPressedKeys(0) && !scene->getPressedKeys(1)){
            if(isColliding("left", hori_speed) != nullptr){
                hori_speed = 0;
            }
        }
        else if(hori_speed > 0){
            if(isColliding("right", hori_speed) != nullptr){
                hori_speed = 0;
            }
        }
        setX(x() + hori_speed);
        views[1]->centerOn(this);
        scene->getInfos()->update();
    }

    skills_available[1] = false;
    scene->getInfos()->updateSkills();
}

void Player::useShield(){
    if(has_shield){
        return;
    }
    skills_available[2] = false;
    scene->getInfos()->updateSkills();
    shield = new QGraphicsPixmapItem(QPixmap("resources/shield.png"));
    shield->setScale(0.1);
    shield->setPos(x() + width / 2 - 13, y() + height / 2 - 32);
    scene->addItem(shield);
    has_shield = true;
    updateShield();
}

void Player::updateShield(){
    if(has_shield){
        shield->setScale(scale() / 10);
        int s_width = 26;
        int s_height = 64;
        if(width != 26){
            s_width = 13;
            s_height = 32;
        }
        shield->setPos(x() + width / 2 - s_width / 2, y() + height / 2 - s_height / 2);
    }
}

int Player::getNextJumpSpeed(){
    return next_jump_speed;
}

void Player::setNextJumpSpeed(int s){
    next_jump_speed = s;
}

bool Player::hasShield(){
    return has_shield;
}

void Player::removeShield(){
    has_shield = false;
    scene->removeItem(shield);
    delete shield;
}

void Player::reducePlayerSize(){
    width = 13;
    height = 24;
    setScale(0.5);
    setY(y() + 24);
    base_hori_speed = 3;
    base_vert_speed = 8;
}

void Player::increasePlayerSize(){
    width = 26;
    height = 48;
    setScale(1);
    setY(y() - 24);
    base_hori_speed = 4;
    base_vert_speed = 9;
}

int Player::getWidth(){
    return width;
}

void Player::setWidth(int w){
    width = w;
}

int Player::getHeight(){
    return height;
}

void Player::setHeight(int h){
    height = h;
}

float Player::getBaseVertSpeed(){
    return base_vert_speed;
}

void Player::isOnIce(){
    is_on_ice = true;
}

int Player::getSpawnX() {
    return spawn_x;
}

int Player::getSpawnY() {
    return spawn_y;
}