#ifndef RTC_H
#define RTC_H

#include <uRTCLib.h>

class CustomuRTCLib : public uRTCLib
{
public:
    CustomuRTCLib(const int address);
    bool clockDataChanged();
    bool dateDataChanged();

private:
    int8_t clockNow;
    int8_t lastClock;
    int8_t dateNow;
    int8_t lastDate;
};

#endif