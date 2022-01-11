#include "record.h"


Record::Record(QString w, float f, int i, int d):
    waveform(w), frequency(f), intensity(i),
    duration(d)
{
    init();
}

Record::~Record()
{
    delete date;
}

void Record::init()
{
    timeStamp = makeTimeStamp();
}

QString Record::makeTimeStamp()
{
/*
 * Creates a time stamp in the form YYYY-MM-DD, HH:MM
*/
    date = new QDateTime();
    QString stamp = "";
    stamp += QString::number(date->date().currentDate().year());
    stamp += "-";
    stamp += QString::number(date->date().currentDate().month());
    stamp += "-";
    stamp += QString::number(date->date().currentDate().day());
    stamp += ", ";
    stamp += date->time().currentTime().toString().remove(5, 3);
    return stamp;
}


QString Record::print()
{
/*
 * Returns a formatted string for Record displaying
*/
    int toMinutesRatio = 60;
    return QString("%1 - %2 -%3Hz -%4μa -%5min %6secs").arg(timeStamp).arg(waveform).arg(frequency, 4).arg(intensity, 4).arg(duration/toMinutesRatio, 3).arg(duration%toMinutesRatio,2);
}
