#include "LevelEnd.h"
#include "math.h"

LevelEnd::LevelEnd(MyScene* scene, Player* player, Infos* infos, Menu* menu, QGraphicsItem* parent) : QGraphicsProxyWidget(parent), scene(scene), player(player), infos(infos), menu(menu){
    setZValue(4);

    QWidget* mainWidget = new QWidget();
    setWidget(mainWidget);
    mainWidget->setStyleSheet("font-size: 5px;");

    width = 300;
    height = 200;

    // Calcul du score
    int deaths_count = scene->getDeaths();
    if(deaths_count > 10){
        deaths_count = 10;
    }
    int minutes = infos->getMinutes();
    int seconds = floor(infos->getSeconds()) + 60 * minutes;
    if(seconds > 3600){
        seconds = 3600;
    }
    int coins = scene->getCoinsCount();

    int score = 10000; // Niveau terminé
    int death_score = 10000 - (deaths_count * 1000); // Morts
    int time_score = (3600 - seconds) * 10; // Temps
    int coins_score = coins * 1000; // Pièces ramassées

    score += death_score + time_score + coins_score;

    QString star_save = "";

    // Vérification de s'il y a nouveau record et update du fichier records.txt
    scene->getMainWindow()->getPlayerData()->updatePlayerData(scene->getLevel(), score, QString::number(minutes) + ":" + QString::number(infos->getSeconds()));
    auto records = scene->getMainWindow()->getPlayerData()->getRecords()->value(scene->getLevel());

    // Fonts
    int id = QFontDatabase::addApplicationFont("../fonts/albas.TTF");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont albas(family);

    id = QFontDatabase::addApplicationFont("../fonts/Maghrib-MVZpx.ttf");
    family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont maghrib(family);

    id = QFontDatabase::addApplicationFont("../fonts/BubbleBobble-rg3rx.ttf");
    family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont bubble(family);

    // Remplissage de l'écran de fin de niveau
    QVBoxLayout* v_layout = new QVBoxLayout();
    mainWidget->setLayout(v_layout);

    // Titre
    QLabel* title = new QLabel();
    if(scene->getLevel() != 0){
        title->setText("Niveau " + QString::number(scene->getLevel()) + " terminé !!!");
    }
    else{
        title->setText("Introduction terminée !!!\nVous êtes prêt pour partir à l'aventure !");
        height += 50;
    }
    star_save += "1/";
    title->setStyleSheet("font-size: 10px;");
    title->setFont(maghrib);
    title->setAlignment(Qt::AlignHCenter);
    v_layout->addWidget(title);

    // Etoiles
    QWidget* stars_widget = new QWidget();
    stars_widget->setStyleSheet("border: 1px solid black;");
    QVBoxLayout* stars_layout = new QVBoxLayout();
    stars_layout->setSpacing(2);
    stars_widget->setLayout(stars_layout);

    QWidget* stars_wg = new QWidget;
    QHBoxLayout* stars = new QHBoxLayout;
    stars->setSpacing(0);
    stars->setMargin(0);
    stars_wg->setLayout(stars);
    stars_wg->setStyleSheet("border: 0px solid black;");

    QWidget* labels_wg = new QWidget;
    QHBoxLayout* labels = new QHBoxLayout;
    labels->setSpacing(0);
    labels->setMargin(0);
    labels_wg->setLayout(labels);
    labels_wg->setStyleSheet("border: 0px solid black;");

    // Niveau terminé
    QLabel* star1 = new QLabel();
    star1->setPixmap(QPixmap("../ressources/star_full.png"));
    star1->setFixedSize(48, 48);
    star1->setScaledContents(true);
    stars->addWidget(star1);

    QLabel* label1 = new QLabel();
    label1->setText("Niveau terminé");
    label1->setFont(albas);
    label1->setMaximumWidth(48);
    label1->setAlignment(Qt::AlignHCenter);
    labels->addWidget(label1);

    // Pièces ramassées
    QLabel* star2 = new QLabel();
    if(coins == scene->getTotalCoins()){
        star2->setPixmap(QPixmap("../ressources/star_full.png"));
        star_save += "1/";
    }
    else{
        star2->setPixmap(QPixmap("../ressources/star_empty.png"));
        star_save += "0/";
    }
    star2->setFixedSize(48, 48);
    star2->setScaledContents(true);
    stars->addWidget(star2);

    QWidget* label2 = new QWidget;
    label2->setMaximumWidth(48);
    QVBoxLayout* label2_layout = new QVBoxLayout;
    label2_layout->setSpacing(0);
    label2_layout->setMargin(0);
    label2->setLayout(label2_layout);

    QLabel* label21 = new QLabel();
    label21->setText("Pièces ramassées");
    label21->setFont(albas);
    label21->setFixedWidth(48);
    label21->setAlignment(Qt::AlignHCenter);
    label2_layout->addWidget(label21);

    QLabel* label22 = new QLabel();
    label22->setText(QString::number(coins) +" / " + QString::number(scene->getTotalCoins()));
    label22->setFont(bubble);
    label22->setFixedWidth(48);
    label22->setAlignment(Qt::AlignHCenter);
    label2_layout->addWidget(label22);

    label2_layout->setSpacing(0);

    labels->addWidget(label2);

    // Morts
    QLabel* star3 = new QLabel();
    if(scene->getDeaths() == 0){
        star3->setPixmap(QPixmap("../ressources/star_full.png"));
        star_save += "1/";
    }
    else{
        star3->setPixmap(QPixmap("../ressources/star_empty.png"));
        star_save += "0/";
    }
    star3->setFixedSize(48, 48);
    star3->setScaledContents(true);
    stars->addWidget(star3);

    QWidget* label3 = new QWidget;
    label3->setMaximumWidth(48);
    QVBoxLayout* label3_layout = new QVBoxLayout;
    label3_layout->setSpacing(0);
    label3_layout->setMargin(0);
    label3->setLayout(label3_layout);

    QLabel* label31 = new QLabel();
    label31->setText("Mort(s)");
    label31->setFont(albas);
    label31->setFixedWidth(48);
    label31->setAlignment(Qt::AlignHCenter);
    label3_layout->addWidget(label31);

    QLabel* label32 = new QLabel();
    label32->setText(QString::number(scene->getDeaths()));
    label32->setFont(bubble);
    label32->setFixedWidth(48);
    label32->setAlignment(Qt::AlignHCenter);
    label3_layout->addWidget(label32);

    label3_layout->setSpacing(0);

    labels->addWidget(label3);

    // Temps
    QLabel* star4 = new QLabel();

    if(minutes < 2){
       star4->setPixmap(QPixmap("../ressources/star_full.png"));
       star_save += "1";
    }
    else{
        star4->setPixmap(QPixmap("../ressources/star_empty.png"));
        star_save += "0";
    }
    star4->setFixedSize(48, 48);
    star4->setScaledContents(true);
    stars->addWidget(star4);

    scene->getMainWindow()->getPlayerData()->updatePlayerStars(scene->getLevel(), star_save);

    QWidget* label4 = new QWidget;
    label4->setMaximumWidth(48);
    QVBoxLayout* label4_layout = new QVBoxLayout;
    label4_layout->setSpacing(0);
    label4_layout->setMargin(0);
    label4->setLayout(label4_layout);

    QLabel* label41 = new QLabel();
    label41->setText("Temps");
    label41->setFont(albas);
    label41->setFixedWidth(48);
    label41->setAlignment(Qt::AlignHCenter);
    label4_layout->addWidget(label41);

    QLabel* label42 = new QLabel();
    label42->setText(QString::number(minutes) + ":" + QString::number(infos->getSeconds(), 'f', 2) + " / 2:00.0");
    label42->setFont(bubble);
    label42->setFixedWidth(48);
    label42->setAlignment(Qt::AlignHCenter);
    label4_layout->addWidget(label42);

    label4_layout->setSpacing(0);

    labels->addWidget(label4);

    stars_layout->addWidget(stars_wg);
    stars_layout->addWidget(labels_wg);
    stars_layout->setMargin(0);
    stars_layout->setContentsMargins(0, 0, 0, 10);
    stars_layout->setSpacing(2);

    v_layout->addWidget(stars_widget);

    QWidget* best_widget = new QWidget;
    QHBoxLayout* best = new QHBoxLayout;
    best->setAlignment(Qt::AlignLeft);
    best->setSpacing(5);
    best_widget->setLayout(best);

    QWidget* score_player_widget = new QWidget;
    QHBoxLayout* score_player_layout = new QHBoxLayout;
    score_player_widget->setLayout(score_player_layout);
    score_player_layout->setMargin(0);

    QWidget* time_widget = new QWidget;
    QVBoxLayout* time_layout = new QVBoxLayout;
    time_widget->setLayout(time_layout);
    time_widget->setStyleSheet("border: 1px solid black;");
    time_widget->setFixedWidth(80);
    time_layout->setMargin(2);

    QWidget* score_widget = new QWidget;
    QVBoxLayout* score_layout = new QVBoxLayout;
    score_widget->setLayout(score_layout);
    score_widget->setStyleSheet("border: 1px solid black;");
    score_widget->setFixedWidth(80);
    score_layout->setMargin(2);

    best->addWidget(time_widget);
    best->addWidget(score_widget);

    QLabel* time_label = new QLabel;
    time_label->setAlignment(Qt::AlignCenter);
    time_label->setStyleSheet("border: 0px solid black;");
    time_label->setFont(bubble);
    QLabel* time_best = new QLabel;
    time_best->setAlignment(Qt::AlignCenter);
    time_best->setStyleSheet("border: 0px solid black;");
    time_best->setFont(bubble);
    if(records->value("time") == QString::number(minutes) + ":" + QString::number(infos->getSeconds())){
        time_label->setText("Nouveau record de temps !");
        time_best->setText(records->value("time") + "\n(" + records->value("time_player") + ")");
    }
    else{
        time_label->setText("Record de temps");
        time_best->setText(records->value("time") + "\n(" + records->value("time_player") + ")");
    }
    time_label->setFont(albas);
    time_layout->addWidget(time_label);
    time_layout->addWidget(time_best);

    QLabel* score_label = new QLabel;
    score_label->setAlignment(Qt::AlignCenter);
    score_label->setStyleSheet("border: 0px solid black;");
    score_label->setFont(bubble);
    QLabel* score_best = new QLabel;
    score_best->setStyleSheet("border: 0px solid black;");
    score_best->setFont(bubble);
    score_best->setAlignment(Qt::AlignCenter);
    if(records->value("score") == QString::number(score)){
        score_label->setText("Nouveau record de score !");
        score_best->setText(records->value("score") + "\n(" + records->value("score_player") + ")");
    }
    else{
        score_label->setText("Record de score");
        score_best->setText(records->value("score") + "\n(" + records->value("score_player") + ")");
    }
    score_label->setFont(albas);
    score_layout->addWidget(score_label);
    score_layout->addWidget(score_best);

    QWidget* player_widget = new QWidget;
    player_widget->setContentsMargins(0, 0, 20, 0);
    QVBoxLayout* player_layout = new QVBoxLayout;
    player_layout->setAlignment(Qt::AlignRight);
    player_widget->setLayout(player_layout);

    moving_player = new QLabel;
    moving_player->setPixmap(QPixmap("../ressources/player_bag_2"));
    moving_player->setFixedWidth(42);
    player_layout->addWidget(moving_player);

    score_player_layout->addWidget(best_widget);
    score_player_layout->addWidget(player_widget);
    v_layout->addWidget(score_player_widget);

    QHBoxLayout* h_layout = new QHBoxLayout;

    QPushButton* restart = new QPushButton("Recommencer le niveau");
    h_layout->addWidget(restart);
    QPushButton* exit = new QPushButton("Retour vers le menu");
    h_layout->addWidget(exit);
    h_layout->setMargin(0);

    QObject::connect(restart, SIGNAL(clicked()), this, SLOT(restart()));
    QObject::connect(exit, SIGNAL(clicked()), this, SLOT(exit()));

    QWidget* buttons_widget = new QWidget;
    v_layout->addWidget(buttons_widget);
    buttons_widget->setLayout(h_layout);

    setMaximumSize(width, height);
    resize(width, height);

    updatePos();

    // Animation du personnage

    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updatePlayer()));
    timer->start(200);

    animation_status = 2;
    animation_direction = 1;

    menu->updateLockedLevels();
}

