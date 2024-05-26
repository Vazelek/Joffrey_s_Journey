#include "PlayerInteractionsTests.h"
#include "TestsGlobal.h"

void PlayerInteractionsTests::initTestCase() {
    mainWindow = new MainWindow();
    mainWindow->show();
    Login* login = (Login*) mainWindow->getStackedWidget()->currentWidget();
    QTest::keyClicks(login->getInput(), "&PlayerInteractionsTests&");
    QTest::mouseClick(login->getLoginButton(), Qt::LeftButton);
    QTest::mouseClick(login->getNewConnectionButton(), Qt::LeftButton);

    QWidget* current_widget = mainWindow->getStackedWidget()->currentWidget();
    QCOMPARE(current_widget->metaObject()->className(), "Menu");

    Menu* menu = (Menu*) current_widget;
    menu->startLevel(-1);

    scene = menu->getScene();
    QVERIFY(scene != nullptr);

    QCOMPARE(scene->getLevel(), -1);

    player = scene->getPlayer();

    QVERIFY(player != nullptr);
}

void PlayerInteractionsTests::test_ArrowKill()
{
    if (player == nullptr) {
        QSKIP("Player is null");
        return;
    }

    QCOMPARE(scene->getDeaths(), 0);
    
    player->setX(920); // Teleport under an arrow thrower

    simulate(2, scene); // Simulate 2 seconds of gameplay

    QCOMPARE(scene->getDeaths(), 1);
}

void PlayerInteractionsTests::test_LevelRespawnPoint() {
    if (scene->getDeaths() != 1 || player == nullptr) {
        QSKIP("Previous failed test is required");
        return;
    }

    // Based on the level_test.txt
    QCOMPARE(player->x(), 0);
    QCOMPARE(player->y(), 152);
}

void PlayerInteractionsTests::test_ActivateCheckpoint()
{
    if (player == nullptr) {
        QSKIP("Player is null");
        return;
    }

    player->setX(860); // Teleport the player at the checkpoint flag position

    simulate(1, scene);

    QCOMPARE(player->getSpawnX(), 860);
    QCOMPARE(player->getSpawnY(), 152);
}

void PlayerInteractionsTests::test_ReturnToCheckpointOnDeath()
{
    if (player == nullptr) {
        QSKIP("Player is null");
        return;
    }

    QCOMPARE(scene->getDeaths(), 1);
    
    player->setX(920); // Teleport under an arrow thrower

    simulate(2, scene); // Simulate 2 seconds of gameplay

    QCOMPARE(scene->getDeaths(), 2);

    QCOMPARE(player->x(), 860);
    QCOMPARE(player->y(), 152);
}

void PlayerInteractionsTests::test_PowerObtention()
{
    if (player == nullptr) {
        QSKIP("Player is null");
        return;
    }

    QCOMPARE(player->getSkillsAvailable(0), false);
    QCOMPARE(player->getSkillsAvailable(1), false);
    QCOMPARE(player->getSkillsAvailable(2), false);

    player->setX(380);
    player->setY(100);

    simulate(1, scene);

    QCOMPARE(player->getSkillsAvailable(0), true);
    QCOMPARE(player->getSkillsAvailable(1), false);
    QCOMPARE(player->getSkillsAvailable(2), false);

    player->setX(428);
    player->setY(100);

    simulate(1, scene);

    QCOMPARE(player->getSkillsAvailable(0), true);
    QCOMPARE(player->getSkillsAvailable(1), false);
    QCOMPARE(player->getSkillsAvailable(2), true);

    player->setX(476);
    player->setY(100);

    simulate(1, scene);

    QCOMPARE(player->getSkillsAvailable(0), true);
    QCOMPARE(player->getSkillsAvailable(1), true);
    QCOMPARE(player->getSkillsAvailable(2), true);
}

void PlayerInteractionsTests::test_PowerActivation()
{
    if (player == nullptr) {
        QSKIP("Player is null");
        return;
    }

    QCOMPARE(player->getSkillsAvailable(0), true);
    QCOMPARE(player->getSkillsAvailable(1), true);
    QCOMPARE(player->getSkillsAvailable(2), true);

    scene->keyPressEvent(new QKeyEvent(QKeyEvent::KeyPress, Qt::Key_Ampersand, 0));
    QCOMPARE(player->getNextJumpSpeed(), 13);

    QCOMPARE(player->getSkillsAvailable(0), false);
    QCOMPARE(player->getSkillsAvailable(1), true);
    QCOMPARE(player->getSkillsAvailable(2), true);

    scene->keyPressEvent(new QKeyEvent(QKeyEvent::KeyPress, Qt::Key_Eacute, 0));

    QCOMPARE(player->getSkillsAvailable(0), false);
    QCOMPARE(player->getSkillsAvailable(1), true); // Does nothing because player isn't going in any direction
    QCOMPARE(player->getSkillsAvailable(2), true);

    scene->keyPressEvent(new QKeyEvent(QKeyEvent::KeyPress, Qt::Key_D, 0)); // Go right
    scene->keyPressEvent(new QKeyEvent(QKeyEvent::KeyPress, Qt::Key_Eacute, 0));
    scene->keyReleaseEvent(new QKeyEvent(QKeyEvent::KeyRelease, Qt::Key_D, 0));

    QCOMPARE(player->getSkillsAvailable(0), false);
    QCOMPARE(player->getSkillsAvailable(1), false); // Does nothing because player isn't going in any direction
    QCOMPARE(player->getSkillsAvailable(2), true);

    scene->keyPressEvent(new QKeyEvent(QKeyEvent::KeyPress, Qt::Key_QuoteDbl, 0));
    QCOMPARE(player->hasShield(), true);

    QCOMPARE(player->getSkillsAvailable(0), false);
    QCOMPARE(player->getSkillsAvailable(1), false);
    QCOMPARE(player->getSkillsAvailable(2), false);
}

void PlayerInteractionsTests::test_ShieldProtectPlayer()
{
    if (player == nullptr || !player->hasShield() || scene->getDeaths() != 2) {
        QSKIP("Previous failed test is required");
        return;
    }

    Arrow* arrow = new Arrow(scene, player, player->x(), player->y() - 30, "down", 100000);

    QVERIFY(arrow != nullptr);

    simulate(2, scene);

    QCOMPARE(player->hasShield(), false);
    QCOMPARE(scene->getDeaths(), 2);
}

void PlayerInteractionsTests::cleanupTestCase() {
    delete mainWindow;
}

// QTEST_MAIN(PlayerInteractionsTests)
// #include "TestExample.moc"
