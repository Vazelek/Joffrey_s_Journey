#ifndef PLAYERINTERACTIONSTESTS_H
#define PLAYERINTERACTIONSTESTS_H

#include <QtTest/QtTest>
#include <QObject>
#include "MainWindow.h"

class PlayerInteractionsTests : public QObject
{
    Q_OBJECT

private:
    MainWindow* mainWindow;

private slots:
    void initTestCase();
    void test_ArrowKill();
    void test_ShieldSuppressArrow();

    void cleanupTestCase();
};

#endif // PLAYERINTERACTIONSTESTS_H
