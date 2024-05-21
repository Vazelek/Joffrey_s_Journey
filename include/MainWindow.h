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

#include "include/MyScene.h"
#include "include/Menu.h"
#include "include/Login.h"
#include "include/PlayerData.h"

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
    static bool isInEnglish();
    static bool is_in_english;
    void setEnglish();
    void setFrench();
};


#endif //MAINWINDOW_H
