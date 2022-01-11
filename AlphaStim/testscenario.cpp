#include "testscenario.h"

TestScenario::TestScenario(AlphaStim* as, int n)
    :alphaStim(as)
    , scenario(n)
{
    init();
}

void TestScenario::init()
{
    isPass = false;
    timer = new QTimer(this);
    QString buttonName = "test_" + QString::number(scenario);
    button = alphaStim->findChild<QPushButton*>(buttonName);
    connect(button, &QPushButton::released, this, &TestScenario::run);
    connect(this, &TestScenario::pass, this, &TestScenario::updatePassOrFail);
    connect(this, &TestScenario::fail, this, &TestScenario::updatePassOrFail);
}

void TestScenario::displayRunning()
{
/*
 * Shows "Running..." on the Button
*/
    button->setText("Running...");
}

void TestScenario::printStart()
{
    qDebug() << QString("[Test %1] Starting.").arg(scenario);
}

bool TestScenario::run()
{
/*
 * Switches to the correct test script depending on which scenario is pressed.
*/
    switch (scenario) {
    case 1:
        //TEST SCENARIO 1 - TOGGLE POWER ON/OFF
        testScript1();
        break;
    case 2:
        //TEST SCENARIO 2 - CONTINUOUS CIRCUIT CHECK
        testScript2();
        break;
    case 3:
        //TEST SCENARIO 3 - CHANGES CURRENT INTENSITY
        testScript3();
        break;
    case 4:
        //TEST SCENARIO 4 - START THERAPY
        testScript4();
        break;
    case 5:
        //TEST SCENARIO 5 - TEST CONFIGURATION
        testScript5();
        break;
    case 6:
        //TEST SCENARIO 6 - TEST SAVING A THERAPY SESSION
        testScript6();
        break;
    case 7:
        //TEST SCENARIO 7 - TEST AUTO OFF TIMER
        testScript7();
        break;
    case 8:
        //TEST SCENARIO 8 - FORCE LOW BATTERY STATE
        testScript8();
        break;
    case 9:
        //TEST SCENARIO 9 - SIMULATE 700μa INTENSITY FAULT
        testScript9();
        break;
    }
    return false;
}

void TestScenario::updatePassOrFail()
{
/*
 * Updates the button to show pass (green) or fail (red).
*/
    if(isPass) {
        button->setStyleSheet("background:rgb(115, 210, 22)");
        button->setText("Pass!");
    }
    else {
        button->setStyleSheet("background:rgb(204, 0, 0)");
        button->setText("Fail!");
    }
}



void TestScenario::testScript1()
{
/*
 * Toggles power button on and off several times.
*/
    try
    {
        displayRunning();
        printStart();

        //Power ON
        qDebug() << "Turning AlphaStim ON";
        QPushButton* powerButton = alphaStim->findChild<QPushButton*>("power_button");
        powerButton->click();
        //Expected: ON
        qDebug() << "-- Checking state... Expected: ON";
        if(!alphaStim->getIsOn()){
            qDebug() << "-- Actual: OFF";
            throw "";
        }
        qDebug() << "-- Actual: ON";

        //Power OFF
        timer->singleShot(500, this, [=](){
            qDebug() <<  "Turning AlphaStim OFF";
            powerButton->click();
            //Expected: OFF
            qDebug() << "-- Checking state... Expected: OFF";
            if(alphaStim->getIsOn()){
                qDebug() << "-- Actual: ON";
                failTest();
            }
            qDebug() << "-- Actual: OFF";

        });

        //Power ON
        timer->singleShot(2000, this, [=](){
            qDebug() <<  "Turning AlphaStim ON";
            powerButton->click();
            //Expected: ON
            qDebug() << "-- Checking state... Expected: ON";
            if(!alphaStim->getIsOn()){
                qDebug() << "-- Actual: OFF";
                failTest();
            }
            qDebug() << "-- Actual: ON";
        });

        //Power OFF
        timer->singleShot(3000, this, [=](){
            qDebug() << "Turning AlphaStim OFF";
            powerButton->click();
            //Expected: OFF
            //If OFF then pass, otherwise fail.
            qDebug() << "-- Checking state... Expected: OFF";
            if(!alphaStim->getIsOn()) {
                qDebug() << "-- Actual: OFF";
                qDebug() << "[Test 1] Passed!";
                isPass = true;
                emit pass();
            }
            else {
                qDebug() << "-- Actual: ON";
                failTest();
            }
        });
    }
    catch(...)
    {
        failTest();
    }
}

