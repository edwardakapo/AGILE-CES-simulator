# Developing-a-CES-device-simulator-with-AGILE-modelling
# COMP 3004 Project

The goal of this project was to develop and test a simulator for the embedded
software used in Cranial Electrical Stimulation (CES) devices, similar to the Alpha-Stim
product. A CES device is a non-invasive neuro-stimulation medical device that delivers
microcurrents via electrodes connected to the earlobes to stimulate the brain for the
purposes of therapeutic intervention. This non-invasive intervention has been shown to
treat conditions such as insomnia, anxiety, and depression. The implementation was
done in C++ using the QT framework. What follows are the use cases that were
designed from the given specification.
The technical document has the specification for the design and all the Modelling

## Team Members  
  
Billal Ghadie  
Oluwademilade Edward Akapo  
Michael Grewal  
Huzaifa Patel  

## How to Run

**The following instructions should be done in the COMP 3004 Virtual Machine:**  

1. Download the Source Code.  
2. Open QT Creator.  
3. Click "Open".  
4. Navigate to the "AlphaStim" directory.  
5. Open the "AlphaStim.pro" file.  
6. Press the green play button on the bottom left of the QT Creator Application.  
7. Wait for the code to build and run.  

## Usage

To use the Alphastim device, the following three conditions **must** hold:
* The power must be turned on.  
* **Both** the Electrodes must be connected to the skin.
* The battery must be sufficiently charged. If it is not sufficiently charged, you may swap batteries from the admin control panel.  

&nbsp;

Before starting **any** automated test, the following two conditions **must** hold:
* The power must be turned off.
* **Both** electrodes must be disconnected from the patients skin.  

&nbsp;

**Note:** It is suggested that the automated tests be run in the order provided on the application window.  
This is because Test 9 disables the AlphaStim device permanently.  
