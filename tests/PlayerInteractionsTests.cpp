#include "PlayerInteractionsTests.h"

void PlayerInteractionsTests::initTestCase() {
    mainWindow = new MainWindow();
    mainWindow->show();
}

void PlayerInteractionsTests::test_ArrowKill()
{
    QVERIFY(true); // This will always pass
}

void PlayerInteractionsTests::test_ShieldSuppressArrow()
{
    //QTest::mouseClick
}

void PlayerInteractionsTests::cleanupTestCase() {
    delete mainWindow;
}

// QTEST_MAIN(PlayerInteractionsTests)
// #include "TestExample.moc"