void TestScenario::testScript2()
{
/*
 * Turns on the device then toggles the electrodes on and off. Observe test circuit indicator.
*/
    try
    {
        displayRunning();
        printStart();

        //Power ON
        qDebug() <<  "Turning AlphaStim ON";
        QPushButton* powerButton = alphaStim->findChild<QPushButton*>("power_button");
        powerButton->click();

        QVector<QPushButton*> electrodes;
        for(int i = 0; i < NUM_ELECTRODES; ++i){
            electrodes.push_back(alphaStim->findChild<QPushButton*>("electrode_" + QString::number(i+1)));
        }

        //Connect both electrodes
        timer->singleShot(3000, this, [=](){
            for(int i = 0; i < electrodes.length(); ++i){
                qDebug() <<  "Connecting Electrode" << i+1;
                electrodes[i]->click();
            }
            //Expected: Connected
            qDebug() << "-- Checking state... Expected: CONNECTED";
            if(!alphaStim->getIsCircuit()){
                qDebug() << "-- Actual: DISCONNECTED";
                failTest();
            }
            qDebug() << "-- Actual: CONNECTED";
        });

        //Disconnect electrode 1
        timer->singleShot(6000, this, [=](){
            qDebug() <<  "Disconnecting Electrode 1";
            electrodes[0]->click();
            //Expected: Disconnected (no circuit)
            qDebug() << "-- Checking state... Expected: DISCONNECTED";
            if(alphaStim->getIsCircuit()){
                qDebug() << "-- Actual: CONNECTED";
                failTest();
            }
            qDebug() << "-- Actual: DISCONNECTED";
        });

        //Connect electrode 1
        timer->singleShot(9000, this, [=](){
            qDebug() <<  "Connecting Electrode 1";
            electrodes[0]->click();
            //Expected: Connected
            qDebug() << "-- Checking state... Expected: CONNECTED";
            if(!alphaStim->getIsCircuit()){
                qDebug() << "-- Actual: DISCONNECTED";
                failTest();
            }
            qDebug() << "-- Actual: CONNECTED";
        });

        //Disconnect electrode 2
        timer->singleShot(12000, this, [=](){
            qDebug() <<  "Disconnecting Electrode 2";
            electrodes[electrodes.length()-1]->click();
            //Expected: Disconnected (no circuit)
            qDebug() << "-- Checking state... Expected: DISCONNECTED";
            if(alphaStim->getIsCircuit()){
                qDebug() << "-- Actual: CONNECTED";
                failTest();
            }
            qDebug() << "-- Actual: DISCONNECTED";
        });

        //Connect electrode 2
        timer->singleShot(15000, this, [=](){
            qDebug() <<  "Connecting Electrode 2";
            electrodes[electrodes.length()-1]->click();
            //Expected: Connected
            qDebug() << "-- Checking state... Expected: CONNECTED";
            if(!alphaStim->getIsCircuit()){
                qDebug() << "-- Actual: DISCONNECTED";
                failTest();
            }
            qDebug() << "-- Actual: CONNECTED";
        });

        //Disconnect both electrodes
        timer->singleShot(18000, this, [=](){
            for(int i = 0; i < electrodes.length(); ++i){
                qDebug() <<  "Disconnecting Electrode" << i+1;
                electrodes[i]->click();
            }
            //Expected: Disconnected (no circuit)
            qDebug() << "-- Checking state... Expected: DISCONNECTED";
            if(alphaStim->getIsCircuit()){
                qDebug() << "-- Actual: CONNECTED";
                failTest();
            }
            qDebug() << "-- Actual: DISCONNECTED";\
        });

        //Connect both electrodes
        timer->singleShot(21000, this, [=](){
            for(int i = 0; i < electrodes.length(); ++i){
                qDebug() <<  "Connecting Electrode" << i+1;
                electrodes[i]->click();
            }
            //Expected: Connected
            qDebug() << "-- Checking state... Expected: CONNECTED";
            if(alphaStim->getIsCircuit()){
                qDebug() << "-- Actual: CONNECTED";
                qDebug() << "[Test 2] Passed!";
                isPass = true;
                emit pass();
            }
            else {
                qDebug() << "-- Actual: DISCONNECTED";
                failTest();
            }

            //Reset state
            qDebug() << "-- Resetting state...";
            for(int i = 0; i < electrodes.length(); ++i){
                electrodes[i]->click();
            }
            powerButton->click();
        });

    }
    catch(...)
    {
        failTest();
    }
}

