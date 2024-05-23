#ifndef WINDOWGENERATIONTESTS_H
#define WINDOWGENERATIONTESTS_H

#include <QtTest/QtTest>
#include <QObject>
#include "MainWindow.h"

class WindowGenerationTests : public QObject
{
    Q_OBJECT

private:
    MainWindow* mainWindow;

private slots:
    void initTestCase();
    void test_WindowWellGenerated();
    void test_ShieldSuppressArrow();

    void cleanupTestCase();
};

#endif // WINDOWGENERATIONTESTS_H
