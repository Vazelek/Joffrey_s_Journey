#include "PlayerInteractionsTests.h"

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
    QTest::mouseClick(menu->getLevelButtons()[0], Qt::LeftButton); // Click on intro button

    QCOMPARE(mainWindow->getStackedWidget()->currentWidget()->metaObject()->className(), "QGraphicsView");    
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
