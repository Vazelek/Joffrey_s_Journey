#ifndef TESTEXAMPLE_H
#define TESTEXAMPLE_H

#include <QtTest/QtTest>
#include <QObject>

class TestExample : public QObject
{
    Q_OBJECT

private slots:
    void testCase1();
    void testCase2();
};

#endif // TESTEXAMPLE_H
