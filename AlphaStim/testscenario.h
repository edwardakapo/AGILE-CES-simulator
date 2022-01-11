#ifndef TESTSCENARIO_H
#define TESTSCENARIO_H

/*
 * Class: TestScenario
 * Role: Testing
 * Purpose: TestScenarios are automated test scripts to verify the AlphaStim's functionalities.
 *          Each TestScenario must start from the AlphaStim's OFF state.
 *          TestScenarios are logged in the console and includes continuous state checking of Expected vs Actual.
 *          TestScenarios always result in a pass or fail.
 *          TestScenarios are not short circuited, they attempt to finish each step in the pipeline.
*/

#define TEST_INTENSITY  300     // (μa) Intensity used for related tests.

#include "alphastim.h"

#include <QObject>
#include <QDebug>
#include <QWidget>
#include <QTimer>
#include <QLabel>
#include <unistd.h>
#include <QPushButton>
#include <QTextEdit>

class TestScenario : public QObject
{
    Q_OBJECT
public:
    TestScenario(AlphaStim*, int);
private:
    AlphaStim* alphaStim;
    int scenario;
    bool isPass;
    QTimer* timer;
    QPushButton* button;
    void init();
    void displayRunning();
    void displayDone();
    void failTest();
    bool run();
    void printStart();
    void testScript1();
    void testScript2();
    void testScript3();
    void testScript4();
    void testScript5();
    void testScript6();
    void testScript7();
    void testScript8();
    void testScript9();

signals:
    void pass();
    void fail();
public slots:
    void updatePassOrFail();
};

#endif // TESTSCENARIO_H
