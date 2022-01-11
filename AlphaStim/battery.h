#ifndef BATTERY_H
#define BATTERY_H

/*
 * Class: Battery
 * Role: Observer
 * Purpose: The battery powers the AlphaStim.
 *
 * Constants may be modified to adjust the battery's behaviour.
*/

#define DISCHARGE_STEP  1       // The decrement step for each time the AlphaStim discharges this battery.
#define CRITICAL_LEVEL  2       // The battery level at which the second low level warning is given and AlphaStim shuts off.
#define LOW_LEVEL       5       // The battery level at which the first low level warning is given.
#define TOTAL_CHARGE    100     // (%) The total battery level capacity, expressed as a percent.
#define SMALL_VALUE     6       // A small value used for TestScenario to quickly simulate a low level state.

#include "alphastim.h"

#include <QObject>
#include <QDebug>
#include <QProgressBar>

class AlphaStim;

class Battery : public QObject
{
    Q_OBJECT
public:
    Battery(AlphaStim*);
    ~Battery();
    int getLevel();
    void lowCharge();

private:
    AlphaStim* alphaStim;
    int level;
    QProgressBar* display;
    void init();
    void isLowBattery();
    void updateDisplay();

public slots:
    void dischage();
    void warning();

signals:
    void notifyLowBattery();
};

#endif // BATTERY_H
