#ifndef UNITTEST_H
#define UNITTEST_H

#include <QtTest/QtTest>
#include "utils.h"

class UnitTest : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void test_collidesWithPlatform_notCollidingTopLeft();
    void test_collidesWithPlatform_notCollidingDown();
    void test_collidesWithPlatform_notColliding_limit();
    void test_collidesWithPlatform_colliding();
    void cleanupTestCase();
};

#endif
