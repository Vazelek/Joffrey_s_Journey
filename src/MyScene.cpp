#include "MyScene.h"

MyScene::MyScene(MainWindow* window, QGraphicsView* player_view, Menu* menu, int level, QObject* parent) : QGraphicsScene(parent), window(window), player_view(player_view), menu(menu), level(level), deaths(0), coins_count(0), total_coins(0), game_stopped(false) {

    // Chargement de l'arrière plan
    background.load("../ressources/background_" + QString::number(level) + ".png");
    setSceneRect(0, 0, background.width(), background.height());

    // Chargement du joueur
    player = new Player("../ressources/player_2.png", this);
    player->setScale(1);

    // Génération des élément (lecture du fichier correspondant au level)
    readLevelGenerationFile();

    // Affichage du joueur (par dessus tous les éléments)
    addItem(player);

    // Timer pour les FPS
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(1000 / FPS);

    // Chargement du menu de pause (non affiché)
    pause = new Pause(this, player);
    pause_menu_displayed = false;

    // Chargement du widget infos
    infos = new Infos(this, player);
    addItem(infos);
}

void MyScene::readLevelGenerationFile(){
    std::string line = "";
    std::string values[11] = {""};
    std::ifstream file("../data/level_" + std::to_string(level) + ".txt");
    int index = 0;
    if(file.is_open()){

        // Lecture de la partie data -----------------------------------------------------------------------------------
        while(line.find("{") == std::string::npos){
            getline(file, line);
        }
        while(line.find("}") == std::string::npos){
            if(line.find("(") != std::string::npos){
                values[index] = line.std::string::substr(line.find("(") + 1, line.find(")") - line.find("(") - 1);
                index++;
            }
            getline(file, line);
        }

        // Placement initial du joueur
        player->setSpawnPoint(std::stoi(values[0]), std::stoi(values[1]));
        player->setPos(std::stoi(values[0]), std::stoi(values[1]));
        spawn_x = std::stoi(values[0]);
        spawn_y = std::stoi(values[1]);

        for(int i = 0; i < 11; i++){
            values[i] = "";
        }

        getline(file, line);

        // Lecture de la partie platformes -----------------------------------------------------------------------------
        while(line.find("{") == std::string::npos){
            getline(file, line);
        }
        while(line.find("}") == std::string::npos){

            // Vérification s'il n'y a pas d'espaces en trop dans le fichier de génération
            if(line.find("[") == std::string::npos){
                getline(file, line);
                continue;
            }

            index = 0;
            while(line.find("]") == std::string::npos){
                if(line.find("(") != std::string::npos){
                    values[index] = line.std::string::substr(line.find("(") + 1, line.find(")") - line.find("(") - 1);
                    index++;
                }
                getline(file, line);
            }

            // Génération des plateformes
            // Gestion des valeurs par défaut
            if(values[5] == ""){
                values[5] = "16";
            }
            if(values[6] == ""){
                values[6] = "16";
            }

            Platform* platform = new Platform(
                    this,
                    player,
                    std::stoi(values[0]),
                    std::stoi(values[1]),
                    std::stoi(values[2]),
                    std::stoi(values[3]),
                    QString::fromStdString(values[4]),
                    std::stoi(values[5]),
                    std::stoi(values[6]));

            for(int i = 0; i < 11; i++){
                values[i] = "";
            }

            getline(file, line);
        }

        // Lecture de la partie platformes mobiles ---------------------------------------------------------------------
        while(line.find("{") == std::string::npos){
            getline(file, line);
        }
        while(line.find("}") == std::string::npos){

            // Vérification s'il n'y a pas d'espaces en trop dans le fichier de génération
            if(line.find("[") == std::string::npos){
                getline(file, line);
                continue;
            }

            index = 0;
            while(line.find("]") == std::string::npos){
                if(line.find("(") != std::string::npos){
                    values[index] = line.std::string::substr(line.find("(") + 1, line.find(")") - line.find("(") - 1);
                    index++;
                }
                getline(file, line);
            }

            // Génération des plateformes mobiles
            // Gestion des valeurs par défaut
            if(values[8] == ""){
                values[8] = "true";
            }
            if(values[9] == ""){
                values[9] = "-1";
            }
            if(values[10] == ""){
                values[10] = "-666";
            }

            // Traduction des booléens
            bool bool1 = true;
            bool bool2 = true;
            if(values[6] == "false"){
                bool1 = false;
            }
            if(values[8] == "false"){
                bool2 = false;
            }

            MovingPlatform* platform = new MovingPlatform(
                    this,
                    player,
                    std::stoi(values[0]),
                    std::stoi(values[1]),
                    std::stoi(values[2]),
                    std::stoi(values[3]),
                    QString::fromStdString(values[4]),
                    std::stoi(values[5]),
                    bool1,
                    std::stoi(values[7]),
                    bool2,
                    std::stoi(values[9]),
                    std::stoi(values[10]));

            for(int i = 0; i < 11; i++){
                values[i] = "";
            }


            getline(file, line);
        }

        // Lecture de la partie platformes poussables ------------------------------------------------------------------
        while(line.find("{") == std::string::npos){
            getline(file, line);
        }
        while(line.find("}") == std::string::npos){

            // Vérification s'il n'y a pas d'espaces en trop dans le fichier de génération
            if(line.find("[") == std::string::npos){
                getline(file, line);
                continue;
            }

            index = 0;
            while(line.find("]") == std::string::npos){
                if(line.find("(") != std::string::npos){
                    values[index] = line.std::string::substr(line.find("(") + 1, line.find(")") - line.find("(") - 1);
                    index++;
                }
                getline(file, line);
            }

            // Génération des plateformes poussables

            PushablePlatform* platform = new PushablePlatform(
                    this,
                    player,
                    std::stoi(values[0]),
                    std::stoi(values[1]),
                    std::stoi(values[2]),
                    std::stoi(values[3]),
                    QString::fromStdString(values[4]));

            for(int i = 0; i < 11; i++){
                values[i] = "";
            }


            getline(file, line);
        }

        // Lecture de la partie platformes cassables -------------------------------------------------------------------
        while(line.find("{") == std::string::npos){
            getline(file, line);
        }
        while(line.find("}") == std::string::npos){

            // Vérification s'il n'y a pas d'espaces en trop dans le fichier de génération
            if(line.find("[") == std::string::npos){
                getline(file, line);
                continue;
            }

            index = 0;
            while(line.find("]") == std::string::npos){
                if(line.find("(") != std::string::npos){
                    values[index] = line.std::string::substr(line.find("(") + 1, line.find(")") - line.find("(") - 1);
                    index++;
                }
                getline(file, line);
            }

            // Génération des plateformes cassables
            // Gestion des valeurs par défaut
            if(values[5] == ""){
                values[5] = "-1";
            }

            BreakablePlatform* platform = new BreakablePlatform(
                    this,
                    player,
                    std::stoi(values[0]),
                    std::stoi(values[1]),
                    std::stoi(values[2]),
                    std::stoi(values[3]),
                    std::stoi(values[4]),
                    std::stoi(values[5]));

            for(int i = 0; i < 11; i++){
                values[i] = "";
            }

            getline(file, line);
        }

        // Lecture de la partie skill platform -------------------------------------------------------------------------
        while(line.find("{") == std::string::npos){
            getline(file, line);
        }
        while(line.find("}") == std::string::npos){

            // Vérification s'il n'y a pas d'espaces en trop dans le fichier de génération
            if(line.find("[") == std::string::npos){
                getline(file, line);
                continue;
            }

            index = 0;
            while(line.find("]") == std::string::npos){
                if(line.find("(") != std::string::npos){
                    values[index] = line.std::string::substr(line.find("(") + 1, line.find(")") - line.find("(") - 1);
                    index++;
                }
                getline(file, line);
            }

            // Génération des plateformes de capacités

            SkillPlatform* platform = new SkillPlatform(
                    this,
                    player,
                    std::stoi(values[0]),
                    std::stoi(values[1]),
                    QString::fromStdString(values[2]));

            for(int i = 0; i < 11; i++){
                values[i] = "";
            }

            getline(file, line);
        }

        // Lecture de la partie platform glissante ---------------------------------------------------------------------
        while(line.find("{") == std::string::npos){
            getline(file, line);
        }
        while(line.find("}") == std::string::npos){

            // Vérification s'il n'y a pas d'espaces en trop dans le fichier de génération
            if(line.find("[") == std::string::npos){
                getline(file, line);
                continue;
            }

            index = 0;
            while(line.find("]") == std::string::npos){
                if(line.find("(") != std::string::npos){
                    values[index] = line.std::string::substr(line.find("(") + 1, line.find(")") - line.find("(") - 1);
                    index++;
                }
                getline(file, line);
            }

            // Génération des plateformes glissantes

            SlidingPlatform* platform = new SlidingPlatform(
                    this,
                    player,
                    std::stoi(values[0]),
                    std::stoi(values[1]),
                    std::stoi(values[2]),
                    std::stoi(values[3]),
                    QString::fromStdString(values[4]));

            for(int i = 0; i < 11; i++){
                values[i] = "";
            }

            getline(file, line);
        }

        // Lecture de la partie platform semi passable -----------------------------------------------------------------
        while(line.find("{") == std::string::npos){
            getline(file, line);
        }
        while(line.find("}") == std::string::npos){

            // Vérification s'il n'y a pas d'espaces en trop dans le fichier de génération
            if(line.find("[") == std::string::npos){
                getline(file, line);
                continue;
            }

            index = 0;
            while(line.find("]") == std::string::npos){
                if(line.find("(") != std::string::npos){
                    values[index] = line.std::string::substr(line.find("(") + 1, line.find(")") - line.find("(") - 1);
                    index++;
                }
                getline(file, line);
            }

            // Génération des plateformes semi-passables

            SemiPassablePlatform* platform = new SemiPassablePlatform(
                    this,
                    player,
                    std::stoi(values[0]),
                    std::stoi(values[1]),
                    std::stoi(values[2]),
                    std::stoi(values[3]),
                    QString::fromStdString(values[4]));

            for(int i = 0; i < 11; i++){
                values[i] = "";
            }

            getline(file, line);
        }

        // Lecture de la partie secret room ----------------------------------------------------------------------------
        while(line.find("{") == std::string::npos){
            getline(file, line);
        }
        while(line.find("}") == std::string::npos){

            // Vérification s'il n'y a pas d'espaces en trop dans le fichier de génération
            if(line.find("[") == std::string::npos){
                getline(file, line);
                continue;
            }

            index = 0;
            while(line.find("]") == std::string::npos){
                if(line.find("(") != std::string::npos){
                    values[index] = line.std::string::substr(line.find("(") + 1, line.find(")") - line.find("(") - 1);
                    index++;
                }
                getline(file, line);
            }

            // Génération des salles secrètes

            SecretRoom* secret_room = new SecretRoom(
                    this,
                    player,
                    std::stoi(values[0]),
                    std::stoi(values[1]),
                    std::stoi(values[2]),
                    std::stoi(values[3]),
                    QString::fromStdString(values[4]));

            for(int i = 0; i < 11; i++){
                values[i] = "";
            }

            getline(file, line);
        }

        // Lecture de la partie lave -----------------------------------------------------------------------------------
        while(line.find("{") == std::string::npos){
            getline(file, line);
        }
        while(line.find("}") == std::string::npos){

            // Vérification s'il n'y a pas d'espaces en trop dans le fichier de génération
            if(line.find("[") == std::string::npos){
                getline(file, line);
                continue;
            }

            index = 0;
            while(line.find("]") == std::string::npos){
                if(line.find("(") != std::string::npos){
                    values[index] = line.std::string::substr(line.find("(") + 1, line.find(")") - line.find("(") - 1);
                    index++;
                }
                getline(file, line);
            }

            // Génération des zones de lave

            Lava* secret_room = new Lava(
                    this,
                    player,
                    std::stoi(values[0]),
                    std::stoi(values[1]),
                    std::stoi(values[2]),
                    std::stoi(values[3]),
                    std::stoi(values[4]),
                    std::stoi(values[5]),
                    std::stoi(values[6]));

            for(int i = 0; i < 11; i++){
                values[i] = "";
            }

            getline(file, line);
        }

        // Lecture de la partie boutons --------------------------------------------------------------------------------
        while(line.find("{") == std::string::npos){
            getline(file, line);
        }
        while(line.find("}") == std::string::npos){

            // Vérification s'il n'y a pas d'espaces en trop dans le fichier de génération
            if(line.find("[") == std::string::npos){
                getline(file, line);
                continue;
            }

            index = 0;
            while(line.find("]") == std::string::npos){
                if(line.find("(") != std::string::npos){
                    values[index] = line.std::string::substr(line.find("(") + 1, line.find(")") - line.find("(") - 1);
                    index++;
                }
                getline(file, line);
            }

            // Génération des boutons
            // Gestion des valeurs par défaut
            if(values[2] == ""){
                values[2] = "-1";
            }

            Button* button = new Button(
                    this,
                    player,
                    std::stoi(values[0]),
                    std::stoi(values[1]),
                    std::stoi(values[2]));

            for(int i = 0; i < 11; i++){
                values[i] = "";
            }

            getline(file, line);
        }

        // Lecture de la partie drapeaux -------------------------------------------------------------------------------
        while(line.find("{") == std::string::npos){
            getline(file, line);
        }
        while(line.find("}") == std::string::npos){

            // Vérification s'il n'y a pas d'espaces en trop dans le fichier de génération
            if(line.find("[") == std::string::npos){
                getline(file, line);
                continue;
            }

            index = 0;
            while(line.find("]") == std::string::npos){
                if(line.find("(") != std::string::npos){
                    values[index] = line.std::string::substr(line.find("(") + 1, line.find(")") - line.find("(") - 1);
                    index++;
                }
                getline(file, line);
            }

            // Génération des drapeaux
            // Traduction du booléen
            bool bool1 = false;
            if(values[2] == "true"){
                bool1 = true;
            }

            Flag* flag = new Flag(
                    this,
                    player,
                    std::stoi(values[0]),
                    std::stoi(values[1]),
                    bool1);

            for(int i = 0; i < 11; i++){
                values[i] = "";
            }

            getline(file, line);
        }

        // Lecture de la partie pièces ---------------------------------------------------------------------------------
        while(line.find("{") == std::string::npos){
            getline(file, line);
        }
        while(line.find("}") == std::string::npos){

            // Vérification s'il n'y a pas d'espaces en trop dans le fichier de génération
            if(line.find("[") == std::string::npos){
                getline(file, line);
                continue;
            }

            index = 0;
            while(line.find("]") == std::string::npos){
                if(line.find("(") != std::string::npos){
                    values[index] = line.std::string::substr(line.find("(") + 1, line.find(")") - line.find("(") - 1);
                    index++;
                }
                getline(file, line);
            }

            // Génération des pièces
            Coin* coin = new Coin(
                    this,
                    player,
                    std::stoi(values[0]),
                    std::stoi(values[1]));

            for(int i = 0; i < 11; i++){
                values[i] = "";
            }

            getline(file, line);
        }

        // Lecture de la partie lanceur de flèches ---------------------------------------------------------------------
        while(line.find("{") == std::string::npos){
            getline(file, line);
        }
        while(line.find("}") == std::string::npos){

            // Vérification s'il n'y a pas d'espaces en trop dans le fichier de génération
            if(line.find("[") == std::string::npos){
                getline(file, line);
                continue;
            }

            index = 0;
            while(line.find("]") == std::string::npos){
                if(line.find("(") != std::string::npos){
                    values[index] = line.std::string::substr(line.find("(") + 1, line.find(")") - line.find("(") - 1);
                    index++;
                }
                getline(file, line);
            }

            // Génération des lanceurs de flèches
            ArrowThrower* arrow_thrower = new ArrowThrower(
                    this,
                    player,
                    std::stoi(values[0]),
                    std::stoi(values[1]),
                    QString::fromStdString(values[2]),
                    std::stoi(values[3]),
                    std::stof(values[4]));

            for(int i = 0; i < 11; i++){
                values[i] = "";
            }

            getline(file, line);
        }

        // Lecture de la partie zone de texte --------------------------------------------------------------------------
        while(line.find("{") == std::string::npos){
            getline(file, line);
        }
        while(line.find("}") == std::string::npos){

            // Vérification s'il n'y a pas d'espaces en trop dans le fichier de génération
            if(line.find("[") == std::string::npos){
                getline(file, line);
                continue;
            }
            getline(file, line);

            index = 0;
            for(int i = 0; i < 5; i++){ // Ici impossible de rechercher un "]" car ils peuvent être présent dans les textes
                if(line.find("(") != std::string::npos){
                    values[index] = line.std::string::substr(line.find("(") + 1, line.find(")") - line.find("(") - 1);
                    index++;
                }
                getline(file, line);
            }

            // Génération des zones de texte
            TextArea* textarea = new TextArea(
                    std::stoi(values[0]),
                    std::stoi(values[1]),
                    std::stoi(values[2]),
                    (this->getLanguage() == Language::EN) ? QString::fromStdString(values[3]) : QString::fromStdString(values[4]));

            addItem(textarea);

            for(int i = 0; i < 11; i++){
                values[i] = "";
            }

            getline(file, line);
        }
    }
    file.close();
}