void TestScenario::testScript3()
{
/*
 * Turns on the device, connect the electrodes, tests min/max bounds for intensity and sets it to TEST_INTENSITY+50.
*/
    try
    {
        displayRunning();
        printStart();
        int delay;
        //Power ON
        qDebug() << "Turning AlphaStim ON";
        QPushButton* powerButton = alphaStim->findChild<QPushButton*>("power_button");
        powerButton->click();

        qDebug() << "Checking upper limit of intensity, clicking 'Up' more than necessary...";
        int numClicksForMinMax = INTENSITY_MAX/INTENSITY_INCREMENT + 5;

        //Increment intensity
        for(delay = 1;delay <= numClicksForMinMax; ++delay){
            timer->singleShot(delay*1000, this, [=](){
                alphaStim->findChild<QPushButton*>("up")->click();
            });
        }
        timer->singleShot(++delay*1000, this, [=](){
            qDebug() << "-- Checking intensity... Expected:" << INTENSITY_MAX;
            qDebug() << "-- Actual: " << alphaStim->getIntensity();
            if(alphaStim->getIntensity() != INTENSITY_MAX){
                failTest();
            }
        });
        timer->singleShot(++delay*1000, this, [=](){
            qDebug() << "Checking lower limit of intensity, clicking 'Down' more than necessary...";
        });

        //Decrement intensity
        for(; delay <= numClicksForMinMax*2; ++delay){
            timer->singleShot(delay*1000, this, [=](){
                alphaStim->findChild<QPushButton*>("down")->click();
            });
        }
        timer->singleShot(++delay*1000, this, [=](){
            qDebug() << "-- Checking intensity... Expected:" << INTENSITY_MIN;
            qDebug() << "-- Actual: " << alphaStim->getIntensity();
            if(alphaStim->getIntensity() != INTENSITY_MIN){
                failTest();
            }
        });

        int testIntensityPlus50 = TEST_INTENSITY+50;

        timer->singleShot(++delay*1000, this, [=](){
            qDebug() << "Setting intensity to" << testIntensityPlus50 << "μa";
        });

        //Increment intensity
        int numClicks = testIntensityPlus50/INTENSITY_INCREMENT;
        int n = delay;
        for(;delay < n+numClicks; ++delay){
            timer->singleShot(delay*1000, this, [=](){
                alphaStim->findChild<QPushButton*>("up")->click();
            });
        }

        //Check that intensity is equal
        timer->singleShot(++delay*1000, this, [this,powerButton,testIntensityPlus50](){
            qDebug() << "-- Checking intensity... Expected:" << testIntensityPlus50;
            qDebug() << "-- Actual: " << alphaStim->getIntensity();
            if(alphaStim->getIntensity() == testIntensityPlus50){
                isPass = true;
                qDebug() << "[Test 3] Passed.";
                emit pass();
            }else{
                failTest();
            }
            //Reset state
            qDebug() << "-- Resetting state...";
            while(alphaStim->getIntensity()>0)
                alphaStim->findChild<QPushButton*>("down")->click();
            powerButton->click();
        });
    }
    catch(...)
    {
        failTest();
    }
}

