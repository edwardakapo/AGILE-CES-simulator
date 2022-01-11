#include "alphastim.h"
#include "ui_alphastim.h"

AlphaStim::AlphaStim(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AlphaStim)
{
    ui->setupUi(this);
    this->setFixedSize(this->size().width(), this->size().height());
    init();
    updateCircuitCheck();

    //Connect UI elements
    connect(findChild<QPushButton*>("power_button"), &QPushButton::released, this, &AlphaStim::togglePower);
    connect(findChild<QPushButton*>("frequency_button"), &QPushButton::released, this, &AlphaStim::setFreq);
    connect(findChild<QPushButton*>("waveform_button"), &QPushButton::released, this, &AlphaStim::setForm);
    connect(findChild<QPushButton*>("duration_button"), &QPushButton::released, this, &AlphaStim::setDur);
    connect(findChild<QPushButton*>("up"), &QPushButton::released, this, &AlphaStim::increaseIntensity);
    connect(findChild<QPushButton*>("down"), &QPushButton::released, this, &AlphaStim::decreaseIntensity);
    connect(findChild<QPushButton*>("swap_batteries"), &QPushButton::released, this, &AlphaStim::swap);
    connect(findChild<QPushButton*>("start"), &QPushButton::released, this, &AlphaStim::promptUser);
    connect(findChild<QPushButton*>("yes"), &QPushButton::released, this, &AlphaStim::recordSession);
    connect(findChild<QPushButton*>("no"), &QPushButton::released, this, &AlphaStim::noRecordSession);
    connect(findChild<QPushButton*>("show_records"), &QPushButton::released, this, &AlphaStim::toggleTherapyHistory);


    //Connect Components
    connect(battery, &Battery::notifyLowBattery, this, &AlphaStim::lowBattery);
    for(int i = 0; i < electrodes.length(); ++i) {
        connect(electrodes[i], &Electrode::notifyContact, this, &AlphaStim::circuitCheck);
    }

    //Connect Timers
    connect(autoOff, &QTimer::timeout, this, &AlphaStim::shutdown);
    connect(idleDischarge, &QTimer::timeout, battery, &Battery::dischage);
    connect(activeDischarge, &QTimer::timeout, battery, &Battery::dischage);
    connect(continuousCircuitCheck, &QTimer::timeout, this, &AlphaStim::circuitCheck);
    connect(continuousFaultCheck, &QTimer::timeout, this, &AlphaStim::faultCheck);
    connect(flashingCircuitSignal, &QTimer::timeout, this, &AlphaStim::flashCircuitSignal);
    connect(therapyTimer, &QTimer::timeout, this, &AlphaStim::runTherapySession);
    connect(promptDelay, &QTimer::timeout, this, &AlphaStim::noRecordSession);
    connect(circuitInterrupt, &QTimer::timeout, this, &AlphaStim::interruptSession);

    //Test Scenarios
    for(int i = 0; i < NUM_TEST_SCENARIOS; ++i) {
        tests.push_back(new TestScenario(this, i+1));
    }

}

AlphaStim::~AlphaStim()
{
    for(int i = 0; i < NUM_ELECTRODES; ++i)
        delete electrodes[i];
    for(int i = 0; i < therapyRecord.size(); ++i)
        delete therapyRecord[i];
    delete battery;
    delete ui;
}

void AlphaStim::init()
{
    isOn = false;
    isInUse = false;
    isDisabled = false;
    isRecording = false;
    isPaused = false;
    isPrompting = false;
    isShowingHistory = false;
    frequency = 100;
    remainingPromptDelay = 0;
    waveform = "Gamma";
    duration = 60;
    intensity = 0;
    maxIntensity = 0;
    QProgressBar* intensityBar = findChild<QProgressBar*>("intensity_level");
    intensityBar->setMaximum(INTENSITY_MAX);
    intensityBar->setMinimum(INTENSITY_MIN);
    autoOff = new QTimer(this);
    battery = new Battery(this);
    for(int i = 0; i < NUM_ELECTRODES; ++i) {
        electrodes.push_back(new Electrode(this, i+1));
    }
    isCircuit = false;
    idleDischarge = new QTimer(this);
    activeDischarge = new QTimer(this);
    continuousCircuitCheck = new QTimer(this);
    continuousFaultCheck = new QTimer(this);
    flashingCircuitSignal = new QTimer(this);
    therapyTimer = new QTimer(this);
    promptDelay = new QTimer(this);
    circuitInterrupt = new QTimer(this);
    timerDisplay = new QTime();
    loadFromFile();
}