MyScene::~MyScene() {
    qDebug() << this;
    while(platforms.size() > 0){
        delete platforms[0];
    }
    while(event_items.size() > 0){
        delete event_items[0];
    }
    while(secret_rooms.size() > 0){
        delete secret_rooms[0];
    }
    delete player;
    delete pause;
    delete infos;
    if(window->getStackedWidget()->count() >= 2){
        window->getStackedWidget()->setCurrentIndex(1);
        window->getStackedWidget()->removeWidget(player_view);
    }
    qDebug() << "trying to delete player_view";
    delete player_view;
    qDebug() << "\n---------MySceneFullFree---------\n";
}

void MyScene::update() {
    auto views = this->views();
    player->move();
    views[1]->centerOn(player);
    for(auto platform : moving_platforms){
        platform->move();
    }
    for(auto lava : lava_areas){
        lava->move();
    }
    for(auto platform : pushable_platforms){
        platform->update();
    }
    for(auto platform : breakable_platforms){
        platform->update();
    }
    for(auto item : event_items){
        item->update();
    }
    for(auto secret_room : secret_rooms){
        secret_room->collidesWithSecretRoom();
    }
    infos->update();
}

void MyScene::drawBackground(QPainter *painter, const QRectF &rect) {
    Q_UNUSED(rect);
    painter->drawPixmap(QRectF(0,0,background.width(), background.height()), background, sceneRect());
}

