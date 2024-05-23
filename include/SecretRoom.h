#ifndef SECRETROOM_H
#define SECRETROOM_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QString>
#include <QDebug>
#include "MyScene.h"
#include "Player.h"

class MyScene;
class Player;

class SecretRoom : public QObject{
    Q_OBJECT
protected:
    int x;
    int y;
    int width;
    int height;
    QGraphicsPixmapItem*** graphics_items;
    Player* player;
    MyScene* scene;
    bool is_hidden;
public:
    SecretRoom(MyScene* scene, Player* player, int x, int y, int width, int height, QString ressource_url);
    ~SecretRoom();
    void itemsGeneration(QString ressource_url, int w = 0, int h = 0);
    QGraphicsPixmapItem*** getItems();
    void collidesWithSecretRoom();
    int getX();
    int getY();
    int getWidth();
    int getHeight();
    void deleteItems();
    void hide();
    void show();
    virtual void toInitialState();
};

#endif