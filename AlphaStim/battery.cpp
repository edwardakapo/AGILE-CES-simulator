#include "battery.h"

Battery::Battery(AlphaStim* as)
    : alphaStim(as)
{
    init();
}

Battery::~Battery(){
    //do nothing
}

void Battery::init()
{
    level = TOTAL_CHARGE;
    display = alphaStim->findChild<QProgressBar*>("battery");
    updateDisplay();
}

void Battery::dischage()
{
/*
 * Simulates battery consumption by lowering the charge level.
*/
    level -= DISCHARGE_STEP;
    updateDisplay();
    isLowBattery();
}

void Battery::isLowBattery()
{
/*
 * Triggers a warning signal to the AlphaStim if battery levels are low.
*/
    if(level <= CRITICAL_LEVEL || level <= LOW_LEVEL){
        warning();
    }
}


void Battery::warning()
{
/*
 * Notify the AlphaStim of the low battery state.
*/
    emit notifyLowBattery();
}

void Battery::updateDisplay()
{
/*
 * Updates the battery level value shown in the UI.
*/
    display->setValue(level);
}

int Battery::getLevel() { return level; }

void Battery::lowCharge()
{
/*
 * sets the battery charge to a small value
*/
    level = SMALL_VALUE;
    updateDisplay();
    isLowBattery();
}
