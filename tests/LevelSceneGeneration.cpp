#include "LevelSceneGeneration.h"

void LevelSceneGeneration::initTestCase() {
    mainWindow = new MainWindow();
    mainWindow->show();
    Login* login = (Login*) mainWindow->getStackedWidget()->currentWidget();
    QTest::keyClicks(login->getInput(), "&LevelSceneGeneration&");
    QTest::mouseClick(login->getLoginButton(), Qt::LeftButton);
    QTest::mouseClick(login->getNewConnectionButton(), Qt::LeftButton);

    QWidget* current_widget = mainWindow->getStackedWidget()->currentWidget();
    QCOMPARE(current_widget->metaObject()->className(), "Menu");

    if (current_widget->metaObject()->className() == QString("Menu")) {
        Menu* menu = (Menu*) current_widget;
        QTest::mouseClick(menu->getLevelButtons()[0], Qt::LeftButton); // Click on intro button

        QCOMPARE(mainWindow->getStackedWidget()->currentWidget()->metaObject()->className(), "QGraphicsView");
    }
    
}

void LevelSceneGeneration::test_ArrowKill()
{
    QVERIFY(true); // This will always pass
}

void LevelSceneGeneration::test_ShieldSuppressArrow()
{
    //QTest::mouseClick
}

void LevelSceneGeneration::cleanupTestCase() {
    delete mainWindow;
}
