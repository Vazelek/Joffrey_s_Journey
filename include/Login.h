#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QTimer>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLayoutItem>
#include <QPushButton>
#include <QObject>
#include <QString>
#include <QDebug>
#include <QLineEdit>
#include <QLabel>
#include "MainWindow.h"
#include "LevelChoiceButton.h"
#include "PlayerData.h"

class Login : public QWidget{
    Q_OBJECT

private:
    MainWindow* main_window;
    QVBoxLayout* vlayout;
    QLineEdit* input;
    QLabel* infos;
    QPushButton* login_btn;
    QPushButton* new_connection;
    bool new_connection_button_displayed;

public:
    Login(MainWindow* main_window, QWidget* parent = nullptr);
    ~Login();
    QLineEdit* getInput();
    QPushButton* getLoginButton();
    QLabel* getInfosLabel();
    QPushButton* getNewConnectionButton();

public slots:
    void buttonClick();
    void newConnection();
};

#endif