void MyScene::gamePause(){
    pause->updatePos();
    addItem(pause);
    pause_menu_displayed = true;
    timer->stop();
}

void MyScene::gameStart(){
    removeItem(pause);
    pause_menu_displayed = false;
    timer->start();
}

void MyScene::keyPressEvent(QKeyEvent* event){
    // Switch
    if((event->key() == Qt::Key_Up || event->key() == Qt::Key_Z) && player->isColliding("down", -2) != nullptr){
        player->jump();
    }
    if(event->key() == Qt::Key_Left || event->key() == Qt::Key_Q){
        pressed_keys[0] = true;
    }
    if(event->key() == Qt::Key_Right || event->key() == Qt::Key_D){
        pressed_keys[1] = true;
    }
    if(event->key() == Qt::Key_A){
        pressed_keys[2] = true;
    }
    if(event->key() == Qt::Key_Escape && !game_stopped){
        if(pause_menu_displayed){
            gameStart();
        }
        else{
            gamePause();
        }
    }
    if(event->key() == Qt::Key_Ampersand && player->getSkillsAvailable(0)){
        player->useSuperJump();
    }
    if(event->key() == Qt::Key_Eacute && player->getSkillsAvailable(1)){
        player->useDash();
    }
    if(event->key() == Qt::Key_QuoteDbl && player->getSkillsAvailable(2)){
        player->useShield();
    }
    if(event->key() == Qt::Key_5){
        qDebug() << "Player (x, y) : (" << player->x() << ", " << player->y() << ")";
    }
}
void MyScene::keyReleaseEvent(QKeyEvent* event){
    // Switch
    if(event->key() == Qt::Key_Left || event->key() == Qt::Key_Q){
        pressed_keys[0] = false;
    }
    if(event->key() == Qt::Key_Right || event->key() == Qt::Key_D){
        pressed_keys[1] = false;
    }
    if(event->key() == Qt::Key_A){
        pressed_keys[2] = false;
    }
}

