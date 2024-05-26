#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include <QTimer>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLayoutItem>
#include <QPushButton>
#include <QObject>
#include <QString>
#include <QDebug>
#include <QVector>
#include "MainWindow.h"
#include "LevelChoiceButton.h"

class MainWindow;
class MyScene;
class LevelChoiceButton;

class Menu : public QWidget{
    Q_OBJECT

private:
    QLabel* connect_name;
    QTimer* timer;
    MainWindow* main_window;
    MyScene* scene;
    QGraphicsView* mainView;
    QGraphicsView* player_view;
    QVector<LevelChoiceButton*> buttons;
    int level_number;

public:
    Menu(MainWindow* main_window, QWidget* parent = nullptr);
    ~Menu();
    void startLevel(int number);
    void reloadConnectName();
    void updateLockedLevels();
    void unlockBtn(int level);
    QLabel* getMenuLabel();
    QVector<LevelChoiceButton*> getLevelButtons();
    MyScene* getScene();

public slots:
    void startLater();
    void signOut();
};

#endif