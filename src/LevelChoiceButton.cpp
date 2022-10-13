#include "LevelChoiceButton.h"

LevelChoiceButton::LevelChoiceButton(int number, Menu* menu, QWidget* parent): QPushButton(parent), number(number), menu(menu){
    locked = true;
    setText("Niveau " + QString::number(number));
    if(number == 0){
        setText("Introduction");
    }
    if(number > 1){
        setText("Coming soon");
        return;
    }
    QObject::connect(this, SIGNAL(clicked()), this, SLOT(ButtonClick()));
}

LevelChoiceButton::~LevelChoiceButton(){

}

void LevelChoiceButton::ButtonClick() {
    if(!locked){
        menu->startLevel(number);
    }
}

void LevelChoiceButton::setUnlocked(){
    locked = false;
}