#ifndef ELECTRODE_H
#define ELECTRODE_H

/*
 * Class: Electrode
 * Role: Observer
 * Purpose: Electrodes make contact with the user's skin and deliver treatment.
 *          The AlphaStim device sends electrotherapy signals through the Electrodes.
*/

#include "alphastim.h"
#include <QObject>
#include <QDebug>
#include <QPushButton>

class AlphaStim;

class Electrode : public QObject
{
    Q_OBJECT
public:
    Electrode(AlphaStim*, int);
    ~Electrode();
    bool getIsContact();

private:
    AlphaStim* alphaStim;
    bool isContact;
    int id;
    QPushButton* contactButton;

    void init();
public slots:
    void toggleContact();
signals:
    void notifyContact();
};

#endif // ELECTRODE_H
