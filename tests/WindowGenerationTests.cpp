#include "WindowGenerationTests.h"

void WindowGenerationTests::initTestCase() {
    mainWindow = new MainWindow();
    mainWindow->show();
}

void WindowGenerationTests::test_WindowWellGenerated()
{
    QVERIFY(mainWindow != nullptr);
    QCOMPARE(mainWindow->windowTitle(), QString("Joffrey's Journey"));
}

void WindowGenerationTests::test_ShieldSuppressArrow()
{
    //QTest::mouseClick
}

void WindowGenerationTests::cleanupTestCase() {
    delete mainWindow;
}