void AlphaStim::togglePower()
{
/*
 * Toggles the power on and off.
*/
    try
    {
        if(isDisabled)
            return;
        renewAutoOffTimer();
        if(isInUse || isPrompting)
            stopTherapy();
        isOn = !isOn;
        isShowingHistory = false;
        useBattery(isOn);
        circuitCheck();
        continuousCircuitCheck->start(CONTINUOUS_CIRCUIT_CHECK);
        continuousFaultCheck->start(CONTINUOUS_FAULT_CHECK);
        updatePower();
        updateTimer();
        clearDisplay();
    }
    catch(...)
    {
        qDebug() << "[ERROR] Failed to toggle power.";
    }
}

void AlphaStim::shutdown()
{
/*
 * Shutdown the device.
*/
    try
    {
        isOn = false;
        useBattery(isOn);
        circuitCheck();
        continuousFaultCheck->stop();
        if(isInUse)
            stopTherapy();
        updatePower();
        updateTimer();
    }
    catch(...)
    {
        qDebug() << "[ERROR] Failed to shutdown.";
    }

}

void AlphaStim::renewAutoOffTimer()
{
/*
 * Stops the auto-off idle timer and renews it if the device is not in use. All buttons are routed here first to keep the timer refreshed.
*/
    autoOff->stop();
    if(isInUse) {
        return;
    }
    autoOff->start(AUTO_OFF_TIMER);
}

void AlphaStim::setFreq()
{
/*
 * Finds the current frequency and sets it to the next one. Wraps around the list.
*/
    try
    {
        renewAutoOffTimer();
        if(isInUse)
            return;
        int i;
        QVector<QLabel*> allFreqs;
        for(i = 0; i < NUM_FREQUENCIES; ++i) {
            allFreqs.push_back(findChild<QLabel*>("frequency_label_" + QString::number(i)));
        }
        for(i = 0; i < NUM_FREQUENCIES; ++i) {
            if(frequency == allFreqs[i]->text().toFloat()) {
                //found it
                break;
            }
        }
        if(i == NUM_FREQUENCIES-1){
            frequency = allFreqs[0]->text().toFloat();
        }
        else {
            frequency = allFreqs[i+1]->text().toFloat();
        }
        updateLabels(i, allFreqs);
    }
    catch(...)
    {
        qDebug() << "[ERROR] Failed to set frequency";
    }
}

void AlphaStim::setForm()
{
/*
 * Finds the current waveform and sets it to the next one. Wraps around the list.
*/
    try
    {
        renewAutoOffTimer();
        if(isInUse)
            return;
        int i;
        QVector<QLabel*> allForms;
        for(i = 0; i < NUM_WAVEFORMS; ++i) {
            allForms.push_back(findChild<QLabel*>("waveform_label_" + QString::number(i)));
        }
        for(i = 0; i < NUM_WAVEFORMS; ++i) {
            if(waveform == allForms[i]->text()) {
                //found it
                break;
            }
        }
        if(i == NUM_WAVEFORMS-1) {
            waveform = allForms[0]->text();
        }
        else {
            waveform = allForms[i+1]->text();
        }
        updateLabels(i, allForms);
    }
    catch(...)
    {
        qDebug() << "[ERROR] Failed to set waveform.";
    }
}

void AlphaStim::setDur()
{
/*
 * Finds the current duration and sets it to the next one. Wraps around the list.
*/
    try
    {
        renewAutoOffTimer();
        if(isInUse)
            return;
        int i;
        QVector<QLabel*> allDurs;
        for(i = 0; i < NUM_DURATIONS; ++i) {
            allDurs.push_back(findChild<QLabel*>("duration_label_" + QString::number(i)));
        }
        for(i = 0; i < NUM_DURATIONS; ++i) {
            if(duration == allDurs[i]->text().toInt()) {
                //found it
                break;
            }
        }
        if(i == NUM_DURATIONS-1) {
            duration = allDurs[0]->text().toInt();
        }
        else {
            duration = allDurs[i+1]->text().toInt();
        }
        updateLabels(i, allDurs);
        updateTimer();
    }
    catch(...)
    {
        qDebug() << "[ERROR] Failed to set duration,";
    }
}

