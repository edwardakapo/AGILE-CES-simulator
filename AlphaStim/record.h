#ifndef RECORD_H
#define RECORD_H

/*
 * Class: Record
 * Role: Entity
 * Purpose: Records store a therapy session's information so the user can view and track their history.
*/

#include "alphastim.h"
#include "QObject"
#include "QDebug"
#include "QDateTime"

class AlphaStim;

class Record: public QObject
{
    Q_OBJECT
public:
    Record(QString, float, int, int);
    ~Record();
    QString print();
private:
    QDateTime* date;
    QString    timeStamp;
    QString    waveform;
    float      frequency;
    int        intensity;
    int        duration;
    void init();
    QString makeTimeStamp();

};

#endif // RECORD_H
