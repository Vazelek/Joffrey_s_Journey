#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    player_data = new PlayerData; // Read player_data file

    menu = new Menu(this);
    Login* login = new Login(this);
    stacked_widget = new QStackedWidget;
    stacked_widget->addWidget(login);
    stacked_widget->addWidget(menu);
    stacked_widget->setCurrentIndex(0); // First print the login window
    setCentralWidget(stacked_widget);
    scene = nullptr;

    setWindowTitle("Joffrey's Journey");
    setFixedSize(1200, 720);

}

MainWindow::~MainWindow(){

}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, "Fermer le jeu",
                                                                tr("Are you sure?\n"),
                                                                QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
                                                                QMessageBox::Yes);
    if (resBtn != QMessageBox::Yes) {
        event->ignore();
    } else {
        event->accept();
        qDebug() << this;
        if(stacked_widget->currentIndex() == 2){
            delete scene;
        }
        delete stacked_widget;
        qDebug() << "stacked_widget";
        delete player_data;
        qDebug() << "player_data";
    }
}

QStackedWidget* MainWindow::getStackedWidget(){
    return stacked_widget;
}

PlayerData* MainWindow::getPlayerData(){
    return player_data;
}

Menu* MainWindow::getMenu(){
    return menu;
}

void MainWindow::setMyScene(MyScene* new_scene){
    scene = new_scene;
}