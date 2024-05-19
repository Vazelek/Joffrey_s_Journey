#ifndef MYSCENE_H
#define MYSCENE_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPixmap>
#include <QTimer>
#include <QString>
#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QRectF>
#include <QKeyEvent>
#include <QVector>
#include <QLabel>
#include <QSoundEffect>
#include <QSound>
#include <QMediaPlayer>
#include <QFileInfo>
#include <QFontDatabase>
#include <QMediaPlaylist>
#include <QDir>
#include <fstream>
#include <string>
#include "MainWindow.h"
#include "Platform.h"
#include "Player.h"
#include "EventItem.h"
#include "Pause.h"
#include "Menu.h"
#include "Infos.h"
#include "LevelEnd.h"
#include "SecretRoom.h"
#include "TextArea.h"

#define FPS 60

class Player;
class Platform;
class MovingPlatform;
class PushablePlatform;
class BreakablePlatform;
class SkillPlatform;
class SlidingPlatform;
class SemiPassablePlatform;
class Lava;
class Button;
class Flag;
class Pause;
class LevelEnd;
class MainWindow;
class Menu;
class Infos;
class Coin;
class EventItem;
class SecretRoom;

enum Language {FR, EN};

class MyScene : public QGraphicsScene {
    Q_OBJECT

private:
    MainWindow* window;
    QGraphicsView* player_view;
    Menu* menu;
    QPixmap background;
    Player* player;
    QTimer* timer;
    Infos* infos;
    int level;
    bool pressed_keys[4] = {0};
    QVector<Platform*> platforms;
    QVector<MovingPlatform*> moving_platforms;
    QVector<PushablePlatform*> pushable_platforms;
    QVector<BreakablePlatform*> breakable_platforms;
    QVector<SkillPlatform*> skill_platform;
    QVector<SlidingPlatform*> sliding_platforms;
    QVector<SemiPassablePlatform*> semi_passable_platforms;
    QVector<Lava*> lava_areas;
    QVector<Button*> buttons;
    QVector<EventItem*> event_items;
    QVector<SecretRoom*> secret_rooms;
    QVector<Flag*> flags;
    Pause* pause;
    bool pause_menu_displayed;
    int deaths;
    int coins_count;
    int total_coins;
    bool game_stopped;
    int spawn_x;
    int spawn_y;
    Language language = Language::EN;

public:
    MyScene(MainWindow* window, QGraphicsView* player_view, Menu* menu, int level, QObject* parent = nullptr);
    void drawBackground(QPainter* painter, const QRectF& rect);
    virtual ~MyScene();
    void gamePause();
    void gameStart();
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);
    bool getPressedKeys(unsigned short int index);
    QVector<Platform*>* getPlatforms();
    QVector<MovingPlatform*>* getMovingPlatforms();
    QVector<PushablePlatform*>* getPushablePlatforms();
    QVector<BreakablePlatform*>* getBreakablePlatforms();
    QVector<SkillPlatform*>* getSkillPlatforms();
    QVector<SlidingPlatform*>* getSlidingPlatforms();
    QVector<SemiPassablePlatform*>* getSemiPassablePlatforms();
    QVector<Lava*>* getLavaAreas();
    QVector<Button*>* getButtons();
    QVector<EventItem*>* getEventItems();
    QVector<SecretRoom*>* getSecretRooms();
    MainWindow* getMainWindow();
    Infos* getInfos();
    void pushPlatform(Platform* platform);
    void pushMovingPlatform(MovingPlatform* platform);
    void pushPushablePlatform(PushablePlatform* platform);
    void pushBreakablePlatform(BreakablePlatform* platform);
    void pushSkillPlatform(SkillPlatform* platform);
    void pushSlidingPlatform(SlidingPlatform* platform);
    void pushSemiPassablePlatform(SemiPassablePlatform* platform);
    void pushLavaArea(Lava* lava);
    void pushButton(Button* button);
    void pushEventItem(EventItem* item);
    void pushSecretRoom(SecretRoom* secret_room);
    void pushFlag(Flag* flag);
    void readLevelGenerationFile();
    void restart();
    int getDeaths();
    int getCoinsCount();
    int getTotalCoins();
    int getLevel();
    void setDeaths(int n);
    void setCoinsCount(int n);
    void setTotalCoins(int n);
    void levelEnd();
    void toInitialState();
    void exit();
    Language getLanguage();

public slots:
    void update();

};


#endif //MYSCENE_H
