#ifndef LEVELCHOICEBUTTON_H
#define LEVELCHOICEBUTTON_H

#include <QPushButton>
#include <QWidget>
#include "Menu.h"

class Menu;

class LevelChoiceButton : public QPushButton{
    Q_OBJECT

private:
    int number;
    Menu* menu;
    bool locked;

public:
    LevelChoiceButton(int number, Menu* menu, QWidget* parent = nullptr);
    ~LevelChoiceButton();
    void setUnlocked();

public slots:
    void ButtonClick();
};

#endif