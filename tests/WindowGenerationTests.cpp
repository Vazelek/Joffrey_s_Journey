#include "WindowGenerationTests.h"

void WindowGenerationTests::initTestCase() {
    current_widget = nullptr;
    login = nullptr;
    menu = nullptr;

    mainWindow = new MainWindow();
    mainWindow->show();
}

void WindowGenerationTests::test_WindowWellGenerated()
{
    QVERIFY(mainWindow != nullptr);
    QCOMPARE(mainWindow->windowTitle(), "Joffrey's Journey");
}

// Login page
void WindowGenerationTests::test_WindowCreatedOnLoginPage() {
    current_widget = mainWindow->getStackedWidget()->currentWidget();
    QCOMPARE(current_widget->metaObject()->className(), "Login");
}

void WindowGenerationTests::test_UsernameInputField() {
    if (current_widget->metaObject()->className() != QString("Login")) {
        QSKIP("Previous failed test is required");
        return;
    }

    login = (Login*) current_widget;
    QLineEdit* input = login->getInput();

    QVERIFY(input != nullptr);

    QTest::keyClicks(input, "&TestUsername&");
    QCOMPARE(input->text(), "&TestUsername&");
}

void WindowGenerationTests::test_NewConnectionMessageOnConnectButtonClick() {
    if (login == nullptr) {
        QSKIP("Previous failed test is required");
        return;
    }

    QTest::mouseClick(login->getLoginButton(), Qt::LeftButton);
    QLabel* infos = login->getInfosLabel();

    QVERIFY(infos != nullptr);

    QCOMPARE(
        infos->text(),
        "You are about to log in as \"&TestUsername&\"\nYour scores and records will be saved under this nickname"
    );
}

// Menu page
void WindowGenerationTests::test_WindowSwitchToMenuOnNewConnectionButtonClicked() {
    if (login == nullptr) {
        QSKIP("Previous failed test is required");
        return;
    }

    QTest::mouseClick(login->getNewConnectionButton(), Qt::LeftButton);
    current_widget = mainWindow->getStackedWidget()->currentWidget();
    QCOMPARE(current_widget->metaObject()->className(), "Menu");
}

void WindowGenerationTests::test_RightUsernameOnMenuPage() {
    if (current_widget->metaObject()->className() != QString("Menu")) {
        QSKIP("Not in the menu window");
        return;
    }

    menu = (Menu*) current_widget;
    QVERIFY(menu != nullptr);
    
    QLabel* menu_label = menu->getMenuLabel();

    QVERIFY(menu_label != nullptr);

    QCOMPARE(
        menu_label->text(),
        "You are logged in as \"&TestUsername&\"\nYour scores and records will be saved under this nickname"
    );
}

void WindowGenerationTests::test_NewUserLevelOneDisabled() {
    if (menu == nullptr) {
        QSKIP("Previous failed test is required");
        return;
    }

    level_buttons = menu->getLevelButtons();
    QCOMPARE(level_buttons.length(), 7);

    // Click on level 1 button
    QTest::mouseClick(level_buttons[1], Qt::LeftButton);

    // No page switch means the level 1 button is well locked
    QCOMPARE(mainWindow->getStackedWidget()->currentWidget()->metaObject()->className(), "Menu");
}

void WindowGenerationTests::test_NewUserIntroductionEnabled() {
    if (
        menu == nullptr ||
        level_buttons.length() != 7 ||
        mainWindow->getStackedWidget()->currentWidget()->metaObject()->className() != QString("Menu")
    ) {
        QSKIP("Previous failed test is required");
        return;
    }
    
    // Click on intro button
    QTest::mouseClick(level_buttons[0], Qt::LeftButton);

    // Page switch means the intro button is well unlocked
    QCOMPARE(mainWindow->getStackedWidget()->currentWidget()->metaObject()->className(), "QGraphicsView");
}

void WindowGenerationTests::cleanupTestCase() {
    delete mainWindow;
}