void TestScenario::testScript4()
{
/*
 * Turns on the device, connects electrodes, then configures and starts a therapy session
*/
        try
        {
            displayRunning();
            printStart();

            qDebug() << "Turning AlphaStim ON";
            //Power ON
            QPushButton* powerButton = alphaStim->findChild<QPushButton*>("power_button");
            powerButton->click();
            //Expected: Alphastim is on
            if(!alphaStim->getIsOn())
                throw "";

            QVector<QPushButton*> electrodes;
            for(int i = 0; i < NUM_ELECTRODES; ++i){
                electrodes.push_back(alphaStim->findChild<QPushButton*>("electrode_" + QString::number(i+1)));
            }

            //Connect both electrodes
            timer->singleShot(3000, this, [=](){
                qDebug() << "Connecting electrodes";
                for(int i = 0; i < electrodes.length(); ++i){
                    electrodes[i]->click();
                }
                //Expected: Connected
                if(!alphaStim->getIsCircuit()){
                    failTest();
                }
            });

            //Set frequency
            timer->singleShot(6000, this, [=](){
                QString freq = alphaStim->findChild<QLabel*>("frequency_label_" + QString::number(NUM_FREQUENCIES-2))->text();
                float testFrequency = freq.toFloat();
                qDebug() << "Setting frequency to" << testFrequency << "Hz";
                alphaStim->findChild<QPushButton*>("frequency_button")->click();
                //Expected: the selected frequency is equal
                if(alphaStim->getFrequency() != testFrequency){
                    failTest();
                }
            });

            //Set waveform
            timer->singleShot(9000, this, [=](){
                QString testWaveForm = alphaStim->findChild<QLabel*>("waveform_label_" + QString::number(NUM_WAVEFORMS-1))->text();
                qDebug() << "Setting waveform to" << testWaveForm;
                for(int i = 0; i < 2; ++i)
                    alphaStim->findChild<QPushButton*>("waveform_button")->click();
                //Expected: the selected waveform is equal
                if(alphaStim->getWaveform() != testWaveForm){
                    failTest();
                }
            });

            //Set duration
            timer->singleShot(12000, this, [=](){
                QString dur = alphaStim->findChild<QLabel*>("duration_label_" + QString::number(NUM_DURATIONS-1))->text();
                int testDuration = dur.toInt();
                qDebug() << "Setting duration to" << testDuration;
                for(int i = 0; i < 2; ++i)
                    alphaStim->findChild<QPushButton*>("duration_button")->click();
                //Expected: the selected duration is equal
                if(alphaStim->getDuration() != testDuration){
                    failTest();
                }
            });

            //Set intensity
            timer->singleShot(15000, this, [=](){
                int testIntensity = TEST_INTENSITY;
                qDebug() << "Setting intensity to" << testIntensity << "μa";
                int numClicks = TEST_INTENSITY/INTENSITY_INCREMENT;
                for(int i = 0; i < numClicks; ++i)
                    alphaStim->findChild<QPushButton*>("up")->click();
                //Expected: the selected intensity is equal
                if(alphaStim->getIntensity() != testIntensity){
                    failTest();
                }
            });

            //start thereapy and ensure the user is being prompted to record the session
            //note recording the therapy is beyond the scope of testing and thus, the session
            //is NOT recorded
            timer->singleShot(18000, this, [=](){
                alphaStim->findChild<QPushButton*>("start")->click();
                qDebug() << "Prompting user to record session";
                //Expected: the selected intensity is equal
                if(!alphaStim->getIsPrompting()){
                    failTest();
                }
                alphaStim->findChild<QPushButton*>("no")->click();

            });

            timer->singleShot(22000, this, [=](){
                qDebug() << "-- Checking state... Expected: IN USE";
            });
            //check therapy is still running
            timer->singleShot(23000, this, [=](){
                if(alphaStim->getIsInUse()){
                    qDebug() << "-- Actual: IN USE";
                    qDebug() << "[Test 4] Passed.";
                    isPass = true;
                    emit pass();
                }else{
                    qDebug() << "-- Actual: NOT IN USE";
                    failTest();
                }
                //Reset state
                qDebug() << "-- Resetting state...";
                for(int i = 0; i < electrodes.length(); ++i){
                    electrodes[i]->click();
                }
                for(int i = 0; i < 5; ++i)
                    alphaStim->findChild<QPushButton*>("down")->click();
                powerButton->click();
            });
        }
        catch(...)
        {
            failTest();
        }
}

