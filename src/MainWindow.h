#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QMenuBar>
#include <QAction>
#include <QMessageBox>
#include <QGraphicsView>
#include <QCloseEvent>
#include <QStackedWidget>

#include "MyScene.h"
#include "Menu.h"
#include "Login.h"
#include "PlayerData.h"

class Menu;

class MainWindow : public QMainWindow {
    Q_OBJECT

private :
    MyScene* scene;
    QStackedWidget* stacked_widget;
    PlayerData* player_data;
    Menu* menu;

public:
    MainWindow(QWidget* parent = nullptr);
    virtual ~MainWindow();
    void closeEvent(QCloseEvent *event);
    QStackedWidget* getStackedWidget();
    PlayerData* getPlayerData();
    Menu* getMenu();
    void setMyScene(MyScene* new_scene);
};


#endif //MAINWINDOW_H
