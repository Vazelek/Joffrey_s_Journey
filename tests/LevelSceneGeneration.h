#ifndef LEVELSCENEGENERATION_H
#define LEVELSCENEGENERATION_H

#include <QtTest/QtTest>
#include <QObject>
#include "MainWindow.h"

class LevelSceneGeneration : public QObject
{
    Q_OBJECT

private:
    MainWindow* mainWindow;
    MyScene* scene;
    bool test_elements_exists_passed;
    Player* player;

private slots:
    void initTestCase();
    void test_SceneWellGenerated();
    void test_ElementsExists();
    void test_PlayerDataInitialisation();
    void test_ElementsCoordinates();
    void test_SceneWellClosed();

    void cleanupTestCase();
};

#endif // LEVELSCENEGENERATION_H
