#include "LevelSceneGeneration.h"

void LevelSceneGeneration::initTestCase() {
    scene = nullptr;
    test_elements_exists_passed = false;
    mainWindow = new MainWindow();
    mainWindow->show();
    Login* login = (Login*) mainWindow->getStackedWidget()->currentWidget();
    QTest::keyClicks(login->getInput(), "&LevelSceneGeneration&");
    QTest::mouseClick(login->getLoginButton(), Qt::LeftButton);
    QTest::mouseClick(login->getNewConnectionButton(), Qt::LeftButton);

    QWidget* current_widget = mainWindow->getStackedWidget()->currentWidget();
    QCOMPARE(current_widget->metaObject()->className(), "Menu");    
}

void LevelSceneGeneration::test_SceneWellGenerated() {
    QWidget* current_widget = mainWindow->getStackedWidget()->currentWidget();
    if (current_widget->metaObject()->className() != QString("Menu")) {
        QSKIP("Previous failed test is required");
        return;
    }

    Menu* menu = (Menu*) current_widget;
    menu->startLevel(-1); // Test level

    current_widget = mainWindow->getStackedWidget()->currentWidget();
    QCOMPARE(current_widget->metaObject()->className(), "QGraphicsView");

    scene = menu->getScene();
    QVERIFY(scene != nullptr);

    QCOMPARE(scene->getLevel(), -1);
}

void LevelSceneGeneration::test_ElementsExists() {
    if (scene == nullptr) {
        QSKIP("Previous failed test is required");
        return;
    }

    QVERIFY(scene->getBreakablePlatforms() != nullptr);
    QVERIFY(scene->getButtons() != nullptr);
    QVERIFY(scene->getEventItems() != nullptr);
    QVERIFY(scene->getInfos() != nullptr);
    QVERIFY(scene->getLavaAreas() != nullptr);
    QVERIFY(scene->getMovingPlatforms() != nullptr);
    QVERIFY(scene->getPlatforms() != nullptr);
    QVERIFY(scene->getPushablePlatforms() != nullptr);
    QVERIFY(scene->getSecretRooms() != nullptr);
    QVERIFY(scene->getSemiPassablePlatforms() != nullptr);
    QVERIFY(scene->getSkillPlatforms() != nullptr);
    QVERIFY(scene->getPlayer() != nullptr);

    QCOMPARE(scene->getTotalCoins(), 1);
    QCOMPARE(scene->getCoinsCount(), 0);
    QCOMPARE(scene->getDeaths(), 0);

    // Based on level_test.txt data file
    QCOMPARE(scene->getBreakablePlatforms()->length(), 1);
    QCOMPARE(scene->getButtons()->length(), 1);
    QCOMPARE(scene->getLavaAreas()->length(), 0);
    QCOMPARE(scene->getMovingPlatforms()->length(), 2);
    QCOMPARE(scene->getPlatforms()->length(), 14);
    QCOMPARE(scene->getPushablePlatforms()->length(), 1);
    QCOMPARE(scene->getSecretRooms()->length(), 1);
    QCOMPARE(scene->getSemiPassablePlatforms()->length(), 1);
    QCOMPARE(scene->getSkillPlatforms()->length(), 5);

    test_elements_exists_passed = true;
}

void LevelSceneGeneration::test_PlayerDataInitialisation() {
    if (!test_elements_exists_passed || scene == nullptr) {
        QSKIP("Previous failed test is required");
        return;
    }

    player = scene->getPlayer();

    // Default values for a newly created player (tall, not moving)
    QCOMPARE(player->getBaseVertSpeed(), 9);
    QCOMPARE(player->getHorizontalSpeed(), 0);
    QCOMPARE(player->getHeight(), 48);
    QCOMPARE(player->getWidth(), 26);
    QCOMPARE(player->getNextJumpSpeed(), 0);
    QCOMPARE(player->getSkillsAvailable(0), false);
    QCOMPARE(player->getSkillsAvailable(1), false);
    QCOMPARE(player->getSkillsAvailable(2), false);
}

void LevelSceneGeneration::test_ElementsCoordinates() {
    if (player == nullptr) {
        QSKIP("Previous failed test is required");
        return;
    }

    // Based on the level_test.txt
    QCOMPARE(player->x(), 0);
    QCOMPARE(player->y(), 152);

    QCOMPARE(scene->getButtons()->at(0)->getX(), 110);
    QCOMPARE(scene->getButtons()->at(0)->getY(), 184);

    QCOMPARE(scene->getMovingPlatforms()->at(0)->getX(), 64);

    QCOMPARE(scene->getPushablePlatforms()->at(0)->getX(), 224);
    QCOMPARE(scene->getPushablePlatforms()->at(0)->getY(), 150);

    QCOMPARE(scene->getSecretRooms()->at(0)->getX(), 780);
    QCOMPARE(scene->getSecretRooms()->at(0)->getY(), 120);

    QCOMPARE(scene->getSemiPassablePlatforms()->at(0)->getX(), 700);
    QCOMPARE(scene->getSemiPassablePlatforms()->at(0)->getY(), 150);

    QCOMPARE(scene->getSlidingPlatforms()->at(0)->getX(), 620);
    QCOMPARE(scene->getSlidingPlatforms()->at(0)->getY(), 184);

    QCOMPARE(scene->getSkillPlatforms()->at(0)->getX(), 380);
    QCOMPARE(scene->getSkillPlatforms()->at(0)->getY(), 184);

    QCOMPARE(scene->getSkillPlatforms()->at(1)->getX(), 428);
    QCOMPARE(scene->getSkillPlatforms()->at(1)->getY(), 184);

    QCOMPARE(scene->getSkillPlatforms()->at(2)->getX(), 476);
    QCOMPARE(scene->getSkillPlatforms()->at(2)->getY(), 184);

    QCOMPARE(scene->getSkillPlatforms()->at(3)->getX(), 524);
    QCOMPARE(scene->getSkillPlatforms()->at(3)->getY(), 184);

    QCOMPARE(scene->getSkillPlatforms()->at(4)->getX(), 572);
    QCOMPARE(scene->getSkillPlatforms()->at(4)->getY(), 184);
}

void LevelSceneGeneration::test_SceneWellClosed() {
    if (scene == nullptr) {
        QSKIP("Scene is null");
        return;
    }

    delete scene;

    QCOMPARE(mainWindow->getStackedWidget()->count(), 2);
    QCOMPARE(
        mainWindow->getStackedWidget()->currentWidget()->metaObject()->className(),
        "Menu"
    );
}

void LevelSceneGeneration::cleanupTestCase() {
    delete mainWindow;
}
