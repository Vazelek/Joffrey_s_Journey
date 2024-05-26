#include "Pause.h"

Pause::Pause(MyScene* scene, Player* player, QGraphicsItem* parent) : QGraphicsProxyWidget(parent), scene(scene), player(player){
    QWidget* mainWidget = new QWidget();
    setWidget(mainWidget);

    mainWidget->setAttribute(Qt::WA_TranslucentBackground, true);

    width = scene->getMainWindow()->window()->size().width() / 3;
    height = 150;

    QLabel* text = new QLabel();
    text->setText("Pause");
    text->setStyleSheet("background-color: rgba(0, 0, 0, 0.35);"
                        "font-size: 40px;");
    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(text);
    mainWidget->setLayout(layout);

    text->setAlignment(Qt::AlignCenter);

    QHBoxLayout* h_layout = new QHBoxLayout;

    QPushButton* restart = new QPushButton((MainWindow::isInEnglish) ? "Restart" : "Redémarer");
    h_layout->addWidget(restart);
    QPushButton* exit = new QPushButton((MainWindow::isInEnglish) ? "Go back to menu" : "Quitter vers le menu");
    h_layout->addWidget(exit);
    QPushButton* kill = new QPushButton("Suicide");
    h_layout->addWidget(kill);

    QObject::connect(restart, SIGNAL(clicked()), this, SLOT(restart()));
    QObject::connect(exit, SIGNAL(clicked()), this, SLOT(exit()));
    QObject::connect(kill, SIGNAL(clicked()), this, SLOT(kill()));

    QWidget* buttons_widget = new QWidget;
    layout->addWidget(buttons_widget);
    buttons_widget->setLayout(h_layout);

    setMaximumSize(width, height);
    resize(width, height);
}

Pause::~Pause(){
    // qDebug() << this;
}

void Pause::updatePos(){
    int coord_x = player->x() + player->getWidth() / 2 - (width / 2);
    int coord_y = player->y() + player->getHeight() / 2 - (height / 2);
    float window_width = scene->getMainWindow()->window()->size().width() / 3;
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

void Pause::exit(){
    scene->exit();
}

void Pause::restart(){
    scene->restart();
}

void Pause::kill(){
    player->death();
    scene->gameStart();
}