bool MyScene::getPressedKeys(unsigned short int index) {
    if(index > 3 || index < 0){
        qDebug() << "Index out of range";
        return false;
    }
    return pressed_keys[index];
}

QVector<Platform*>* MyScene::getPlatforms(){
    return &platforms;
}

QVector<MovingPlatform*>* MyScene::getMovingPlatforms(){
    return &moving_platforms;
}

QVector<PushablePlatform*>* MyScene::getPushablePlatforms(){
    return &pushable_platforms;
}

QVector<BreakablePlatform*>* MyScene::getBreakablePlatforms(){
    return &breakable_platforms;
}

QVector<SkillPlatform*>* MyScene::getSkillPlatforms(){
    return &skill_platform;
}

QVector<SlidingPlatform*>* MyScene::getSlidingPlatforms(){
    return &sliding_platforms;
}

QVector<SemiPassablePlatform*>* MyScene::getSemiPassablePlatforms(){
    return &semi_passable_platforms;
}

QVector<Lava*>* MyScene::getLavaAreas(){
    return &lava_areas;
}

QVector<Button*>* MyScene::getButtons(){
    return &buttons;
}

QVector<EventItem*>* MyScene::getEventItems() {
    return &event_items;
}

QVector<SecretRoom*>* MyScene::getSecretRooms() {
    return &secret_rooms;
}

