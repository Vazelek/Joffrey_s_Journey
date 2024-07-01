#include "UnitTest.h"

void UnitTest::initTestCase() { 
    QVERIFY(true);  
}

void UnitTest::test_collidesWithPlatform_notCollidingTopLeft(){
    bool collides = collidesWithPlatform(
        0, 
        0, 
        100,
        100,
        50,
        50,
        10,
        10,
        0,
        0
    );
    QCOMPARE(false, collides);
}

void UnitTest::test_collidesWithPlatform_notCollidingDown(){
    bool collides = collidesWithPlatform(
        100, 
        150, 
        100,
        100,
        50,
        50,
        10,
        10,
        0,
        0
    );
    QCOMPARE(false, collides);
}


void UnitTest::test_collidesWithPlatform_notColliding_limit(){
    bool collides = collidesWithPlatform(
        0, 
        0, 
        100,
        100,
        100,
        100,
        10,
        10,
        0,
        0
    );
    QCOMPARE(false, collides);
}

void UnitTest::test_collidesWithPlatform_colliding(){
    bool collides = collidesWithPlatform(
        100, 
        100, 
        100,
        100,
        100,
        100,
        10,
        10,
        0,
        0
    );
    QCOMPARE(true, collides);
}

void UnitTest::cleanupTestCase() {
    QVERIFY(true);
}
