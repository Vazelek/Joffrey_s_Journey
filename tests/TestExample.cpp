#include "TestExample.h"

void TestExample::testCase1()
{
    QVERIFY(true); // This will always pass
}

void TestExample::testCase2()
{
    QCOMPARE(1 + 1, 2); // This will also pass
    QCOMPARE(0, 1);
}

QTEST_MAIN(TestExample)
// #include "TestExample.moc"