void AlphaStim::updateTimer()
{
/*
* Updates the timer display
*/
    if(!isOn)
        timerDisplay->setHMS(0, 0, 0, 0);
    else if(duration == 60)
        timerDisplay->setHMS(1, 0, 0, 0);
    else
        timerDisplay->setHMS(0, duration, 0, 0);

    findChild<QLineEdit*>("timer")->setText(timerDisplay->toString("hh:mm:ss"));

}

void AlphaStim::increaseIntensity()
{
/*
 * Increases intensity of therapy by 50ua.
*/
    renewAutoOffTimer();
    intensity += INTENSITY_INCREMENT;
    if(intensity > INTENSITY_MAX) {
        intensity = INTENSITY_MAX;
    }
    useBattery(isOn);
    updateIntensity();
    setMaxIntensity();
}

void AlphaStim::setMaxIntensity(){
    if(intensity > maxIntensity)
        maxIntensity = intensity;
}

void AlphaStim::decreaseIntensity()
{
/*
 * Decreases intensity of therapy by 100ua.
*/
    renewAutoOffTimer();
    intensity -= INTENSITY_DECREMENT;
    if(intensity < INTENSITY_MIN) {
        intensity = INTENSITY_MIN;
    }
    useBattery(isOn);
    updateIntensity();
}

void AlphaStim::lowBattery()
{
/*
 * Handles low battery notifications (5% and 2%) from Battery, updates the display and shutdown (if 2% or lower).
*/
    QTextEdit* display = findChild<QTextEdit*>("text_display");
    QString warning;

    int level = battery->getLevel();
    if(level == CRITICAL_LEVEL) {
        warning = "[Warning] " + QString::number(CRITICAL_LEVEL) + "% Critial Low Battery Warning. Shutting down now.";
        display->setText(warning);
        shutdown();
    }
    else if (level == LOW_LEVEL) {
        warning = "[Warning] " + QString::number(LOW_LEVEL) + "% Low Battery Warning.";
        display->setText(warning);
    }
}

void AlphaStim::useBattery(bool isOn)
{
/*
 * Uses the battery through timers. Faster drain when in active therapy versus idle.
*/
    try
    {
        if(isOn) {
            if(!isInUse){
                activeDischarge->stop();
                idleDischarge->setInterval(BATTERY_USAGE_RATE);
                idleDischarge->start();
            } else {
                idleDischarge->stop();
                if(intensity!=0){
                    float modifier = 100.0/intensity;
                    activeDischarge->setInterval(BATTERY_USAGE_RATE*modifier);
                    activeDischarge->start();
                }
                else{
                    activeDischarge->setInterval(BATTERY_USAGE_RATE);
                    activeDischarge->start();
                }
            }
        }
        else {
            idleDischarge->stop();
            activeDischarge->stop();
        }
    }
    catch(...)
    {
        qDebug() << "[ERROR] Failed to use battery.";
    }


}

void AlphaStim::circuitCheck()
{
/*
 * Checks if all electrodes are making contact with skin.
*/
    try
    {
        if(!isOn){
            continuousCircuitCheck->stop();
            updateCircuitCheck();
            return;
        }
        for(int i = 0; i < electrodes.length(); ++i) {
            if(!electrodes[i]->getIsContact()) {
                isCircuit = false;
                updateCircuitCheck();
                return;
            }
        }
        isCircuit = true;
        updateCircuitCheck();
    }
    catch(...)
    {
        qDebug() << "[ERROR] Failed to check circuit.";
    }

}

void AlphaStim::faultCheck()
{
    if(!isOn){
        continuousFaultCheck->stop();
        return;
    }
    if(intensity>=DANGEROUS_INTENSITY_LEVEL) {
        handleFault();
    }
}

