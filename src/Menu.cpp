#include "Menu.h"

Menu::Menu(MainWindow* main_window, QWidget* parent) : QWidget(parent), main_window(main_window), level_number(0){

    QVBoxLayout* vlayout = new QVBoxLayout(this);

    connect_name = new QLabel;
    connect_name->setText(
        (MainWindow::isInEnglish()) ?
            "You are logged in as \""  + main_window->getPlayerData()->getCurrentPlayer() + "\"\nYour scores and records will be saved under this nickname": 
            "Vous êtes connecté en tant que \"" + main_window->getPlayerData()->getCurrentPlayer() + "\"\nVos scores et records seront enregistrés sous ce nom"
    );
    connect_name->setAlignment(Qt::AlignCenter);
    connect_name->setMaximumHeight(80);

    vlayout->addWidget(connect_name);

    QPushButton* disconnect_button = new QPushButton;
    disconnect_button->setText((MainWindow::isInEnglish()) ? "Log out" : "Déconnexion");
    QObject::connect(disconnect_button, SIGNAL(clicked()), this, SLOT(signOut()));
    vlayout->addWidget(disconnect_button);

    QWidget* buttons_widget = new QWidget;
    QVBoxLayout* btn_layout = new QVBoxLayout;
    btn_layout->setMargin(70);
    buttons_widget->setLayout(btn_layout);
    vlayout->addWidget(buttons_widget);

    LevelChoiceButton* intro = new LevelChoiceButton(0, this);
    btn_layout->addWidget(intro);
    buttons.push_back(intro);

    for(int i = 0; i < 3; i++){
        QWidget* widget = new QWidget();
        btn_layout->addWidget(widget);
        QHBoxLayout* hlayout = new QHBoxLayout(widget);
        hlayout->setSpacing(50);
        for(int j = 0; j < 2; j++){
            LevelChoiceButton* button = new LevelChoiceButton(j + 1 + i * 2, this);
            hlayout->addWidget(button);
            buttons.push_back(button);
        }
    }
    mainView = nullptr;
}

Menu::~Menu(){
    qDebug() << this;
    if(mainView != nullptr){
        delete mainView;
    }
    qDebug() << "View";
}

void Menu::startLevel(int number){
    if(mainView != nullptr){
        delete mainView;
    }
    if(number != 0){
        number = 1;
    }

    player_view = new QGraphicsView();

    scene = new MyScene(main_window, player_view, this, number);
    main_window->setMyScene(scene);

    mainView = new QGraphicsView;
    mainView->setScene(scene);

    // A delete
//     mainView->setWindowTitle("Scene");
//     mainView->resize(2000, 1000);
//     mainView->show();
    // A delete

    player_view->setScene(scene);
    player_view->scale(3, 3);
    player_view->setFixedSize(1200, 720);
    player_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    player_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    main_window->getStackedWidget()->addWidget(player_view);
    main_window->getStackedWidget()->setCurrentIndex(main_window->getStackedWidget()->count() - 1);
}

void Menu::startLater(){
    startLevel(level_number);
    delete timer;
}

void Menu::signOut(){
    main_window->getStackedWidget()->setCurrentIndex(0);
}

void Menu::reloadConnectName(){
    connect_name->setText(
        (MainWindow::isInEnglish()) ?
            "You are logged in as \""  + main_window->getPlayerData()->getCurrentPlayer() + "\"\nYour scores and records will be saved under this nickname": 
            "Vous êtes connecté en tant que \"" + main_window->getPlayerData()->getCurrentPlayer() + "\"\nVos scores et records seront enregistrés sous ce nom"
    );
    updateLockedLevels();
}

void Menu::updateLockedLevels(){
    int level = 0;
    for(auto level_data : *(main_window->getPlayerData()->getPlayerData())){
        QStringList saved_stars = (*level_data)["star"].split(QLatin1Char('/'));
        int count_obtained_stars = 0;
        int count_saved_stars = 0;
        for(int i = 0; i < 4; i++){
            count_saved_stars += saved_stars[i].toInt();
        }
        if(count_saved_stars != 0 && buttons.length() != level + 1){ // If we're not on the last level
            buttons[level + 1]->setUnlocked();
        }
        if(level == 0){ // Intro
            buttons[0]->setUnlocked();
        }
        level++;
    }
}

QLabel* Menu::getMenuLabel() {
    return connect_name;
}

QVector<LevelChoiceButton*> Menu::getLevelButtons(){
    return buttons;
}