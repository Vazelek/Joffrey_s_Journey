#ifndef WINDOWGENERATIONTESTS_H
#define WINDOWGENERATIONTESTS_H

#include <QtTest/QtTest>
#include <QObject>
#include "MainWindow.h"
#include "Login.h"

class WindowGenerationTests : public QObject
{
    Q_OBJECT

private:
    MainWindow* mainWindow;
    QWidget* current_widget;
    Login* login;
    Menu* menu;
    QVector<LevelChoiceButton*> level_buttons;

private slots:
    // Init
    void initTestCase();
    void test_WindowWellGenerated();

    // Login page
    void test_WindowCreatedOnLoginPage();
    void test_UsernameInputField();
    void test_NewConnectionMessageOnConnectButtonClick();

    // Menu page
    void test_WindowSwitchToMenuOnNewConnectionButtonClicked();
    void test_RightUsernameOnMenuPage();
    void test_NewUserLevelOneDisabled();
    void test_NewUserIntroductionEnabled();

    // Cleanup
    void cleanupTestCase();
};

#endif // WINDOWGENERATIONTESTS_H
