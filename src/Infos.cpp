#include "Infos.h"
#include "math.h"

Infos::Infos(MyScene* scene, Player* player, QGraphicsItem* parent) : QGraphicsProxyWidget(parent), scene(scene), player(player), minutes(0), seconds(0){

    setZValue(3);

    QWidget* widget = new QWidget;
    setWidget(widget);

    widget->setAttribute(Qt::WA_TranslucentBackground, true);

    QHBoxLayout* layout = new QHBoxLayout;
    widget->setLayout(layout);
    QWidget* left_widget = new QWidget;
    layout->addWidget(left_widget);
    QWidget* right_widget = new QWidget;
    layout->addWidget(right_widget);

    // Infos part ----------------------------------------------------------------------------------------------------
    QHBoxLayout* layout_right = new QHBoxLayout;
    right_widget->setLayout(layout_right);
    layout_right->setAlignment(Qt::AlignRight);

    // Coins
    QWidget* coins_widget = new QWidget;
    QHBoxLayout* coins_layout = new QHBoxLayout;
    coins_widget->setLayout(coins_layout);
    coins_layout->setMargin(5);

    QLabel* coins_image = new QLabel;
    coins_image->setPixmap(QPixmap("../ressources/coin_icon.png"));
    coins_image->setFixedSize(16, 16);
    coins_image->setScaledContents(true);
    coins_layout->addWidget(coins_image);

    coins = new QLabel;
    coins->setText("0/20");
    coins->setStyleSheet("background-color: rgba(255, 255, 255, 0.5);");
    coins_layout->addWidget(coins);

    layout_right->addWidget(coins_widget);


    // Deaths
    QWidget* deaths_widget = new QWidget;
    QHBoxLayout* deaths_layout = new QHBoxLayout;
    deaths_widget->setLayout(deaths_layout);
    deaths_layout->setMargin(5);

    QLabel* deaths_image = new QLabel;
    deaths_image->setPixmap(QPixmap("../ressources/death.png"));
    deaths_image->setFixedSize(16, 16);
    deaths_image->setScaledContents(true);
    deaths_layout->addWidget(deaths_image);

    deaths = new QLabel;
    deaths->setText("0");
    deaths->setStyleSheet("background-color: rgba(255, 255, 255, 0.5);");
    deaths_layout->addWidget(deaths);

    layout_right->addWidget(deaths_widget);


    // Chronometer
    QWidget* chrono_widget = new QWidget;
    QHBoxLayout* chrono_layout = new QHBoxLayout;
    chrono_widget->setLayout(chrono_layout);
    chrono_layout->setMargin(5);

    QLabel* chronometer_image = new QLabel;
    chronometer_image->setPixmap(QPixmap("../ressources/clock.png"));
    chronometer_image->setFixedSize(16, 16);
    chronometer_image->setScaledContents(true);
    chrono_layout->addWidget(chronometer_image);

    chronometer = new QLabel;
    chronometer->setText("00:00");
    chronometer->setStyleSheet("background-color: rgba(255, 255, 255, 0.5);");
    chrono_layout->addWidget(chronometer);

    layout_right->addWidget(chrono_widget);


    // Skills part ---------------------------------------------------------------------------------------------------
    QHBoxLayout* layout_left = new QHBoxLayout;
    left_widget->setLayout(layout_left);
    layout_left->setAlignment(Qt::AlignLeft);

    // Super jump
    jump  = new QLabel;
    jump->setPixmap(QPixmap("../ressources/jump_empty.png"));
    jump->setFixedSize(16, 16);
    jump->setScaledContents(true);
    layout_left->addWidget(jump);

    // Dash
    dash  = new QLabel;
    dash->setPixmap(QPixmap("../ressources/dash_empty.png"));
    dash->setFixedSize(16, 16);
    dash->setScaledContents(true);
    layout_left->addWidget(dash);

    // Shield
    shield  = new QLabel;
    shield->setPixmap(QPixmap("../ressources/shield_empty.png"));
    shield->setFixedSize(16, 16);
    shield->setScaledContents(true);
    layout_left->addWidget(shield);



    width = scene->getMainWindow()->window()->size().width() / 3;
    height = 10;

    setPos(0, 0);
    resize(width, height);

}

Infos::~Infos(){

}

void Infos::update(){

    float window_width = scene->getMainWindow()->window()->size().width() / 3;
    float window_height = scene->getMainWindow()->window()->size().height() / 3;
    int coord_x = player->x() + player->getWidth() / 2  + (window_width / 2) - width;
    int coord_y = player->y() + player->getHeight() / 2  - (window_height / 2);

    if(player->x() <  window_width / 2 - player->getWidth() / 2){
        coord_x = window_width - width;
    }
    if(player->x() > scene->sceneRect().width() - (window_width / 2) - player->getWidth() / 2){
        coord_x = scene->sceneRect().width() - width;
    }
    if(player->y() < window_height / 2 - player->getHeight() / 2){
        coord_y = 0;
    }
    if(player->y() > scene->sceneRect().height() - (window_height / 2) - player->getHeight() / 2){
        coord_y = scene->sceneRect().height() - window_height;
    }

    setPos(coord_x, coord_y - 22);

    seconds += (double) 1 / FPS; // Not precise
    if(seconds >= 60){
        seconds -= 60;
        minutes++;
    }

    QString sec = "";

    if(seconds < 10){
        sec = "0";
    }

    QString min = "";

    if(minutes < 10){
        min = "0";
    }

    chronometer->setText(min + QString::number(minutes) + ":" + sec + QString::number(seconds, 'f', 2));
    deaths->setText(QString::number(scene->getDeaths()));
    coins->setText(QString::number(scene->getCoinsCount()) + "/" + QString::number(scene->getTotalCoins()));
}

int Infos::getMinutes(){
    return minutes;
}

double Infos::getSeconds(){
    return seconds;
}

void Infos::updateSkills(){
    if(player->getSkillsAvailable(0)){
        jump->setPixmap(QPixmap("../ressources/jump_full.png"));
    }
    else{
        jump->setPixmap(QPixmap("../ressources/jump_empty.png"));
    }

    if(player->getSkillsAvailable(1)){
        dash->setPixmap(QPixmap("../ressources/dash_full.png"));
    }
    else{
        dash->setPixmap(QPixmap("../ressources/dash_empty.png"));
    }

    if(player->getSkillsAvailable(2)){
        shield->setPixmap(QPixmap("../ressources/shield_full.png"));
    }
    else{
        shield->setPixmap(QPixmap("../ressources/shield_empty.png"));
    }
}

void Infos::toZero(){
    minutes = 0;
    seconds = 0;
}