void TestScenario::testScript5()
{
/*
 * Tests the configuration for frequency, waveform, and duration of a therapy session.
*/
    try
    {
        displayRunning();
        printStart();
        static bool passFreqs = false;
        static bool passForms = false;
        static bool passDurs = false;

        //Power ON
        qDebug() <<  "Turning AlphaStim ON";
        QPushButton* powerButton = alphaStim->findChild<QPushButton*>("power_button");
        powerButton->click();


        QVector<QLabel*> allFreqs;
        for(int i = 0; i < NUM_FREQUENCIES; ++i) {
            allFreqs.push_back(alphaStim->findChild<QLabel*>("frequency_label_" + QString::number(i)));
        }

        qDebug() << "Testing Frequencies";

        for(int i = 0; i < 3; ++i){
            float freq = allFreqs[i]->text().toFloat();
            timer->singleShot((i+1)*1000, this, [this,freq]() mutable {
                qDebug() << "-- Checking frequency... Expected: " << freq;
                qDebug() << "-- Actual: " << alphaStim->getFrequency();
                if(alphaStim->getFrequency() != freq){
                    failTest();
                }
                passFreqs = true;
                alphaStim->findChild<QPushButton*>("frequency_button")->click();
            });
        }

        QVector<QLabel*> allForms;
        for(int i = 0; i < NUM_WAVEFORMS; ++i) {
            allForms.push_back(alphaStim->findChild<QLabel*>("waveform_label_" + QString::number(i)));
        }

        timer->singleShot(4000, this, [=](){
            qDebug() << "Testing Waveforms";
        });

        for(int i = 0; i < 3; ++i){
            QString form = allForms[i]->text();
            timer->singleShot((i+5)*1000, this, [this,form]() mutable{
                qDebug() << "-- Checking waveforms... Expected: " << form;
                qDebug() << "-- Actual: " << alphaStim->getWaveform();
                if(alphaStim->getWaveform() != form){
                    failTest();
                }
                passForms = true;
                alphaStim->findChild<QPushButton*>("waveform_button")->click();
            });
        }


        //Test duration
        QVector<QLabel*> allDurs;
        for(int i = 0; i < NUM_DURATIONS; ++i){
            allDurs.push_back(alphaStim->findChild<QLabel*>("duration_label_" + QString::number(i)));
        }
        timer->singleShot(8000, this, [=](){
            qDebug() << "Testing Durations";
        });

        for(int i = 0; i < 3; ++i){
            int dur = allDurs[i]->text().toInt();
            timer->singleShot((i+9)*1000, this, [this,dur]() mutable{
                qDebug() << "-- Checking duration... Expected: " << dur;
                qDebug() << "-- Actual: " << alphaStim->getDuration();
                if(alphaStim->getDuration() != dur){
                    failTest();
                }
                passDurs = true;
                alphaStim->findChild<QPushButton*>("duration_button")->click();
            });
        }
        timer->singleShot(12000, this, [this,powerButton]() mutable{
            if(passFreqs && passForms && passDurs) {
                isPass = true;
                qDebug() << "[Test 5] Passed.";
                emit pass();
            }
            else {
                failTest();
            }
            //Reset state
            qDebug() << "-- Resetting state...";
            powerButton->click();
        });
    }
    catch(...)
    {
        failTest();
    }
}