LevelEnd::~LevelEnd(){
    qDebug() << this;
}

void LevelEnd::updatePos(){
    int coord_x = player->x() + player->getWidth() / 2  - (width / 2);
    int coord_y = player->y() + player->getHeight() / 2  - (height / 2);
    float window_width = scene->getMainWindow()->window()->size().width() / 3; // /3 pour le scale
    float window_height = scene->getMainWindow()->window()->size().height() / 3;

    if(player->x() <  window_width / 2 - player->getWidth() / 2){
        coord_x = window_width / 2 - (width / 2);
    }
    if(player->x() > scene->sceneRect().width() - (window_width / 2) - player->getWidth() / 2){
        coord_x = scene->sceneRect().width() - (window_width / 2) - (width / 2);
    }
    if(player->y() < window_height / 2 - player->getHeight() / 2){
        coord_y = window_height / 2 - (height / 2);
    }
    if(player->y() > scene->sceneRect().height() - (window_height / 2) - player->getHeight() / 2){
        coord_y = scene->sceneRect().height() - (window_height / 2) - (height / 2);
    }

    setPos(coord_x, coord_y);
}

void LevelEnd::exit(){
    scene->exit();
}

void LevelEnd::restart(){
    scene->restart();
    scene->removeItem(this);
}

void LevelEnd::updatePlayer(){
    if(animation_status == 1){
        animation_direction = 1;
    }
    if(animation_status == 3){
        animation_direction = -1;
    }
    animation_status += animation_direction;
    moving_player->setPixmap(QPixmap("../ressources/player_bag_" + QString::number(animation_status) + ".png"));
}