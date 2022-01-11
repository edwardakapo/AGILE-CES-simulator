#ifndef ALPHASTIM_H
#define ALPHASTIM_H

/*
 * Class: AlphaStim
 * Role: Subject
 * Purpose: The AlphaStim is the subject and the "MainWindow" for the application.
 *          It simulates the main unit of the cranial electrotheerapy stimulation (CES) device.
 *          It also orchestrates the main behaviour flow by maintaining it's components (Battery, Electrodes, Records).
 *
 * Constants may be modified to adjust the AlphaStim's behaviour.
*/

#define AUTO_OFF_TIMER              30000       // (ms) Idle time elapsed before auto shut off.
#define CONTINUOUS_CIRCUIT_CHECK    250         // (ms) Time interval for continuously detecting if all electrodes are in contact or not.
#define CONTINUOUS_FAULT_CHECK      250         // (ms) Time interval for continuously detecting a fault in the intensity delivered.
#define SIMULATE_DELAY              3000        // (ms) The delay for time taken to swap battery, clear display, or show faulty message.
#define CIRCUIT_TIMEOUT             5000        // (ms) The time elapsed before terminating the therapy session if electrodes lose contact.
#define BATTERY_USAGE_RATE          6000        // (ms) The rate at which the battery drains, and it's affected by a modifier when in active therapy use depending on intensity level.
#define THERAPY_DECREMENT_RATE      15          // (ms) The rate at which therapy session time expires (speed of session).
#define PROMPT_USER_DELAY           5000        // (ms) The time alloted to the user to choose "Yes" or "No" when prompted to save the session.
#define DANGEROUS_INTENSITY_LEVEL   700         // (μa) The threshold intensity for what a fault is considered to be.
#define INTENSITY_INCREMENT         50          // (μa) The amount of intensity increase when pressing "Up".
#define INTENSITY_DECREMENT         100         // (μa) The amount of intensity decrease when pressing "Down".
#define INTENSITY_MAX               500         // (μa) The maximum intensity the device can deliver.
#define INTENSITY_MIN               0           // (μa) The minimum intensity the device can deliver.
#define NUM_ELECTRODES              2           // The number of electrodes for the device.
#define NUM_FREQUENCIES             3           // The number of frequency options available.
#define NUM_WAVEFORMS               3           // The number of waveform options available.
#define NUM_DURATIONS               3           // The number of therapy durations available.
#define NUM_TEST_SCENARIOS          9           // The number of test scenarios in the admin panel.

#include "battery.h"
#include "electrode.h"
#include "record.h"
#include "testscenario.h"

#include <QMainWindow>
#include <QDebug>
#include <QVector>
#include <QLabel>
#include <QTimer>
#include <QFile>
#include <QTextStream>
#include <stdio.h>
#include <iostream>

QT_BEGIN_NAMESPACE
namespace Ui { class AlphaStim; }
QT_END_NAMESPACE

class Battery;
class Electrode;
class Record;
class TestScenario;

class AlphaStim : public QMainWindow
{
    Q_OBJECT

public:
    AlphaStim(QWidget *parent = nullptr);
    ~AlphaStim();

private:
    void init();
    void updateLabels(int, QVector<QLabel*>);
    void updateIntensity();
    void updatePower();
    void updateTimer();
    void updateCircuitCheck();
    void flashCircuitSignal();
    void hideLabels();
    void clearDisplay();
    void useBattery(bool);
    void delay(int);
    void stopTherapy();
    void saveSession();
    void setMaxIntensity();
    void saveToFile(Record*);
    void loadFromFile();

    Ui::AlphaStim *ui;
    QTime*  timerDisplay;
    QTimer* autoOff;
    QTimer* idleDischarge;
    QTimer* activeDischarge;
    QTimer* continuousCircuitCheck;
    QTimer* flashingCircuitSignal;
    QTimer* therapyTimer;
    QTimer* promptDelay;
    QTimer* circuitInterrupt;
    QTimer* continuousFaultCheck;
    bool isInUse;
    bool isPrompting;
    bool isOn;
    bool isPaused;
    bool isDisabled;
    bool isShowingHistory;
    float frequency;
    int duration;
    int intensity;
    int maxIntensity;
    int remainingPromptDelay;
    bool isCircuit;
    bool isRecording;
    QString waveform;
    Battery* battery;
    QVector<Electrode*> electrodes;
    QVector<Record*> therapyRecord;
    QVector<QString> recordlist;
    QVector<TestScenario*> tests;

public slots:
    void togglePower();
    void shutdown();
    void renewAutoOffTimer();
    void setFreq();
    void setForm();
    void setDur();
    void increaseIntensity();
    void decreaseIntensity();
    void lowBattery();
    void circuitCheck();
    void swap();
    void handleFault();
    void faultCheck();
    void promptUser();
    void runTherapySession();
    void recordSession();
    void noRecordSession();
    void toggleTherapyHistory();
    void startTherapy();
    void interruptSession();

    bool getIsOn();
    bool getIsCircuit();
    QString getWaveform();
    float getFrequency();
    int getDuration();
    int getIntensity();
    int getNumSavedSessions();
    bool getIsPrompting();
    bool getIsInUse();
    bool getIsDisabled();
    Battery* getBattery();

    void setIntensity(int);

};
#endif // ALPHASTIM_H