void TestScenario::testScript6()
{
/*
 * Turns on the device, connects electrodes, then configures and records and saves a therapy session.
*/
    try
    {
        displayRunning();
        printStart();

        qDebug() << "Turning AlphaStim ON";
        //Power ON
        QPushButton* powerButton = alphaStim->findChild<QPushButton*>("power_button");
        powerButton->click();
        //Expected: Alphastim is on
        if(!alphaStim->getIsOn())
            throw "";

        QVector<QPushButton*> electrodes;
        for(int i = 0; i < NUM_ELECTRODES; ++i){
            electrodes.push_back(alphaStim->findChild<QPushButton*>("electrode_" + QString::number(i+1)));
        }

        //Connect both electrodes
        timer->singleShot(3000, this, [=](){
            qDebug() << "Connecting electrodes";
            for(int i = 0; i < electrodes.length(); ++i){
                electrodes[i]->click();
            }
            //Expected: Connected
            if(!alphaStim->getIsCircuit()){
                failTest();
            }
        });

        //Set frequency
        timer->singleShot(6000, this, [=](){
            QString freq = alphaStim->findChild<QLabel*>("frequency_label_" + QString::number(NUM_FREQUENCIES-2))->text();
            float testFrequency = freq.toFloat();
            qDebug() << "Setting frequency to" << freq << "Hz";
            alphaStim->findChild<QPushButton*>("frequency_button")->click();
            //Expected: the selected frequency is equal
            if(alphaStim->getFrequency() != testFrequency){
                failTest();
            }
        });

        //Set waveform
        timer->singleShot(9000, this, [=](){
            QString testWaveForm = alphaStim->findChild<QLabel*>("waveform_label_" + QString::number(NUM_WAVEFORMS-1))->text();
            qDebug() << "Setting waveform to" << testWaveForm;
            for(int i = 0; i < 2; ++i)
                alphaStim->findChild<QPushButton*>("waveform_button")->click();
            //Expected: the selected waveform is equal
            if(alphaStim->getWaveform() != testWaveForm){
                failTest();
            }

        });

        //Set duration
        timer->singleShot(12000, this, [=](){
            QString dur = alphaStim->findChild<QLabel*>("duration_label_" + QString::number(NUM_DURATIONS-1))->text();
            int testDuration = dur.toInt();
            qDebug() << "Setting duration to" << dur;
            for(int i = 0; i < 2; ++i)
                alphaStim->findChild<QPushButton*>("duration_button")->click();
            //Expected: the selected duration is equal
            if(alphaStim->getDuration() != testDuration){
                failTest();
            }
        });

        //Set intensity
        timer->singleShot(15000, this, [=](){
            int testIntensity = 300;
            qDebug() << "Setting intensity to" << testIntensity;
            for(int i = 0; i < 6; ++i)
                alphaStim->findChild<QPushButton*>("up")->click();
            //Expected: the selected intensity is equal
            if(alphaStim->getIntensity() != testIntensity){
                failTest();
            }
        });

        //start thereapy and ensure the user is being prompted to record the session
        //note the session is recorded.
        timer->singleShot(18000, this, [=](){
            alphaStim->findChild<QPushButton*>("start")->click();
            qDebug() << "Prompting user to record session";
            //Expected: the selected intensity is equal to 300
            if(!alphaStim->getIsPrompting()){
                failTest();
            }
            alphaStim->findChild<QPushButton*>("yes")->click();

        });

        //check therapy is still running
        timer->singleShot(23000, this, [=](){
            if(!alphaStim->getIsInUse()){
                failTest();
            }
        });

        //represents the number of records saved before the current record
        int num_sessions_saved = alphaStim->getNumSavedSessions();

        //toggle the power to interupt the session
        timer->singleShot(24000, this, [=](){
            powerButton->click();
        });

        timer->singleShot(24500, this, [=](){
            powerButton->click();
        });

        //compare the current number of records saved to the previous. If
        //they former is greater than the later, a new record has been saved.
        timer->singleShot(31000, this, [=](){
            qDebug() << "-- Checking number of records... Expected: " << alphaStim->getNumSavedSessions();
            qDebug() << "-- Actual : " << alphaStim->getNumSavedSessions();
            if(alphaStim->getNumSavedSessions() > num_sessions_saved){
                isPass = true;
                emit pass();
                qDebug() << "[Test 6] Passed.";
            }else{
                failTest();
            }
            //Reset state
            qDebug() << "-- Resetting state...";
            for(int i = 0; i < electrodes.length(); ++i){
                electrodes[i]->click();
            }
            for(int i = 0; i < 5; ++i)
                alphaStim->findChild<QPushButton*>("down")->click();
            powerButton->click();
        });
    }
    catch(...)
    {
        failTest();
    }
}

void TestScenario::testScript7()
{
/*
 * Turns on the alpha stim and waits for AUTO_OFF_TIMER to expire, if the alpha stim turns off then the test case passes.
*/
    try {
        displayRunning();
        //Power ON
        qDebug() << "Turning AlphaStim ON";
        QPushButton* powerButton = alphaStim->findChild<QPushButton*>("power_button");
        if(!alphaStim->getIsOn()){
         powerButton->click();
        }
        qDebug() << "Simulating device auto off feature. Please wait" << AUTO_OFF_TIMER/1000 << "seconds...";
        /* wait 30 minutes then check again if its on */
        timer->singleShot((AUTO_OFF_TIMER), this, [=](){
            qDebug() << "EXPECTED: OFF";
            if(alphaStim->getIsOn()){
                qDebug() << "-- Actual: ON";
             failTest();
            }
            else{
            qDebug() << "-- Actual: OFF";
            isPass = true;
            emit pass();}
        });
    }
     catch (...) {
        failTest();
    }
}

