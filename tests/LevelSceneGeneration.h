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

private slots:
    void initTestCase();
    void test_ArrowKill();
    void test_ShieldSuppressArrow();

    void cleanupTestCase();
};

#endif // LEVELSCENEGENERATION_H
