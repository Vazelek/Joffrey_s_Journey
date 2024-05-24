#include <QtTest/QtTest>
#include <QApplication>
#include "PlayerInteractionsTests.h"
#include "WindowGenerationTests.h"
#include "LevelSceneGeneration.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    int status = 0;
    status |= QTest::qExec(new WindowGenerationTests, argc, argv);
    status |= QTest::qExec(new LevelSceneGeneration, argc, argv);
    status |= QTest::qExec(new PlayerInteractionsTests, argc, argv);

    return status;
}