void AlphaStim::updateCircuitCheck()
{
/*
 * Updates the visuals for circuit check test signal on the main screen.
*/
    QLabel* testCircuit = findChild<QLabel*>("test_circuit");

    if(!isOn){
        testCircuit->setVisible(false);
        return;
    }
    if(!isCircuit) {
        flashCircuitSignal();
        //pause therapy timer session here (requirement #2 from assignment specs)
        //also pauses the user prompt delay
        if((isInUse || isPrompting) && !isPaused){
            isPaused = true;
            //5 second interupt delay, as per the assignment specs
            circuitInterrupt->start(CIRCUIT_TIMEOUT);
            remainingPromptDelay = promptDelay->remainingTime();
            promptDelay->stop();
        }
    }
    else {
        if(isPaused && isPrompting){
            //restart the prompt delay
            promptDelay->start(remainingPromptDelay);
        }
        isPaused = false;
        testCircuit->setVisible(true);
        testCircuit->setText("Connected");
        testCircuit->setStyleSheet("color:rgb(78, 154, 6)");
        if(isInUse)
            circuitInterrupt->stop();
    }
}

void AlphaStim::flashCircuitSignal()
{
/*
 * Creates a flashing effect for test circuit signal when all electrodes are not making contact with skin.
*/
    QLabel* testCircuit = findChild<QLabel*>("test_circuit");
    testCircuit->setText("Disconnected");
    testCircuit->setStyleSheet("color:rgb(239, 41, 41)");

    if(flashingCircuitSignal->isActive()) {
        testCircuit->setVisible(false);
        flashingCircuitSignal->stop();
        return;
    }
    testCircuit->setVisible(true);
    flashingCircuitSignal->setInterval(1000);
    flashingCircuitSignal->start();
}

void AlphaStim::updatePower()
{
/*
 * Updates the appearance of the CES device to indicate powered on or off state.
*/
    QFrame* screen = findChild<QFrame*>("screen");
    QFrame* controls = findChild<QFrame*>("controls");
    QPushButton* powerButton = findChild<QPushButton*>("power_button");
    if(isOn){
        screen->setEnabled(true);
        controls->setEnabled(true);
        setFreq();
        setForm();
        setDur();
        updateIntensity();
        return;
    } else {
        screen->setEnabled(false);
        controls->setEnabled(false);
        powerButton->setChecked(false);
        frequency = 100;
        waveform = "Gamma";
        duration = 60;
        intensity = 0;
        maxIntensity = 0;
        hideLabels();
        clearDisplay();
        updateIntensity();
        return;
    }
}

void AlphaStim::updateLabels(int i, QVector<QLabel*> arr)
{
/*
 * Updates the label colours to show active selection.
*/
    if(i == arr.length()-1){
        arr[i]->setStyleSheet("color:rgb(0, 0, 0)");
        arr[0]->setStyleSheet("color:rgb(239, 41, 41)");
    }
    else {
        arr[i]->setStyleSheet("color:rgb(0, 0, 0)");
        arr[i+1]->setStyleSheet("color:rgb(239, 41, 41)");
    }
}

void AlphaStim::updateIntensity()
{
/*
 * Updates the intensity gauge display.
*/
    QProgressBar* bar = findChild<QProgressBar*>("intensity_level");
    bar->setValue(intensity);
}

void AlphaStim::hideLabels()
{
/*
 * Hides all labels in the control panel. Used to simulate a powered off look.
*/
    QList<QLabel*> lst = findChildren<QLabel*>();
    foreach (QLabel* label, lst) {
        label->setStyleSheet("");
    }
}

void AlphaStim::clearDisplay()
{
/*
 * Clears the display, but leaves the low battery warning on the display for some time.
*/
    QTextEdit* display = findChild<QTextEdit*>("text_display");

    if(display->toPlainText().contains(QString::number(CRITICAL_LEVEL) + "%")) {
        QTimer* delay = new QTimer(this);
        delay->singleShot(SIMULATE_DELAY, this, [=](){
            display->setText("");
        });
    }
    else {
        display->setText("");
    }
}