MainWindow* MyScene::getMainWindow(){
    return window;
}

void MyScene::pushPlatform(Platform *platform) {
    platforms.push_back(platform);
}

void MyScene::pushMovingPlatform(MovingPlatform *platform) {
    moving_platforms.push_back(platform);
}

void MyScene::pushPushablePlatform(PushablePlatform *platform) {
    pushable_platforms.push_back(platform);
}

void MyScene::pushBreakablePlatform(BreakablePlatform* platform){
    breakable_platforms.push_back(platform);
}

void MyScene::pushSkillPlatform(SkillPlatform* platform){
    skill_platform.push_back(platform);
}

void MyScene::pushSlidingPlatform(SlidingPlatform* platform){
    sliding_platforms.push_back(platform);
}

void MyScene::pushSemiPassablePlatform(SemiPassablePlatform* platform){
    semi_passable_platforms.push_back(platform);
}

void MyScene::pushLavaArea(Lava *lava){
    lava_areas.push_back(lava);
}

void MyScene::pushButton(Button* button){
    buttons.push_back(button);
}

void MyScene::pushEventItem(EventItem* item){
    event_items.push_back(item);
}

void MyScene::pushSecretRoom(SecretRoom* secret_room){
    secret_rooms.push_back(secret_room);
}

void MyScene::pushFlag(Flag* flag){
    flags.push_back(flag);
}

