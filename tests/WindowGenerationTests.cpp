#include "WindowGenerationTests.h"

void WindowGenerationTests::initTestCase() {
    stacked_widgets = nullptr;
    login = nullptr;

    mainWindow = new MainWindow();
    mainWindow->show();
}

void WindowGenerationTests::test_WindowWellGenerated()
{
    QVERIFY(mainWindow != nullptr);
    QCOMPARE(mainWindow->windowTitle(), QString("Joffrey's Journey"));
}

void WindowGenerationTests::test_WindowCreatedOnLoginPage() {
    stacked_widgets = mainWindow->getStackedWidget()->currentWidget();
    QCOMPARE(stacked_widgets->metaObject()->className(), QString::fromStdString("Login"));
}

void WindowGenerationTests::test_UsernameInputField() {
    if (stacked_widgets->metaObject()->className() != QString::fromStdString("Login")) {
        QSKIP("Previous failed test is required");
        return;
    }

    login = (Login*) stacked_widgets;
    QLineEdit* input = login->getInput();

    QVERIFY(input != nullptr);

    if (input != nullptr) {
        QTest::keyClicks(input, "TestUsername");
        QCOMPARE(input->text(), QString::fromStdString("TestUsername"));
    }
}

void WindowGenerationTests::test_NewConnectionMessageOnConnectButtonClick() {
    if (login == nullptr) {
        QSKIP("Previous failed test is required");
        return;
    }

    QTest::mouseClick(login->getLoginButton(), Qt::LeftButton);
    QLabel* infos = login->getInfosLabel();

    QVERIFY(infos != nullptr);

    if (infos != nullptr) {
        QCOMPARE(
            infos->text(),
            QString::fromStdString("You are about to log in as \"TestUsername\"\nYour scores and records will be saved under this nickname")
        );
    }
}

void WindowGenerationTests::test_WindowSwitchToMenuOnNewConnectionButtonClicked() {
    if (login == nullptr) {
        QSKIP("Previous failed test is required");
        return;
    }

    QTest::mouseClick(login->getNewConnectionButton(), Qt::LeftButton);
    QCOMPARE(mainWindow->getStackedWidget()->currentWidget()->metaObject()->className(), QString::fromStdString("Menu"));
}

void WindowGenerationTests::cleanupTestCase() {
    delete mainWindow;
}