void AlphaStim::swap()
{
/*
 * Swaps the current battery with a new one
*/
    try
    {
        if(isInUse || isPrompting)
            stopTherapy();
        shutdown();
        QPushButton* swapButton = findChild<QPushButton*>("swap_batteries");
        QTextEdit* display = findChild<QTextEdit*>("text_display");
        idleDischarge->stop();
        activeDischarge->stop();
        Battery* tmp = battery;
        battery = new Battery(this);
        delete tmp;
        connect(idleDischarge, &QTimer::timeout, battery, &Battery::dischage);
        connect(activeDischarge, &QTimer::timeout, battery, &Battery::dischage);
        connect(battery, &Battery::notifyLowBattery, this, &AlphaStim::lowBattery);
        useBattery(isOn);
        display->setFontPointSize(18);
        display->setPlainText("The Batteries have been changed!");

        //disable swap battery button
        swapButton->setEnabled(false);

        //keep message for specified time
        QTimer *delay = new QTimer(this);
        delay->setSingleShot(true);
        connect(delay, &QTimer::timeout, [=](){
            //revert changes
            display->setFontPointSize(9);
            swapButton->setEnabled(true);
        });
        delay->start(SIMULATE_DELAY);
    }
    catch(...)
    {
        qDebug() << "[ERROR] Failed to swap battery.";
    }

}

void AlphaStim::handleFault()
{
/*
 * Simulate a current intensity fault
*/
    try
    {
        if(isDisabled || !isOn)
            return;
        //update the display
        QTextEdit* display = findChild<QTextEdit*>("text_display");
        QProgressBar* bar = findChild<QProgressBar*>("intensity_level");
        bar->setStyleSheet("QProgressBar::chunk { background-color:rgb(255, 22, 12); "
                                                                   "border-radius: 5px; width: 35px;  "
                                                                   "margin: 0.5px}"
                                                                   "QProgressBar {"
                                                                   "border: 2px solid grey; "
                                                                   "border-radius: 5px;"
                                                                   "text-align: center;}");
        bar->setMaximum(intensity);
        bar->setValue(intensity);
        display->setFontPointSize(18);
        display->setPlainText("A fault has been detected!");

        //disable system
        isDisabled = true;

        //keep fault on screen for specified time
        QTimer *delay = new QTimer(this);
        delay->setSingleShot(true);
        connect(delay, &QTimer::timeout, [this](){
            shutdown();
        });
        delay->start(SIMULATE_DELAY);
    }
    catch(...)
    {
        qDebug() << "[ERROR] Failed to handle fault.";
    }
}

void AlphaStim::promptUser()
{
/*
 * Prompt the user to choose whether or not to record the therapy session,
*/
    try
    {
        renewAutoOffTimer();
        if(isInUse || !isCircuit || !isOn || isPrompting)
            return;
        isPrompting = true;

        //display message about recording session
        findChild<QTextEdit*>("text_display")->setPlainText("Would you like to record the session?");
        promptDelay->start(PROMPT_USER_DELAY);
    }
    catch(...)
    {
        qDebug() << "[ERROR] Failed to prompt user.";
    }
}

void AlphaStim::startTherapy()
{
/*
 * Starts the therapy session
*/
    try
    {
        renewAutoOffTimer();
        isInUse = true;
        isPrompting = false;
        useBattery(isOn);
        if(!isCircuit || !isOn)
            stopTherapy();
        therapyTimer->start(THERAPY_DECREMENT_RATE);
        updateTimer();
    }
    catch(...)
    {
        qDebug() << "[ERROR] Failed to start therapy.";
    }

}

void AlphaStim::runTherapySession()
{
/*
 * Runs the therapy session
*/
    try
    {
        renewAutoOffTimer();
        if(!isCircuit)
            return;
        if(!isOn)
            stopTherapy();

        QTime tmp = timerDisplay->addSecs(-1);
        findChild<QLineEdit*>("timer")->setText(tmp.toString("hh:mm:ss"));
        if(timerDisplay->minute() == 0 && timerDisplay->second() == 0 && timerDisplay->hour() == 0){
            stopTherapy();
        }
        timerDisplay->setHMS(0, tmp.minute(), tmp.second(), 0);
    }
    catch(...)
    {
        qDebug() << "[ERROR] Failed to run the therapy session.";
    }
}

