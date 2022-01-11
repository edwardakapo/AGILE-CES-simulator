#include "electrode.h"

Electrode::Electrode(AlphaStim* as, int i)
    : alphaStim(as)
    , id(i)
{
    init();
    connect(contactButton, &QPushButton::released, this, &Electrode::toggleContact);
}

Electrode::~Electrode(){
    //do nothing
}

void Electrode::init()
{
    isContact = false;
    contactButton = alphaStim->findChild<QPushButton*>("electrode_"+QString::number(id));
}

void Electrode::toggleContact()
{
/*
 * Toggles contact (on or off) with skin and notifies the AlphaStim of the state change.
*/
    isContact = !isContact;
    emit notifyContact();
}

bool Electrode::getIsContact() { return isContact; }
