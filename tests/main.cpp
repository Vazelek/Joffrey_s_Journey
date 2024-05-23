#include <QtTest/QtTest>
#include <QApplication>
#include "PlayerInteractionsTests.h"
#include "WindowGenerationTests.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    int status = 0;
    status |= QTest::qExec(new PlayerInteractionsTests, argc, argv);
    status |= QTest::qExec(new WindowGenerationTests, argc, argv);

    return status;
}