void TestScenario::testScript8()
{
/*
 * Tests for low battery warnings issued at the correct time.
*/
    try
    {
        static bool warning1 = false;
        static bool warning2 = false;
        QString lowTrigger = QString::number(LOW_LEVEL) + "%";
        QString criticalTrigger = QString::number(CRITICAL_LEVEL) + "%";
        QTextEdit* display = alphaStim->findChild<QTextEdit*>("text_display");
        QPushButton* powerButton = alphaStim->findChild<QPushButton*>("power_button");
        QPushButton* swapButton = alphaStim->findChild<QPushButton*>("swap_batteries");
        displayRunning();
        printStart();

        //Power ON
        qDebug() <<  "Turning AlphaStim ON";
        powerButton->click();

        //Force low charge on battery
        if(alphaStim->getBattery()->getLevel() >= SMALL_VALUE)
            qDebug() <<  "Forcing low battery to" << SMALL_VALUE << "%";
            alphaStim->getBattery()->lowCharge();

        if(alphaStim->getIsOn()){
            qDebug() << "-- Checking state... Expected: 2x Warnings at" << lowTrigger << "and" << criticalTrigger;
            timer->setInterval(250);
            timer->start();

            connect(timer, &QTimer::timeout, this, [this,display,powerButton, lowTrigger, criticalTrigger, swapButton]() mutable{
                QString text = display->toPlainText();

                if(text.contains(lowTrigger) && warning1==false) {
                    qDebug() <<  "--" << lowTrigger << "Warning given (first)";
                    warning1 = true;
                }
                if(text.contains(criticalTrigger) && warning2==false) {
                    qDebug() <<  "--" << criticalTrigger << "(second) Warning given (second)";
                    warning2 = true;
                }
                if(!alphaStim->getIsOn()){
                    timer->stop();
                    if(warning1 && warning2) {
                        qDebug() <<  "-- Both warnings given";
                        isPass = true;
                    }
                    else {
                        qDebug() <<  "-- Not all warnings were given";
                    }
                    timer->singleShot(3000,this,[=](){
                        qDebug() << "-- Resetting state...";
                        qDebug() << "-- Putting a fresh battery in.";
                        swapButton->click();
                        if(isPass) {
                            qDebug() << "[Test 7] Passed!";
                            emit pass();
                        }
                        else {
                            failTest();
                        }
                    });
                }
            });
        }
    }
    catch(...)
    {
        failTest();
    }
}


void TestScenario::testScript9()
{
/*
 * Creates a fault which causes intensity to go above DANGEROUS_INTENSITY_LEVEL to test the fault detection handling.
*/
    try
    {
        displayRunning();
        printStart();

        //Power ON
        qDebug() <<  "Turning AlphaStim ON";
        QPushButton* powerButton = alphaStim->findChild<QPushButton*>("power_button");
        powerButton->click();

        //Set intensity to dangerous levels
        qDebug() <<  "Setting the intensity to a dangerous level:" << DANGEROUS_INTENSITY_LEVEL << "μa";
        alphaStim->setIntensity(DANGEROUS_INTENSITY_LEVEL);

        //Give AlphaStim enough time to check for fault and enter disabled state
        timer->singleShot(500, this, [=](){
            qDebug() <<  "-- Checking state... Expected: DISABLED";
            //EXPECTED: Disabled
            if(alphaStim->getIsDisabled()){
                qDebug() << "-- Actual: DISABLED";
                qDebug() << "[Test 8] Passed!";
                isPass = true;
                emit pass();
            }
            else {
                qDebug() << "-- Actual: ENABLED";
                failTest();
            }
            qDebug() << "Resetting state...";
            powerButton->click();
        });
    }
    catch(...)
    {
        failTest();
    }
}

void TestScenario::failTest()
{
/*
 * Handles the failed test by printing a failed message and emiiting the fail signal.
*/
    QString failMsg = "[Test " + QString::number(scenario) + "] Failed.";
    qDebug() << failMsg;
    isPass = false;
    emit fail();
}