void AlphaStim::stopTherapy()
{
/*
 * Stops the therapy session
*/
    try
    {
        renewAutoOffTimer();
        isInUse = false;
        isPrompting = false;
        useBattery(isOn);
        promptDelay->stop();
        therapyTimer->stop();
        circuitInterrupt->stop();
        if(isRecording)
            saveSession();

        isRecording = false;
        updateTimer();
        clearDisplay();
    }
    catch(...)
    {
        qDebug() << "[ERROR] Failed to stop therapy.";
    }
}

void AlphaStim::recordSession()
{
/*
 * Handle the user choosing to record the therapy session
*/
    renewAutoOffTimer();
    if(!isOn || !isPrompting)
        return;
    isRecording = true;
    findChild<QTextEdit*>("text_display")->setText("The therapy session is being recorded.");
    promptDelay->stop();
    startTherapy();
}

void AlphaStim::noRecordSession()
{
/*
 * Handle the user choosing to record not the therapy session
*/
    renewAutoOffTimer();
    if(!isOn || !isPrompting)
        return;
    isRecording = false;
    findChild<QTextEdit*>("text_display")->setText("The therapy session is not being recorded.");
    promptDelay->stop();
    startTherapy();
}

void AlphaStim::saveSession()
{
/*
 * Saves the recently terminated therapy session
*/
    try
    {
        //calculated the how much time remains in the therapy session, in seconds
        int remainingSessionTime = (timerDisplay->minute()*60 + timerDisplay->second());

        //calculated the length of the therapy session
        int sessionDuration = (duration*60) - remainingSessionTime;
        Record* r = new Record(waveform, frequency, maxIntensity, sessionDuration);
        therapyRecord.push_back(r);

        // save to file here
        saveToFile(r);
    }
    catch(...)
    {
        qDebug() << "[ERROR] Failed to save therapy session.";
    }
}



void AlphaStim::toggleTherapyHistory()
{
/*
 * Toggles displaying the history of therapy sessions
*/
    renewAutoOffTimer();
    if(isPrompting)
        return;
    isShowingHistory = !isShowingHistory;
    QString displayMsg = "";
    if(isShowingHistory){
        if(therapyRecord.size() > 0){
            for(int i = therapyRecord.size() - 1 ; i >= 0; --i){
                displayMsg += therapyRecord[i]->print();
                displayMsg += "\n";
            }
        }
        for(int i = recordlist.size() - 1; i >= 0; --i){
            displayMsg += recordlist[i];
            displayMsg += "\n";
        }

    }
    findChild<QTextEdit*>("text_display")->setPlainText(displayMsg);
}

void AlphaStim::saveToFile(Record* r)
/*
 * Saves therapy session data to file.
*/
{
    try
    {
        QFile data("Session_history");
        data.open(QIODevice::Append);
        QTextStream out (&data);
        out << r->print()<<endl;
        data.close();
    }
    catch(...)
    {
        qDebug() << "[ERROR] Saving to file failed.";
    }

}

void AlphaStim::loadFromFile()
/*
 * Loads the session history data from file into AlphaStim.
*/
{
    try
    {
        QFile data("Session_history");
        if(data.open(QIODevice::ReadOnly)){
            QTextStream in(&data);
            while(not in.atEnd()){
                recordlist.push_back(in.readLine());
            }
        }
        data.close();
    }
    catch(...)
    {
        qDebug() << "[ERROR] Loading from file failed.";
    }

}

void AlphaStim::interruptSession()
{
/*
 * Handles interruptions when an Electrode is disconnected during therapy session.
*/
    findChild<QTextEdit*>("text_display")->setPlainText("The therapy session was interrupted!");
    stopTherapy();
}


//Getters
bool AlphaStim::getIsOn() { return isOn; }
bool AlphaStim::getIsCircuit() { return isCircuit; }
QString AlphaStim::getWaveform(){ return waveform; }
float AlphaStim::getFrequency(){ return frequency; }
int AlphaStim::getDuration(){ return duration; }
int AlphaStim::getIntensity(){ return intensity; }
bool AlphaStim::getIsPrompting(){ return isPrompting; }
bool AlphaStim::getIsInUse(){ return isInUse; }
bool AlphaStim::getIsDisabled() { return isDisabled; }
Battery* AlphaStim::getBattery() { return battery; }
int AlphaStim::getNumSavedSessions(){ return therapyRecord.size();}

//Setters
void AlphaStim::setIntensity(int i) { intensity = i; }
