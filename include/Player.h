#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QPixmap>
#include <QString>
#include <QDebug>
#include "MyScene.h"

class MyScene;
class Platform;

class Player : public QGraphicsPixmapItem{
private:
    MyScene* scene;
    float vert_speed;
    float hori_speed;
    float base_vert_speed;
    float base_hori_speed;
    float ice_speed;
    int spawn_x;
    int spawn_y;
    int width;
    int height;
    int next_jump_speed;
    bool skills_available[3];
    bool has_shield;
    bool is_on_ice;
    QGraphicsPixmapItem* shield;
    int animation_status;
    int animation_time;
    int animation_direction;
    bool facing_left;
public:
    Player(QString ressource_url, MyScene* scene);
    ~Player();
    void move();
    void setVerticalSpeed(int speed);
    Platform* isColliding(QString direction, float speed = 0);
    bool collidesWithPlatform(Platform* platform, int v_speed = 0, int h_speed = 0);
    float getHorizontalSpeed();
    float getVerticalSpeed();
    void death(Platform* platform);
    void death();
    void setSpawnPoint(int x, int y);
    bool getSkillsAvailable(unsigned short int index);
    void setSkillsAvailable(unsigned short int index);
    void useSuperJump();
    void useDash();
    void useShield();
    void updateShield();
    int getNextJumpSpeed();
    void setNextJumpSpeed(int s);
    bool hasShield();
    void removeShield();
    void reducePlayerSize();
    void increasePlayerSize();
    int getWidth();
    void setWidth(int w);
    int getHeight();
    void setHeight(int h);
    float getBaseVertSpeed();
    void jump();
    void isOnIce();
    int getSpawnX();
    int getSpawnY();
};

#endif