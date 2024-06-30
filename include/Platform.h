#ifndef PLATFORM_H
#define PLATFORM_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QPixmap>
#include <QString>
#include <QDebug>
#include "MyScene.h"
#include "Player.h"
#include "utils.h"

class MyScene;
class Player;

class Platform : public QObject{
    Q_OBJECT
protected:
    int x;
    int y;
    int width;
    int height;
    int item_width;
    int item_height;
    QGraphicsPixmapItem*** graphics_items;
    Player* player;
    MyScene* scene;
public:
    Platform(MyScene* scene, Player* player, int x, int y, int width, int height, QString ressource_url, int item_width = 16, int item_height = 16);
    ~Platform();
    void itemsGeneration(QString ressource_url, int new_width = 0, int new_height = 0);
    QGraphicsPixmapItem*** getItems();
    int getX();
    int getY();
    int getWidth();
    int getHeight();
    int getItemWidth();
    int getItemHeight();
    virtual void isOnIt();
    void moveTo(int new_x, int new_y);
    void platformCollidesWithGravitySensitiveItem(bool positive_speed, bool movement_vertical, QVector<Platform*>* platforms_moved = nullptr, QVector<Platform*>* platforms_to_move = nullptr);
    void updateImage(QString ressource_url);
    void deleteItems();
    virtual void toInitialState();
};

#include "MovingPlatform.h"
#include "PushablePlatform.h"
#include "BreakablePlatform.h"
#include "SkillPlatform.h"
#include "SlidingPlatform.h"
#include "SemiPassablePlatform.h"
#include "Button.h"
#include "Lava.h"

#endif