void MyScene::restart() {
    player->setSpawnPoint(spawn_x, spawn_y);
    player->death(); // Le replace, le remet gros et enlève ses skills et remet toutes les plateformes
    for(auto flag : flags){
        flag->toFullyInitialState();
    }
    deaths = 0;
    game_stopped = false;
    infos->toZero();
    timer->start();
}

int MyScene::getDeaths(){
    return deaths;
}

int MyScene::getCoinsCount(){
    return coins_count;
}

int MyScene::getTotalCoins(){
    return total_coins;
}

int MyScene::getLevel(){
    return level;
}

Infos* MyScene::getInfos(){
    return infos;
}

Language MyScene::getLanguage() {
    return language;
}

void MyScene::setDeaths(int n){
    deaths = n;
}

void MyScene::setCoinsCount(int n){
    coins_count = n;
}

void MyScene::setTotalCoins(int n){
    total_coins = n;
}

void MyScene::levelEnd(){
    game_stopped = true;
    timer->stop();
    LevelEnd* level_end_display = new LevelEnd(this, player, infos, menu);
    addItem(level_end_display);
}

void MyScene::toInitialState(){
    for(auto platform : platforms){
        platform->toInitialState();
    }
    for(auto eventitem : event_items){
        eventitem->toInitialState();
    }
    coins_count = 0;
    if(pause_menu_displayed){
        gameStart();
    }
}

void MyScene::exit(){
    deleteLater();
}