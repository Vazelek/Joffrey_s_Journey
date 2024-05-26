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
    MyScene* scene;
    Player* player;

private slots:
    void initTestCase();
    void test_ArrowKill();
    void test_LevelRespawnPoint();
    void test_ActivateCheckpoint();
    void test_ReturnToCheckpointOnDeath();
    void test_PowerObtention();
    void test_PowerActivation();
    void test_ShieldProtectPlayer();

    void cleanupTestCase();
};

#endif // PLAYERINTERACTIONSTESTS_H